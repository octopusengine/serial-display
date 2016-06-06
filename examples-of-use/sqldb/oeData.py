#!/usr/bin/python
# -*- coding: utf-8 -*-
# http://octopusengine.eu/sqlitedisplay
# http://zetcode.com/db/sqlitepythontutorial/
#------------------------------------------------------
# :::todo:::
# input/insert csv --- csvout, csvin
# export xml --- xmlout, xmlin
# upload ftp --- ftpout, ftpin
#------------------------------------------------------

import sqlite3 as lite
import os, sys, time, datetime
from time import strftime
from octopusEngineHWlib import * #display
from octopusEngineGraf import  * #pygame graf

#======================

sel = "none"
ffile = 'data16' # .db
table = "temp"
#sele="nic"

ramdiskPath = "/home/pi/ramdisk/"
seleConf= ramdiskPath+"table.ini"
fileConf= ramdiskPath+"file.ini"

print "------------------init"
print int(time.time())
s.write("C") #clear
sleep(0.1)

sdRQC(0,"Serial Display - sqlite",7)

con = lite.connect(ffile+'.db')

if not os.path.exists(fileConf):
  fs = open(fileConf,"w")
  fs.write(ffile)
  fs.close()
else: 
  fs = open(fileConf,"r")
  ffile=fs.read()
  fs.close()  

if not os.path.exists(seleConf):
  fs = open(seleConf,"w")
  fs.write(table)
  fs.close()
else: 
  fs = open(seleConf,"r")
  table=fs.read()
  fs.close()

print ("> db file: "+ ffile )
print ("> table use / sele: "+ table )

try:  
  sel=str(sys.argv[1])
  #name="robot" 	#scanning object name
except: 
   name="noname"
   print ("sel: "+ sel )

if sel=="help":
    print ("help 123 ")
    sys.exit()
    #err.stop
else:
    print ("First argument > sel: "+ sel )
#con = None

# "----------------------------------------temp"      
if sel=="temp":
  kolik=10
  argA="t1"
  try:
    kolik=int(sys.argv[2]) 
    nic=True
  except:
    print "kolik " + str(kolik)
  
  with con:
		cur = con.cursor()  
		for i in range(kolik):  
			id=str(int(time.time())) 
			ptemp=str(getProcTemp())
			dtemp=str(getDallTemp())
			print i, id, dtemp, ptemp  
     
			#ok cur.execute("INSERT INTO "+table+" (id,type,text,r1,r2) VALUES("+id+",'nic','t1',1.23,2.56)") 
			cur.execute("INSERT INTO "+table+" (id,type,text,r1,r2) VALUES("+id+",'nic','t1',"+dtemp+","+ptemp+")") 
			time.sleep(2)

# "----------------------------------------file"      
if sel=="file":
  try:
    ffile=str(sys.argv[2]) 
    print "second argument: " + ffile
    fs = open(fileConf,"w")
    fs.write(ffile)
    fs.close()
  except:
    print "file - second argument?"
    sys.exit(1)  
        
# "----------------------------------------use/sele/table"      
if sel=="sele" or sel=="use":
  try:
    table=str(sys.argv[2]) 
    print "second argument: " + table
    fs = open(seleConf,"w")
    fs.write(table)
    #fws.write("sub"+str(cntx))
    fs.close()
  except:
    print "second argument?"
    sys.exit(1)      
  
  

print "----------------------------------------start" 
con = lite.connect(ffile+'.db')      
cur = con.cursor() 

# "----------------------------------------crea 
if sel=="crea":
	cur.execute("CREATE TABLE "+table+"(id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Price INT)")
	con.close()

if sel=="crea2":
	cur.execute("CREATE TABLE "+table+"(id INTEGER, type TEXT, text TEXT, r1 REAL ,r2 REAL, i3 INTEGER)")
	con.close()

