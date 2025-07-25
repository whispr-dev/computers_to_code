// fastping_client.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstring>
#include <sstream>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip_icmp.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

std::atomic<bool> running(true);

struct Target {
    std::string ip;
    int port = 80;
};

void signalHandler(int signum) {
    std::cout << "\n[INFO] Signal " << signum << " received. Exiting.\n";
    running = false;
}

void printUsage() {
    std::cout << "Usage: fastping_client --protocol icmp|udp|tcp --target <ip> [--port <port>] [--format text|json] [--batch <file.json>] [--interval <ms>]\n";
}

void outputResult(const std::string& protocol, const std::string& target, int port, bool success, int ms, const std::string& format) {
    if (format == "json") {
        std::cout << "{ \"protocol\": \"" << protocol
                  << "\", \"target\": \"" << target
                  << "\", \"port\": " << port
                  << ", \"success\": " << (success ? "true" : "false")
                  << ", \"latency_ms\": " << ms
                  << " }\n";
    } else {
        if (success) {
            std::cout << "[" << protocol << "] " << target;
            if (port > 0) std::cout << ":" << port;
            std::cout << " reachable in " << ms << "ms\n";
        } else {
            std::cout << "[" << protocol << "] " << target;
            if (port > 0) std::cout << ":" << port;
            std::cout << " unreachable.\n";
        }
    }
}

int checksum(const void* data, int len) {
    unsigned long sum = 0;
    const uint16_t* ptr = static_cast<const uint16_t*>(data);

    while (len > 1) {
        sum += *ptr++;
        len -= 2;
    }
    if (len) sum += *(const uint8_t*)ptr;

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return ~sum;
}

