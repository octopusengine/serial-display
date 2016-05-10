#var/lib/mpd/playlists
# python test - raspberry + serialdisplay (arduino) 
# octopusengine.eu

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
# ===============================================
def sdRQC(row,textString,col): # row position + string + color  
  s.write("W"+str(col)) # set color W or c
  s.write("R"+str(row)) 
  s.write("Q"+textString+"*")   # Q string *
  sleep(0.1)

from socket import gethostname, gethostbyname #getIp
import subprocess
def getIp():
   try:
    arg='ip route list'
    p=subprocess.Popen(arg,shell=True,stdout=subprocess.PIPE)
    data = p.communicate()
    split_data = data[0].split()
    ipaddr = split_data[split_data.index('src')+1]
   except:
     ipaddr ="ip.Err"
   #print "ip: " ip
   return ipaddr

#-------------------------main test --------------
s.write("C") #clear
sdRQC(0,"Serial Display",7)
s.write("h35")
s.write("h200")
sdRQC(10,"octopusengine.eu",7)
sleep(1)

sdRQC(2,"raspberry pi test",1)
sdRQC(5,"IP address:",1)
sleep(1)

txt="> ip: "+getIp()
print txt
#s.write("R7Q"+txt+"*")
sdRQC(6,txt,2)
     
#================================================
print "test ok - end"














