#var/lib/mpd/playlists
# simple library for raspberry pi + serialdisplay (arduino) 
# 2016/05
# octopusengine.eu
# ------------------------------
import sys, os, time
from time import sleep

# ======tft serial monitor====================
import serial
s = serial.Serial(port='/dev/ttyAMA0',baudrate=9600,                                                   
            timeout=3.0,
            xonxoff=False, rtscts=False, 
            writeTimeout=3.0,
            dsrdtr=False, interCharTimeout=None)
# ===============================================
def sdW(textString):    # simple command write  
  s.write(textString)   # 
  sleep(0.1)

def sdRQC(row,textString,col): # row position + string + color  
  s.write("W"+str(col)) # set color W or c
  s.write("R"+str(row)) 
  s.write("Q"+textString+"*")   # Q string *
  sleep(0.1)

def sdPXYC(px,py,col): # pixel x,y + color  
  s.write("W"+str(col)) # set color W or c
  s.write("P"+str(px)) 
  s.write(","+str(py)) 
  sleep(0.1)

def sdPXY(px,py): # pixel x,y  
  s.write("P"+str(px)) 
  s.write(","+str(py)) 
  sleep(0.05)


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


# ======dallas====================================
try:
 import glob 
 os.system('modprobe w1-gpio')
 os.system('modprobe w1-therm')
 
 base_dir = '/sys/bus/w1/devices/'
 device_folder = glob.glob(base_dir + '28*')[0]
 device_file = device_folder + '/w1_slave'
 
 def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines
 
 def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.1) #0.2 ok
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0 / 5.0 + 32.0
        #return temp_c, temp_f
        return temp_c
except:
 err=True


#-------------------------end --------------
