<<<<<<< HEAD
import paho.mqtt.client as mqtt
from urllib import parse, request
import time
import math
import requests

val1=float(0.0)
val2=float(0.0)
# The callback for whem the client recieves a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("/ITESM/PUEBLA/temperature")
    client.subscribe("/ITESM/PUEBLA/humidity")
    
# The callback for when a PUBLISH message is recieved from the ESP8266.
def on_message(client, userdata, msg):
    if msg.topic == "/ITESM/PUEBLA/temperature":
        str0 = str(msg.payload)
        str1=str0[3:7]
        global val1
        val1=float(str1)
        print("Received message: " + msg.topic + "  "  + str1 + "ºC"  )

    if msg.topic == "/ITESM/PUEBLA/humidity":
        str2 = str(msg.payload)
        str3=str2[3:7]
        global val2
        val2=float(str3)
        print("Received message: " + msg.topic + "  "  + str3 + "%" )    
        
Token = "BBFF-9PfHxzOo6an0VKuy1hMqxZ1rEkkeio"
Device_label = "GM_WIN10"
varl1= "Temperature"
varl2= "Humidity"


def build_payload(var1,var2):
   
    payload = {var1: val1,var2: val2}
    return payload
    
def post_request(payload):
    url = "http://things.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, Device_label)
    headers = {"X-Auth-Token": Token, "Content-Type": "application/json"}
    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, json=payload)
        status = req.status_code
        attempts +=  1
    if status >= 400:
        return False
    print("[INFO] REQUEST MADE PROPERLY, YOUR device is updated")
    return True

def main():
    payload = build_payload(varl1,varl2)
    print("[INFO] Attemping to send data")
    post_request(payload)

if __name__ == '__main__':
    c=0
    while (True):
        if c==0:
            mqttc=mqtt.Client()
            mqttc.on_connect = on_connect
            mqttc.on_message = on_message
            mqttc.connect("localhost",1883,60)
            mqttc.loop_start()
            time.sleep(10)
            main()
            c=1
        elif c==1:

            mqttc.on_message = on_message
            main()
            time.sleep(5)
=======
import paho.mqtt.client as mqtt
from urllib import parse, request
import time
import math
import requests

val1=float(0.0)
val2=float(0.0)
# The callback for whem the client recieves a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("/ITESM/PUEBLA/temperature")
    client.subscribe("/ITESM/PUEBLA/humidity")
    
# The callback for when a PUBLISH message is recieved from the ESP8266.
def on_message(client, userdata, msg):
    if msg.topic == "/ITESM/PUEBLA/temperature":
        str0 = str(msg.payload)
        str1=str0[3:7]
        global val1
        val1=float(str1)
        print("Received message: " + msg.topic + "  "  + str1 + "ºC"  )

    if msg.topic == "/ITESM/PUEBLA/humidity":
        str2 = str(msg.payload)
        str3=str2[3:7]
        global val2
        val2=float(str3)
        print("Received message: " + msg.topic + "  "  + str3 + "%" )    
        
Token = "BBFF-9PfHxzOo6an0VKuy1hMqxZ1rEkkeio"
Device_label = "GM_WIN10"
varl1= "Temperature"
varl2= "Humidity"


def build_payload(var1,var2):
   
    payload = {var1: val1,var2: val2}
    return payload
    
def post_request(payload):
    url = "http://things.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, Device_label)
    headers = {"X-Auth-Token": Token, "Content-Type": "application/json"}
    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, json=payload)
        status = req.status_code
        attempts +=  1
    if status >= 400:
        return False
    print("[INFO] REQUEST MADE PROPERLY, YOUR device is updated")
    return True

def main():
    payload = build_payload(varl1,varl2)
    print("[INFO] Attemping to send data")
    post_request(payload)

if __name__ == '__main__':
    c=0
    while (True):
        if c==0:
            mqttc=mqtt.Client()
            mqttc.on_connect = on_connect
            mqttc.on_message = on_message
            mqttc.connect("localhost",1883,60)
            mqttc.loop_start()
            time.sleep(10)
            main()
            c=1
        elif c==1:

            mqttc.on_message = on_message
            main()
            time.sleep(5)
>>>>>>> 5698e477a19cc9894495aee30c37483c559f9ea6
