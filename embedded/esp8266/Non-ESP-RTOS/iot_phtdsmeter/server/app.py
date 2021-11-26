from flask import Flask, render_template,Response,jsonify,send_file
from flask import request
import datetime
import os

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/data")
def value():
    try:
        with open("data.csv", "r") as f:
            data = [val.strip().split("#") for val in f.readlines()]
    except:
        data = []
    return jsonify(data)

@app.route("/reset")
def reset():
    try:
        with open("data.csv", "w") as f:
            f.write("")
        status = "OK"
    except:
        status = "Fail"
    return jsonify({"status" : status})

@app.route("/<val1>/<val2>/<val3>/<val4>/")
def data(val1, val2, val3, val4):
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open("data.csv", "a") as f:
        f.write(f"{now}#{val1}#{val2}#{val3}#{val4}\n")
    return jsonify({"status" : "received"})

if __name__ == '__main__':
    app.run(host="0.0.0.0" ,port=9000, debug=True,threaded=True, use_reloader=False)
