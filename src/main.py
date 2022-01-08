from flask import Flask, render_template
import json

settings = json.load(open("settings"))

app = Flask(__name__)

@app.route("/")
def home():
      return render_template("index.html")

if __name__ == "__main__":
      app.run(host="localhost", port=(settings['port'] if 'port' in settings else 8080));