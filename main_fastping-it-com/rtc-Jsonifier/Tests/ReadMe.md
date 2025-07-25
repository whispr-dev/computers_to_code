# Json-Performance
Performance profiling of JSON libraries (Compiled and run on Ubuntu-22.04 using the Clang++19 compiler)

Latest Results: (Sep 08, 2024)
#### Using the following commits:
----
| Jsonifier: [](https://github.com/RealTimeChris/Jsonifier/commit/)  
| Glaze: [a4e9697](https://github.com/stephenberry/glaze/commit/a4e9697)  
| Simdjson: [70a68da](https://github.com/simdjson/simdjson/commit/70a68da)  

 > At least 30 iterations on a (Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz        ), until coefficient of variance is at or below 1%.


### Json Test (Prettified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/JsonData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Json%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Json%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 131.579 | 1695711 | 1.28874e+07 | 101 | 165.584 | 1695711 | 1.02408e+07 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 101.234 | 1693978 | 1.67332e+07 | 101 | 176.406 | 1693978 | 9.60272e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 17.5394 | 1697728 | 9.67951e+07 | 101 | 

### Json Test (Minified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/JsonData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Json%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Json%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 154.562 | 1387574 | 8.97746e+06 | 101 | 216.873 | 1387574 | 6.3981e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 147.819 | 1385841 | 9.37529e+06 | 101 | 183.448 | 1385841 | 7.55441e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 15.6424 | 1389591 | 8.8835e+07 | 101 | 

### ABC Test (Out of Sequence Performance - Prettified) [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/JsonData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Abc%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Abc%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>

The JSON documents in the previous tests featured keys ranging from "a" to "z," where each key corresponds to an array of values. Notably, the documents in this test arrange these keys in reverse order, deviating from the typical "a" to "z" arrangement.

This test effectively demonstrates the challenges encountered when utilizing simdjson and iterative parsers that lack the ability to efficiently allocate memory locations through hashing. In cases where the keys are not in the expected sequence, performance is significantly compromised, with the severity escalating as the document size increases.

In contrast, hash-based solutions offer a viable alternative by circumventing these issues and maintaining optimal performance regardless of the JSON document's scale, or ordering of the keys being parsed.

| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 150.684 | 1695711 | 1.12534e+07 | 101 | 210.652 | 1695711 | 8.04983e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 138.187 | 1693978 | 1.22586e+07 | 101 | 211.546 | 1693978 | 8.00759e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 15.6584 | 1697728 | 1.08423e+08 | 101 | 

### ABC Test (Out of Sequence Performance - Minified) [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/JsonData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Abc%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Abc%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 150.32 | 1387574 | 9.23083e+06 | 101 | 224.882 | 1387574 | 6.17023e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 138.221 | 1385841 | 1.00263e+07 | 101 | 235.736 | 1385841 | 5.87878e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 14.6338 | 1389591 | 9.49576e+07 | 101 | 

### Discord Test (Prettified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/DiscordData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Discord%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Discord%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 148.296 | 138774 | 935791 | 101 | 281.087 | 138774 | 493705 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 108.631 | 138774 | 1.27748e+06 | 101 | 346.928 | 138774 | 400008 | 97 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 1.85943 | 138774 | 7.46326e+07 | 101 | 

### Discord Test (Minified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/DiscordData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Discord%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Discord%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 103.073 | 69037 | 669788 | 101 | 181.886 | 69037 | 379561 | 96 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 77.1309 | 69037 | 895063 | 101 | 243.007 | 69037 | 284094 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 0.937744 | 69037 | 7.36203e+07 | 101 | 

### Canada Test (Prettified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/CanadaData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Canada%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Canada%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 82.6165 | 6661897 | 8.06364e+07 | 101 | 76.1061 | 6661897 | 8.75344e+07 | 101 | 
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 65.9626 | 6661897 | 1.00995e+08 | 101 | 71.8747 | 6661897 | 9.26877e+07 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 22.2276 | 6661897 | 2.99713e+08 | 101 | 

### Canada Test (Minified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/CanadaData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Canada%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Canada%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 30.4413 | 2090234 | 6.86644e+07 | 101 | 32.7027 | 2090234 | 6.39163e+07 | 101 | 
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 26.9047 | 2090234 | 7.76903e+07 | 101 | 31.9009 | 2090234 | 6.55227e+07 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 9.14904 | 2090234 | 2.28465e+08 | 101 | 

### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/CitmCatalogData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/CitmCatalog%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/CitmCatalog%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 182.216 | 1439562 | 7.90029e+06 | 101 | 334.738 | 1439562 | 4.30056e+06 | 101 | 
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 180.481 | 1439584 | 7.97638e+06 | 101 | 320.374 | 1439584 | 4.49345e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 0.00890164 | 222 | 2.49392e+07 | 101 | 

### CitmCatalog Test (Minified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/CitmCatalogData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/CitmCatalog%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/CitmCatalog%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 91.3162 | 500299 | 5.47876e+06 | 101 | 116.829 | 500299 | 4.28233e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 76.0128 | 500299 | 6.58177e+06 | 101 | 169.269 | 500299 | 2.95565e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 0.0177597 | 222 | 1.25002e+07 | 101 | 

### Twitter Test (Prettified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/TwitterData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Twitter%20Test%20(Prettified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Twitter%20Test%20(Prettified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 143.944 | 727702 | 5.05544e+06 | 101 | 223.97 | 727702 | 3.24911e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 83.6923 | 727793 | 8.69606e+06 | 101 | 226.314 | 727793 | 3.21585e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 3.83198 | 726755 | 1.89655e+08 | 101 | 

### Twitter Test (Minified) Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/TwitterData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Twitter%20Test%20(Minified)_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Twitter%20Test%20(Minified)_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 100.014 | 482009 | 4.81939e+06 | 101 | 213.702 | 482009 | 2.25552e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 75.7909 | 482100 | 6.36092e+06 | 101 | 292.396 | 482100 | 1.64879e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 2.10454 | 481062 | 2.28583e+08 | 101 | 

### Minify Test Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/DiscordData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Minify%20Test_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Minify%20Test_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ------------ | -------------------- | --------------- | --------------------- |   
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 72.9281 | 69037 | 946645 | 101 | 
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 53.9609 | 69037 | 1.27939e+06 | 101 | 
| [simdjson](https://github.com/simdjson/simdjson/commit/70a68da) | 6.05005 | 69037 | 1.1411e+07 | 101 | 

### Prettify Test Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/DiscordData-Minified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Prettify%20Test_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Prettify%20Test_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Write (MB/s) | Write Length (Bytes) | Write Time (ns) | Write Iteration Count |
| ------- | ------------ | -------------------- | --------------- | --------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 331.183 | 1695771 | 5.12034e+06 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 234.712 | 1695771 | 7.22489e+06 | 101 | 

### Validation Test Results [(View the data used in the following test)](https://github.com/RealTimeChris/Json-Performance/blob/main/Json/DiscordData-Prettified.json):

----
<p align="left"><a href="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Validate%20Test_Results.png" target="_blank"><img src="https://github.com/RealTimeChris/Json-Performance/blob/main/Graphs/Validate%20Test_Results.png?raw=true" 
alt="" width="400"/></p>


| Library | Read (MB/s) | Read Length (Bytes) | Read Time (ns) | Read Iteration Count |
| ------- | ----------- | ------------------- | -------------- | -------------------- |   
| [glaze](https://github.com/stephenberry/glaze/commit/a4e9697) | 180.723 | 138774 | 767884 | 101 | 
| [jsonifier](https://github.com/realtimechris/jsonifier/commit/) | 144.755 | 138774 | 958685 | 101 | 