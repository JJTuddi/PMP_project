from flask import Flask
from flask_restful import Api, Resource
import json
#Raspberry pins setup
from gpiozero import LED
from time import sleep
INTERRUPT_PIN = 25
INTERRUPT_B0 = 23
INTERRUPT_B1 = 24

interruptPin = LED(INTERRUPT_PIN)
interruptPin.off()
b0Pin = LED(INTERRUPT_B0)
b0Pin.off()
b1Pin = LED(INTERRUPT_B1)
b1Pin.off()
bPinArray = [b0Pin, b1Pin]

animationNumber = {"Mid": 1, "Horizontal": 0, "Front": 2}
settings = json.load(open("settings"))

def numberToPin(number, b):
    tempNumber = number
    for bPin in b:
        if tempNumber % 2 == 1:
            bPin.on()
        tempNumber //= 2

def turnOffPins(pins):
      [pin.off() for pin in pins]

app = Flask(__name__)
api = Api(app)

class LedStrip(Resource):
      def put(self, animation):
            print(animation)
            numberToPin(animationNumber[animation], bPinArray)
            sleep(0.01)
            interruptPin.on()
            sleep(0.1)
            turnOffPins([interruptPin] + bPinArray)
            return {"status": "oke"}

@app.route("/")
def home():
      return open("website/index.html", "r").read()

api.add_resource(LedStrip, "/led-strip/<string:animation>")

if __name__ == "__main__":
      app.run(host="0.0.0.0", port=(settings['port'] if 'port' in settings else 8080));