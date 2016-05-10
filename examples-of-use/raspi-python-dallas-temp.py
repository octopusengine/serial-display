#var/lib/mpd/playlists
# python test - raspberry + serialdisplay (arduino) 
# octopusengine.eu

import random, sys, os, time
from time import sleep

from octopusEngineHWlib import *

# 
#-------------------------main test --------------
s.write("C") #clear
sdRQC(0,"Serial Display",7)
s.write("h35")
s.write("h200")
sdRQC(10,"octopusengine.eu",7)

s.write("W5h150")

sleep(1)

#sdRQC(2,"raspberry pi test",1)
#sdRQC(4,"IP addres:",1)
#sleep(1)

txt="> ip: "+getIp()
print txt
#s.write("R7Q"+txt+"*")
sdRQC(2,txt,2)

#sdRQC(7,"temperature:",1)
     
#================================================
print "test ok - end"

tt=1
while True:
        
        t=read_temp()
	print(str(t))
        sdRQC(8,"temp: "+str(t),2)
    
        #s.write("W3P")
        #s.write(str(int(tt/2)))
        #s.write(",")
        px=str(int(tt/2))
        py=150-t*2
	#s.write(str(gt))
	sdPXYC(px,py,3)

        time.sleep(0.1)
        tt=tt+1

        if tt>320: tt=1

