# /home/wofl/fastping.it.com/app.py
from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello():
    return 'Proxy test active fren!'

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)