if sel=="crea3":
	cur.execute("CREATE TABLE "+table+"(id INTEGER PRIMARY KEY AUTOINCREMENT, datum TEXT, popis TEXT, val1 INT, val2 INT, val3 int, jin TEXT )")
	con.close()

# "----------------------------------------add 
if sel=="add1":	
  try:
    argA=str(sys.argv[2]) 
    #argB=str(sys.argv[3])     
  except:
    print "second argument?"
    sys.exit(1)  
 
  with con:
	 cur = con.cursor() 
	 cur.execute("INSERT INTO "+table+" (Name,Price) VALUES('"+argA+"',0)") 	
	
if sel=="addt":	#pro temp
  try:
    argA=str(sys.argv[2]) 
    #argB=str(sys.argv[3])     
  except:
    print "second argument?"
    sys.exit(1)  
 
  with con:
	 id=str(int(time.time()))  
	 cur = con.cursor() 
	 cur.execute("INSERT INTO "+table+" (id,type,text,r1) VALUES('"+id+"','nic','"+argA+"',1.23)") 	
	
	
if sel=="add":	
  try:
    argA=str(sys.argv[2]) 
    #argB=str(sys.argv[3])     
  except:
    print "second argument?"
    sys.exit(1)  
 
  with con:
	 cur = con.cursor() 
	 cur.execute("INSERT INTO "+table+" VALUES(2,'"+argA+"',0)") 
	 
	 #cur.execute("INSERT INTO Cars VALUES(2,'Volvo567',29000)")
	   
    #sql="INSERT INTO "+table+" VALUES(9,'"+argA+"',200)"
    #cur.execute("INSERT INTO "+table+" VALUES(2,'Volvo123',29000)") 
    #cur.execute("INSERT INTO "+table+" VALUES(2,pok,29000)") 
    
    
    #sql="INSERT INTO Cars VALUES(9,'Volkswagen9',21600)"
    #print sql
    #if cur.execute(sql):
    #	 print "insert ok"
  
 
    #cur.execute("INSERT INTO  VALUES(2,'Volvo123',29000)") 
    #con.close()
 
if sel=="addb":	#pro crea3 bitcoins
  try:
    argDat=str(sys.argv[2]) 
    argTxt=str(sys.argv[3])  
    argVal1=str(sys.argv[4])  
    #argVal2=str(sys.argv[5])    
    #argVal3=str(sys.argv[6])     
  except:
    print "5 arguments?"
    sys.exit(1)  
 
  with con:
	 cur = con.cursor() 
	 cur.execute("INSERT INTO "+table+" (datum,popis,val1) VALUES('"+argDat+"','"+argTxt+"','"+argVal1+"')") 
	 
	
if sel=="insert":	
  with con:
    cur = con.cursor()    
    cur.execute("INSERT INTO Cars VALUES(1,'Audi',52642)")
    cur.execute("INSERT INTO Cars VALUES(2,'Mercedes',57127)")
    cur.execute("INSERT INTO Cars VALUES(3,'Skoda',9000)")
 
# "----------------------------------------list 
    
if sel=="list1":
  cur.execute("SELECT * FROM "+table)
  rows = cur.fetchall()
  for row in rows:
        print row   
        
if sel=="list2":
  with con:
    cur = con.cursor()    
    cur.execute("SELECT * FROM "+table)

    while True:
      
        row = cur.fetchone()
   
        if row == None:
            break
        print row[0], row[1] #, row[2]


if sel=="list3":
#The default cursor returns the data in a tuple of tuples. 
#When we use a dictionary cursor, the data is sent 
#in the form of Python dictionaries. 
#This way we can refer to the data by their column names.

  #con = lite.connect('test.db')    

  with con:
    
    con.row_factory = lite.Row
       
    cur = con.cursor() 
    cur.execute("SELECT * FROM "+table)

    rows = cur.fetchall()

    for row in rows:
        print "%s %s %s" % (row["Id"], row["Name"], row["Price"])
        
        
