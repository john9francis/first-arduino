# -*- coding: utf-8 -*-
"""
Created on Thu Feb 29 16:34:29 2024

@author: john9
"""

import serial
import time

timeBetween = .1

N = 600

dataFile = open("./rcdata.csv", "w")

ser = serial.Serial('COM3', baudrate=9600, timeout=1)

ser.flushOutput()

print('getting started...')

i = 0


while (i < N):
    waitStart = time.time()
    
    while (time.time() - waitStart < timeBetween):
        arduinoData = ser.readline().decode('ascii')
        
    
    print(f"Datapoint: {i}: Data: {arduinoData}")
    
    writeString = str(arduinoData)
    
    writeString = writeString.replace("\n", "")
    
    dataFile.write(writeString)
    
    i += 1
    
print("done with data collection")

dataFile.close()

ser.close()