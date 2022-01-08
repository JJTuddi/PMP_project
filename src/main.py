from flask import Flask
from flask_restful import API, Api, Resource
import json

settings = json.load(open("settings"))

app = Flask(__name__)
api = Api(app)

myObj = {"ledStrip": "led strip", "avem": "navem", "object": {
                  "id": 1,
                  "innerObject": {
                        "name": "inner"
                  },
                  "name": "outerObject - object"
            }}
class LedStrip(Resource):
      def get(self):
            print("get was accessed")
            return myObj
      def put(self):
            print("put was accessed")
            return {
                  "function": "PUT",
                  "result": myObj
            }
      def post(self):
            print("post was accessed")
            return {
                  "function": "POST",
                  "result": myObj
            }
      def delete(self):
            print("delete was accessed")
            return {
                  "function": "DELETE",
                  "result": myObj
            }

@app.route("/")
def home():
      return open("website/index.html", "r").read()

api.add_resource(LedStrip, "/led-strip")

if __name__ == "__main__":
      app.run(host="0.0.0.0", port=(settings['port'] if 'port' in settings else 8080));