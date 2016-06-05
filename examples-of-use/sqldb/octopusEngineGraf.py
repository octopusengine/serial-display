#!/usr/bin/python
# -*- coding: utf-8 -*-

#======================
import pygame
    

colYel = (255,255,0)
colWhi = (255,255,255)
colRed = (255,0,0)
colBlu = (0,0,255)
colSil = (128,128,128)
colBla = (0,0,0)


sizeWinX=800
sizeWinY=600

hX=30   #pozice
hY=30
sY=sizeWinY-hY #startY
hW=sizeWinX-2*hX
hH=sizeWinY-2*hY

hBod=3

# Creates a list containing 5 lists initialized to 0
# myMatrix = [[0 for x in xrange(hA)] for x in xrange(hB)] 

pygame.init()

window = pygame.display.set_mode([sizeWinX,sizeWinY])  # Create the pygame window


def doGrafInit():
	global window      	
	window = pygame.display.set_mode([sizeWinX,sizeWinY])  # Create the pygame window
	pygame.display.set_caption("graf") 

	pygame.draw.line(window,colSil,(hX,hY),(hX,hY+hH),2)
	pygame.draw.line(window,colSil,(hX,hY+hH),(hX+hW,hY+hH),2)
	pygame.draw.line(window,colSil,(hX+hW,hY+hH),(hX+hW,hY),2)
	pygame.draw.line(window,colSil,(hX+hW,hY),(hX,hY),2)
	pygame.display.flip()
 
#---/grafInit


def strDat2num(datum):
  #intdat = int(row[1][5:7])*31+int(row[1][8:10])
  try:
  	intdat = int(datum[5:7])*31+int(datum[8:10])
  except:
        intdat = 0
  return intdat

def grafBod(px,py):
  pygame.draw.line(window,colRed,(hX+px,sY-py),(hX+px+1,sY-py),hBod)
  
#------------------------------------/end-------------------------










   