if sel=="listt":
  with con:    
    con.row_factory = lite.Row
       
    cur = con.cursor() 
    cur.execute("SELECT * FROM "+table)

    rows = cur.fetchall()

    for row in rows:
		#cas= str(row["id"])
		#datetime.fromtimestamp(int("1284101485")).strftime('%Y-%m-%d %H:%M:%S')
		#datName=name+datetime.now().strftime("%Y_%m_%d_%H_%M") 
		#cas= str(time.mktime(row["id"]))
		intid=int(str(row["id"]))
		cas= str(datetime.datetime.utcfromtimestamp(intid).strftime('%y/%m/%d %H:%M:%S'))
		print "%s %s %s %s" % (cas, row["text"], row["r1"], row["r2"])       
        
        
if sel=="displ":
  linesFile=[] 	
  with con:    
    con.row_factory = lite.Row
       
    cur = con.cursor() 
    cur.execute("SELECT * FROM "+table)

    rows = cur.fetchall()
    
    
    for row in rows:
        print "%s %s %s" % (row["Id"], row["Name"], row["Price"]) 
        linesFile.append(str(row["Id"])+ " - "+str(row["Name"])+ " "+ str(row["Price"]))
              
  sdArrQ(1,linesFile)    



if sel=="listb": #pro bitcoin
  cur.execute("SELECT * FROM "+table +" ORDER BY datum")
  rows = cur.fetchall()
  for row in rows:
        print row 


if sel=="grafb": #pro bitcoin  
  doGrafInit()

  cur.execute("SELECT * FROM "+table +" ORDER BY datum")
  rows = cur.fetchall()
  px=10

  pxOld=0
  pyOld=0

  for row in rows:
        
        #print row ##ok
        #print px, row[1], #datum
        #intdat = int(row[1][5:7])*31+int(row[1][8:10])
        intdat = strDat2num(row[1])

        #px=px+10
        px=intdat*2
        print intdat


        #print int(row[3])
        py = int(row[3])/2
        print px,py
        
        #pygame.draw.line(window,colRed,(hX+px,hY+py),(hX+px+1,hY+py),hBod)
        
        pygame.draw.line(window,colBlu,(hX+pxOld,sY-pyOld),(hX+px,sY-py),1)
        grafBod(px,py)

        pxOld=px
        pyOld=py

        pygame.display.flip() 

  time.sleep(3) 
 
# "----------------------------------------dele id / all / drop"         
        
if sel=="dele":
  try:
    delid=int(sys.argv[2])    
    
    with con:
      cur = con.cursor() 
      cur.execute("DELETE FROM "+table+" WHERE Id="+str(delid))
      print "dele id "+ str(delid) + " .ok" 
    
  except:
    print "Err. second argument? ID integer"
    sys.exit(1) 

if sel=="deleall":
	with con:
	  cur = con.cursor() 
	  cur.execute("DELETE FROM "+table+" WHERE Id>0")
	#con.close()
	print "OK. delete all"

if sel=="drop":
	cur.execute("DROP TABLE IF EXISTS "+table)
	con.close() 
        print "OK. drop table " + table 
                 
# "----------------------------------------meta / struct / last"         
        
if sel=="meta":               
  with con:    
    cur = con.cursor()    
    cur.execute('PRAGMA table_info('+table+')')    
    data = cur.fetchall()    
    for d in data:
        print d[0], d[1], d[2]  

if sel=="last":
  lid = cur.lastrowid
  print "The last Id of the inserted row is %d" % lid 
  
  
# "----------------------------------------info"
if sel=="info":
  try:
    cur = con.cursor()    
    cur.execute('SELECT SQLITE_VERSION()')    
    data = cur.fetchone()    
    print "SQLite version: %s" % data                
    
  except lite.Error, e:    
    print "Error %s:" % e.args[0]
    sys.exit(1)    
  finally:    
    if con:
        con.close() 
#------------------------------------/end-------------------------
