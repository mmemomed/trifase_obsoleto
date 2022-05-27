import serial
import time 
import collections
import matplotlib.pyplot as pit
import matplotlibr.animation as animation
from matplotlib.line import Line2D
import numpy as np

def getSerialData(self, Samles, numData, SerialConnection, Lines):
    for i in range(numdata):
        value = float (serialConnection.readline().strip())
        data[i].append(value)
        lines[i].set_data(range(Samples),data[i])

# HAY QUE CREAR UNA MANERA DE DETECTAR A QUE PUERTO ESTÁ CONECTADO EL ARCHIVO

baudRate = 115200

try:
    serialConnection = serial.Serial(serialPort, baudRate)
except:
    print("No se estableció conexión en el puerto")

#Definición de variables para la recolección de datos
Samples = 1200
sampleTime = 200
numData = 6

#Límites de los ejes
xmin = 0
xmax = Samples
ymin = [0,0]