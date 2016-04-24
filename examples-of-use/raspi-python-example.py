#using serial display as a terminal for RaspberryPi
import random, sys, os, time
from time import sleep

# ===============================================
#---tft serial monitor
import serial
s = serial.Serial(port='/dev/ttyAMA0',baudrate=9600,                                                   
            timeout=3.0,
            xonxoff=False, rtscts=False, 
            writeTimeout=3.0,
            dsrdtr=False, interCharTimeout=None)

#simple display string on the "terminal"
def sdQ(row,string,color):
  s.write("W"+str(color))
  s.write("R"+str(row))
  s.write("Q"+string+"*")

#s.write("CR0W7QoeRadio*")
s.write("C")      #clear

sdQ(0,"oeRadio 2",7)
s.write("h35")    #horizontal line
s.write("h200")   #horizontal line
s.write("R10Qoctopusengine.eu*")
# ===============================================
newCmd=False

#co="> ip: "+getIp()
#print co
#sdQ(7,co,1)

#================================================












