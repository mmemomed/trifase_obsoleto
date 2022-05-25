<<<<<<< HEAD
import paho.mqtt.client as mqtt
from urllib import parse, request
import time
import math
import requests

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("/ITESM/PUEBLA/temperature")
    client.subscribe("/ITESM/PUEBLA/humidity")   

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
        
mqttc=mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.connect("localhost",1883,60)
=======
import paho.mqtt.client as mqtt
from urllib import parse, request
import time
import math
import requests

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("/ITESM/PUEBLA/temperature")
    client.subscribe("/ITESM/PUEBLA/humidity")   

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
        
mqttc=mqtt.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.connect("localhost",1883,60)
>>>>>>> 5698e477a19cc9894495aee30c37483c559f9ea6
mqttc.loop_start()