int icmpPing(const std::string& target) {
#ifdef _WIN32
    SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
#else
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
#endif
    if (sock < 0) return -1;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
#ifdef _WIN32
    inet_pton(AF_INET, target.c_str(), &addr.sin_addr);
#else
    inet_aton(target.c_str(), &addr.sin_addr);
#endif

#ifdef _WIN32
    struct {
        uint8_t type;
        uint8_t code;
        uint16_t checksum;
        uint16_t id;
        uint16_t seq;
    } icmpHeader;
#else
    struct icmphdr icmpHeader;
#endif

    memset(&icmpHeader, 0, sizeof(icmpHeader));
    icmpHeader.type = 8;
    icmpHeader.code = 0;
    icmpHeader.checksum = 0;
    icmpHeader.id = htons(1234);
    icmpHeader.seq = htons(1);
    icmpHeader.checksum = checksum(&icmpHeader, sizeof(icmpHeader));

    auto start = std::chrono::high_resolution_clock::now();

    sendto(sock, &icmpHeader, sizeof(icmpHeader), 0, (sockaddr*)&addr, sizeof(addr));

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(sock, &readSet);
    timeval timeout = { 2, 0 };

    char buffer[512];
    sockaddr_in from;
#ifdef _WIN32
    int fromLen = sizeof(from);
#else
    socklen_t fromLen = sizeof(from);
#endif
    int ms = -1;

    if (select(sock + 1, &readSet, nullptr, nullptr, &timeout) > 0) {
        int received = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&from, &fromLen);
        if (received > 0) {
            auto end = std::chrono::high_resolution_clock::now();
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    return ms;
}

int udpPing(const std::string& target, int port) {
    int sock;
#ifdef _WIN32
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
    sock = socket(AF_INET, SOCK_DGRAM, 0);
#endif
    if (sock < 0) return -1;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef _WIN32
    inet_pton(AF_INET, target.c_str(), &addr.sin_addr);
#else
    inet_aton(target.c_str(), &addr.sin_addr);
#endif

    const char* msg = "fastping_test";
    sendto(sock, msg, strlen(msg), 0, (sockaddr*)&addr, sizeof(addr));

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(sock, &readSet);
    timeval timeout = { 2, 0 };

    char buffer[512];
    sockaddr_in from;
#ifdef _WIN32
    int fromLen = sizeof(from);
#else
    socklen_t fromLen = sizeof(from);
#endif
    int ms = -1;
    auto start = std::chrono::high_resolution_clock::now();

    if (select(sock + 1, &readSet, nullptr, nullptr, &timeout) > 0) {
        int received = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&from, &fromLen);
        if (received > 0) {
            auto end = std::chrono::high_resolution_clock::now();
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
    }

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    return ms;
}

int tcpPing(const std::string& target, int port) {
    int sock;
#ifdef _WIN32
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    sock = socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (sock < 0) return -1;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef _WIN32
    inet_pton(AF_INET, target.c_str(), &addr.sin_addr);
#else
    inet_aton(target.c_str(), &addr.sin_addr);
#endif

    auto start = std::chrono::high_resolution_clock::now();

#ifdef _WIN32
    u_long nonBlocking = 1;
    ioctlsocket(sock, FIONBIO, &nonBlocking);
#else
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
#endif

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);
    timeval timeout = { 2, 0 };

    int ms = -1;

    if (select(sock + 1, nullptr, &writeSet, nullptr, &timeout) > 0) {
        auto end = std::chrono::high_resolution_clock::now();
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    return ms;
}

std::vector<Target> loadTargets(const std::string& filePath) {
    std::vector<Target> targets;
    std::ifstream file(filePath);
    if (!file) return targets;

    std::string line, content;
    while (std::getline(file, line)) content += line;

    size_t pos = 0;
    while ((pos = content.find("{")) != std::string::npos) {
        size_t end = content.find("}", pos);
        if (end == std::string::npos) break;

        std::string entry = content.substr(pos, end - pos + 1);

        Target t;
        size_t ipPos = entry.find("\"target\"");
        if (ipPos != std::string::npos) {
            size_t start = entry.find("\"", ipPos + 8) + 1;
            size_t end = entry.find("\"", start);
            t.ip = entry.substr(start, end - start);
        }

        size_t portPos = entry.find("\"port\"");
        if (portPos != std::string::npos) {
            size_t start = entry.find(":", portPos) + 1;
            t.port = std::stoi(entry.substr(start));
        }

        targets.push_back(t);
        content = content.substr(end + 1);
    }

    return targets;
}

int main(int argc, char* argv[]) {
    std::string protocol, target, format = "text", batchFile;
    int port = 80;
    int intervalMs = 1000;

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

    std::signal(SIGINT, signalHandler);

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--protocol" && i + 1 < argc) protocol = argv[++i];
        else if (arg == "--target" && i + 1 < argc) target = argv[++i];
        else if (arg == "--port" && i + 1 < argc) port = std::stoi(argv[++i]);
        else if (arg == "--format" && i + 1 < argc) format = argv[++i];
        else if (arg == "--batch" && i + 1 < argc) batchFile = argv[++i];
        else if (arg == "--interval" && i + 1 < argc) intervalMs = std::stoi(argv[++i]);
    }

    if (protocol.empty()) {
        printUsage();
        return 1;
    }

    if (!batchFile.empty()) {
        auto targets = loadTargets(batchFile);
        if (targets.empty()) {
            std::cerr << "[ERROR] No valid targets in batch file.\n";
            return 1;
        }

        while (running) {
            for (const auto& t : targets) {
                int latency = -1;
                if (protocol == "icmp") latency = icmpPing(t.ip);
                else if (protocol == "udp") latency = udpPing(t.ip, t.port);
                else if (protocol == "tcp") latency = tcpPing(t.ip, t.port);

                bool success = latency >= 0;
                outputResult(protocol, t.ip, t.port, success, latency, format);

                if (!running) break;
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
            }
        }
    } else if (!target.empty()) {
        while (running) {
            int latency = -1;
            if (protocol == "icmp") latency = icmpPing(target);
            else if (protocol == "udp") latency = udpPing(target, port);
            else if (protocol == "tcp") latency = tcpPing(target, port);

            bool success = latency >= 0;
            outputResult(protocol, target, port, success, latency, format);

            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        }
    } else {
        printUsage();
        return 1;
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
