#!/usr/bin/python
# -*- encoding: utf-8 -*-

import time               
import urllib2             

try:    
    # response = urllib2.urlopen('http://tethys.cz/3dwarf?k=test1')
    response = urllib2.urlopen('http://sentu.cz/get/datetime.php') 
    urlTxt = response.read()
    response.close() 
except:
    urlTxt= "url read err"

print "date time: " , urlTxt 

