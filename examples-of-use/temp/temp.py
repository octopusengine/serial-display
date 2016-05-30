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
sy=215
nas=2
nast=3

s.write("W7")
s.write("h")
s.write(str(sy-20*nast))
s.write("h")
s.write(str(sy-30*nast))
s.write("h")
s.write(str(sy-40*nast))



while True:
  td=getDallTemp()
  tp=getProcTemp()
  print(str(td),str(tp))
  sdRQC(8,"temp: "+str(td)+" "+str(tp),2)
    
  px=str(int(tt/nas))
  py=sy-td*nast
  sdPXYC(px,py,1)

  px=str(int(tt/nas))
  py=sy-tp*nast
  sdPXYC(px,py,3)


  time.sleep(0.1)
  tt=tt+1

  if tt>320*nas: tt=1

