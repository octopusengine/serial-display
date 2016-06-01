#var/lib/mpd/playlists
# python test - raspberry + serialdisplay (arduino) 
# octopusengine.eu

import random, sys, os, time
from time import sleep

from octopusEngineHWlib import *


#======================
import pygame
pygame.init()
sizeWinX=800
sizeWinY=600
window = pygame.display.set_mode([sizeWinX,sizeWinY])  # Create the pygame window
pygame.display.set_caption("graf")        

colYel = (255,255,0)
colWhi = (255,255,255)
colRed = (255,0,0)
colBlu = (0,0,255)
colSil = (128,128,128)
colBla = (0,0,0)

hBod=3
hX=30   #pozice
hY=30
hA=240 #matice
hB=180
hW=hA*hBod #velikost
hH=hB*hBod

# Creates a list containing 5 lists initialized to 0
# myMatrix = [[0 for x in xrange(hA)] for x in xrange(hB)] 

def doGrafInit():
    pygame.draw.line(window,colSil,(hX,hY),(hX,hY+hH),2)
    pygame.draw.line(window,colSil,(hX,hY+hH),(hX+hW,hY+hH),2)
    pygame.draw.line(window,colSil,(hX+hW,hY+hH),(hX+hW,hY),2)
    pygame.draw.line(window,colSil,(hX+hW,hY),(hX,hY),2)
    pygame.display.flip()
# 
#-------------------------main test --------------
doGrafInit()

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

for l in range(0,60,10):
	pygame.draw.line(window,colSil,(hX,hY+(sy-l*nast)),(hX+hW,hY+(sy-l*nast)),1)

while True:
	try:
		td=getDallTemp()
	except:
		td=20
		
  tp=getProcTemp()
  print(str(td),str(tp))
  sdRQC(8,"temp: "+str(td)+" "+str(tp),2)

  px=(int(tt/nas))
  py=sy-td*nast
  sdPXYC(px,py,1)

  pygame.draw.line(window,colWhi,(hX+px,hY+py),(hX+px+1,hY+py),hBod)
  

  px=(int(tt/nas))
  py=sy-tp*nast
  sdPXYC(px,py,3)

  pygame.draw.line(window,colRed,(hX+px,hY+py),(hX+px+1,hY+py),hBod)

  pygame.display.flip() 


  time.sleep(0.1)
  tt=tt+1

  if tt>320*nas: tt=1

