#var/lib/mpd/playlists
# simple library for raspberry pi + serialdisplay (arduino) 
# 2016/05
# octopusengine.eu
# ------------------------------
import sys, os, subprocess, time
from socket import gethostname, gethostbyname #getIp
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
  lenLim = 25 #len limit for standard font size
  s.write("W"+str(col)) # set color W or c
  s.write("R"+str(row)) 
  s.write("Q"+textString[:lenLim]+"*")   # Q string *
  sleep(0.1)
  
def sdArrQ(rStart,arrText):  # block of text (several lines) from row position / last set color 
   rr=rStart
   for row in (arrText):
     sdRQC(rr,row,1)
     rr=rr+1  
  
def sdPXYC(px,py,col): # pixel x,y + color  
  s.write("W"+str(col)) # set color W or c
  s.write("P"+str(px)) 
  s.write(","+str(py)) 
  sleep(0.05)

def sdPXY(px,py): # pixel x,y  
  s.write("P"+str(px)) 
  s.write(","+str(py)) 
  sleep(0.001)

def sdpXY(px,py): # pixel x,y  
  s.write("p"+str(px)) 
  s.write(","+str(py)) 
  sleep(0.0001)
  
#======get IP ============================
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

#====== get procesor temp ============================
def getProcTemp():  
   try:
     pytemp = subprocess.check_output(['vcgencmd', 'measure_temp'], universal_newlines=True)
     #ipoutput = subprocess.check_output(['vcgencmd measure_temp'], universal_newlines=True, 'w'))
     #print pytemp 
     eq_index = pytemp.find('=')+1 
     #if eq_index>0:
     var_name = pytemp[:eq_index].strip()
     value = pytemp[eq_index:eq_index+4]
     numvalue=float(value)
   except:
     numvalue = -1
   return numvalue 


# ====== get dallas temp ===============================
#sudo nano /boot/config.txt >> dtoverlay=w1-gpio,gpiopin=4
try:
 import glob 
 os.system('modprobe w1-gpio')
 os.system('modprobe w1-therm')
 
 base_dir = '/sys/bus/w1/devices/'
 device_folder = glob.glob(base_dir + '28*')[0]
 device_file = device_folder + '/w1_slave'

except:
 err=True
 
def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines
 
def getDallTemp(): #get dallas senson temperature
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
        return float(int(temp_c*10))/10

#-------------------------end --------------