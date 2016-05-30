#var/lib/mpd/playlists
# python test - raspberry + serialdisplay (arduino) 
# octopusengine.eu

import random, sys, os, time
from time import sleep

from octopusEngineHWlib import *

#-------------------------main test --------------
sdW("C") #clear
sdRQC(0,"Serial Display",7)
sdW("h35")
sdW("h200")
sdRQC(10,"octopusengine.lib",7)

sdW("W5h150")

sleep(1)

txt="> ip: "+getIp()
print txt
#s.write("R7Q"+txt+"*") = sdW.. =
sdRQC(2,txt,2)

sdRQC(7,"temperature:",1)

tt=1
while True:
        
        t=getDallTemp()
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

     














