import time
import matplotlib.pyplot as plt
import numpy as np
import serial
import paho.mqtt.client as paho



serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)
x=[]

for i in range(40):
    line=s.readline()
    line=line.decode()
    print(line)
#    mqttc.publish(topic, line)
    x.append(line)