#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <TouchScreen.h>
#include <EEPROM.h>
#include "oe8x8max.h"

//2020 - 17886 Bytes bin

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

//---tlacitka
#define T1min 0 //20
#define T1max 80 //150
#define T2min 85 //150
#define T2max 160
#define LRcenter 110 //c 110 //b 200 //a 130
//---/tlacitka

int kodLock=123; //code for un/lock
int numBut = 3; //defa 2 tlac - mozno 3.. 5..
int butEn = 1;

//butt 1
int xr = 20;
int yr = 165;
int wr = 280;
int hr = 60;
//tft.fillRect(20, 100, 130, 60, RED);
//tft.fillRect(170, 100, 130, 60, RED);
int xrL = xr;
int xrR = 170;

int yLR = 100;
int wLR = 130;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
///TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLACK2   0x0003
#define	BLUE    0x001F
#define	NAVY    0x0011
#define	RED     0xF800
#define	MAROO   0x5000
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define SILVER  0x9999
#define DIMGRAY  0x4228

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//-----------------------------------------------------
#define SN "15xxyy"
//1.06 - 003
//1.07 - dalsi upravy - hlavne "13"

#define VER "2020-D3.10" //
int test = 0; // 0/1
int rychlost = 3; //3 ok (5) 10 ok - nacitani
//-----------------------------------------------------
//37672//

#define BOXSIZE 40
#define PENRADIUS 2
int oldcolor, currentcolor;

//oe
int colTxt = WHITE;

int stavT1 =0;
int stavT2 =0;
int stavT3 =0;
int pozX = 10;
int pozY = 10; //vychozi pro Info //20 logo.. /40/60/80..
int pozYR = 10;
int pozYr = 100; //vychozi pro Info //20 logo.. /40/60/80..
int pozix = 200;
int poziy = 100;

int sideL=0;
int sideR=0;

//uart
char inData[32]; // Allocate some space for the string
char strData[32]; // Allocate some space for the string
char strDataM[64]; 
char butLab[32] = " press butt.";
char butWait[32] = " please wait";

char butLabL[32] = "   (UP)";
char butLabR[32] = "  (EXIT)";
char butLabLRC[32] = "        "; // LR clear

char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int noComm = 0;
int loadOk= 0;
int touchPoz =0;

const uint8_t //PROGMEM
logo[] = {
  0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00 }; 

void setup(void) { 
  if(test){ rychlost=1;} 
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  
  //Serial.begin(9600);
  Serial.begin(115200); //2016/10
  //Serial.println("DWARF3D");  
  tft.reset();  
  uint16_t identifier = tft.readID();
    //test
  if (test){  Serial.println(tft.readID()); }

  //Serial.print(F("LCD driver chip: "));
  //Serial.println(identifier, HEX);
    
  //Serial.println(tft.width());
  //Serial.println(tft.height());
  
  tft.begin(identifier);
  tft.fillScreen(BLACK);  
  tft.setRotation(1);//oe 
  
  tft.setCursor(20, 230);
  tft.setTextColor(DIMGRAY);  
  tft.setTextSize(1);     
  tft.print(VER); 
  tft.print("-"); 
  tft.print(identifier);
  
  //togoTxt();
  
  //tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  //tft.fillRect( 0, BOXSIZE, BOXSIZE, BOXSIZE, YELLOW);
  //tft.fillRect( 0,BOXSIZE*2, BOXSIZE, BOXSIZE, GREEN);
  
  //tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = YELLOW;
 
  //T1OnOff(0);
  //delay(1000);  setButL(0); 
  //delay(1000);  setButL(1); 
  //delay(1500);  resetButLR();
  //delay(1000);  setButR(0);
  //delay(1000);  setButR(1);
  //delay(1500);  resetButLR();
  //T2OnOff(0);
  
  //butLab[32] = "Loading - wait";
  
  //tft.setTextColor(MAGENTA); 
  //pozX=10;
  //pozY=20;
  int iy = 150;
  colTxt = GREEN; 
  icon(invader1a,90,iy);

  colTxt = MAGENTA;
  icon(invader1b,150,iy);

  colTxt = CYAN;
  icon(invader2a,210,iy);
  delay(1000);

  tft.setTextColor(WHITE); 
  
  tft.setCursor(80,80);
  tft.setTextSize(2);
  tft.println("serial display");  
  tft.setCursor(68,100);
  tft.setTextColor(YELLOW); 
  tft.println("octopusengine.org"); 
  delay(1000); 

  tft.fillRect(10,130, 300, 7, DIMGRAY);
  
  for (int load=0; load<300;load++)
  { 
  tft.fillRect(10,131, load, 5, RED);
  //tft.fillRect(20, 85, load, 7, RED);
  //delay(rychlost); 
  } 

  //delay(1000); 
  //tft.fillScreen(BLACK);  
  //pozX = 10; 
  //pozY = 10;  
  //tft.setCursor(pozX, pozY);  
  
  
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  //digitalWrite(13, HIGH);
  //digitalWrite(12, HIGH); 
  
  tft.setTextColor(YELLOW); 
  //pozX=10;
  //pozY=20; 
  tft.setCursor(pozX,pozY);
  tft.setTextSize(2);
  //tft.println("OK"); 
  
  colTxt = WHITE; 
}

//#define MINPRESSURE 10
//#define MAXPRESSURE 1000

void loop()
{
  while (Serial.available() > 0) {    
    //Serial.println(Serial.available());
    // look for the next valid integer in the incoming serial stream:
    //int sel = Serial.parseInt(); 
    char sel= Serial.read();
    if (sel == 'A') 
    {
      int verif = Serial.parseInt(); 
      if (verif==kodLock){
        loadOk=1;
        Serial.println("LoadOk");
        tft.fillRect(0, 0, 320, 100, BLACK);
        
        togoTxtMale();
      
        //butLab = "Loading - ready";
        stavT1=0;
        T1OnOff(stavT1);
      }      
    }
    if (1){ //LOK
    //if (loadOk){ //LOK
    //------------------------------------------------------
     if (sel == 'B') //set button //bit
    {
      int but = Serial.parseInt();      
      int setB = Serial.parseInt();      
      if ((but==1)&(setB==0))  T1OnOff(0); 
      if ((but==1)&(setB==1))  T1OnOff(1);     
     }


     if (sel == 'b') //big - prepisovatelný string na pozici Y
    {
      for (int i=0;i<64;i++) {            strDataM[i]=0;      }  
      Serial.readBytesUntil('*', strDataM, sizeof(strData));
     tft.setCursor(pozX, pozYr);
     tft.fillRect(pozX-1, pozYr-1, 380, 37, BLACK);
     tft.setTextColor(colTxt);  
     tft.setTextSize(5);     
     tft.println(strDataM);     
     }
    //------------------------------------------------------
  if (sel == 'C') //cls
    {
      tft.fillScreen(BLACK);  
      pozX = 10; 
      pozY = 10;  
      tft.setCursor(pozX, pozY);  
      //T1OnOff(stavT1);     
     } 
    //------------------------------------------------------
     if (sel == 'D') //digital
    {
     int num  = Serial.parseInt(); 
/*
     int xi =25;
     int yi= 40;
     tft.setTextColor(YELLOW); 
     
     for (int cas=9;cas>-1;cas--)
     //for (int i=0;i<32;i++)
     { 
       //Serial.println(cas);
       tft.setCursor(xi+2, yi+2);
       tft.fillRect(xi, yi, 30, 20, BLACK); 
       tft.print(cas);
       delay(2000); 
     }
     tft.setCursor(xi+2, yi+2);
     tft.fillRect(xi, yi, 30, 20, BLACK); 
     tft.print(" ");
*/
     
     if (num) 
     {
       digitalWrite(13, HIGH);
       digitalWrite(12, HIGH);
     }       
     else { 
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
         }
     }
 
    //------------------------------------------------------
     
     if (sel == 'E') //EEprom write
    {
      int addr = Serial.parseInt();      
      int val = Serial.parseInt();      
      EEPROM.write(addr, val);   
     }
     
      if (sel == 'F') //EEprom read
    {
      int addr = Serial.parseInt();      
      int data = EEPROM.read(addr); 
      Serial.println(data);   
     }
    //------------------------------------------------------
     if (sel == 'G')  {   togoTxt(); }
     if (sel == 'H')  {   togoTxtMale(); } 
     
      if (sel == 'h') //horizontal line
       {
       //int sx = Serial.parseInt();      
       int sy = Serial.parseInt();   
       //tft.fillCircle(sx,sy, 2, WHITE);  //PENRADIUS=2;
        tft.drawFastHLine(0, sy, 320, colTxt); 
    }
     
     
    
     

   /// -----------------------I J K
   //set L
   //if (sel == 'I')  {  int num = Serial.parseInt();  setButL(num); }
   //set R
    if (sel == 'i') //ikony
    {     
       int col = Serial.parseInt();
       if (col==0) icon5(c0,pozix,poziy);
       if (col==1) icon5(c1,pozix,poziy);
       if (col==2) icon5(c2,pozix,poziy);
       if (col==3) icon5(c3,pozix,poziy);
       if (col==4) icon5(c4,pozix,poziy);
       if (col==5) icon5(c5,pozix,poziy);
       if (col==6) icon5(c6,pozix,poziy);
       if (col==7) icon5(c7,pozix,poziy);
       if (col==8) icon5(c8,pozix,poziy);
       if (col==9) icon5(c9,pozix,poziy);
      
     } 


   
   if (sel == 'I') //ikony
    {     
       int col = Serial.parseInt();
       if (col==0) icon(nic,pozix,poziy);
       if (col==1) icon(invader1a,pozix,poziy);
       if (col==2) icon(invader1b,pozix,poziy);
       if (col==3) icon(invader2a,pozix,poziy);
       if (col==4) icon(invader1b,pozix,poziy);
       if (col==5) icon(tq,pozix,poziy);
      
     } 
   
   if (sel == 'J')   {  int num = Serial.parseInt();  setButR(num);  }
   //reset Kill
   if (sel == 'K')     {    resetButLR();  }
   //-------------------------------------------------
  
   if (sel == 'L') //label1
    {
      for (int i=0;i<32;i++) { butLab[i]=0;   }     
      Serial.readBytesUntil('*', butLab, sizeof(strData));    
      T1OnOff(stavT1);      
    }
  
    //------------------------------------------------------
   if (sel == 'l') //label1
    {
      for (int i=0;i<32;i++) { butLabL[i]=0;   }     
      Serial.readBytesUntil('*', butLabL, sizeof(strData)); 
      tft.setCursor(40, 120);
      tft.setTextColor(WHITE);  
      tft.setTextSize(2); 
      //tft.println(butLabLRC);
      //tft.setCursor(40, 123);
      tft.println(butLabL);  
      setButL(0);
    }
    
    if (sel == 'r') //label1
    {
      for (int i=0;i<32;i++) { butLabR[i]=0;   }     
      Serial.readBytesUntil('*', butLabR, sizeof(strData)); 
      tft.setCursor(190, 120);
      tft.setTextColor(WHITE);  
      tft.setTextSize(2); 
      //tft.println(butLabLRC);
      //tft.setCursor(185, 123);
      tft.println(butLabR);
      setButR(0); 
    } 
  
  
   if (sel == 'M') //maly˝ info string
    {
      for (int i=0;i<64;i++) {   strDataM[i]=0;  }     
      Serial.readBytesUntil('*', strDataM, sizeof(strData));    
      tft.setCursor(20, 85);
      tft.fillRect(20, 85, 300, 10, BLACK);
      tft.setTextColor(colTxt);  
      tft.setTextSize(1);     
      tft.println(strDataM);       
     }
     
      if (sel == 'N')   {  Serial.println(SN); }//serial.num      
      
      if (sel == 'O')   { int num  = Serial.parseInt();  numBut=num; }  
      
      
      if (sel == 'p') //point 1x1
       {
       int sx = Serial.parseInt();      
       int sy = Serial.parseInt();   
       //tft.fillCircle(sx,sy, 2, WHITE);  //PENRADIUS=2;
       tft.drawPixel(sx, sy, colTxt);
       //tft.drawPixel(sx+1, sy, colTxt);
       //tft.drawPixel(sx, sy+1, colTxt);
       //tft.drawPixel(sx+1, sy+1, colTxt);
       //tft.point(sx, sy);       
    }
      
      
       if (sel == 'P') //point 2x2
       {
       int sx = Serial.parseInt();      
       int sy = Serial.parseInt();   
       //tft.fillCircle(sx,sy, 2, WHITE);  //PENRADIUS=2;
       tft.drawPixel(sx, sy, colTxt);
       tft.drawPixel(sx+1, sy, colTxt);
       tft.drawPixel(sx, sy+1, colTxt);
       tft.drawPixel(sx+1, sy+1, colTxt);
       //tft.point(sx, sy);      
    }


    if (sel == 'q') //dynamic string - ending "*" Y
    {
      for (int i=0;i<64;i++) {            strDataM[i]=0;      }  
      Serial.readBytesUntil('*', strDataM, sizeof(strData));
     tft.setCursor(pozX, pozYr);
     tft.fillRect(pozX-1, pozYr-1, 380, 12, BLACK);
     tft.setTextColor(colTxt);  
     tft.setTextSize(1);     
     tft.println(strDataM);     
     }

      
    if (sel == 'Q') //prepisovatelný string na pozici Y
    {
      for (int i=0;i<64;i++) {            strDataM[i]=0;      }  
      Serial.readBytesUntil('*', strDataM, sizeof(strData));
     tft.setCursor(pozX, pozYR);
     tft.fillRect(pozX-2, pozYR-2, 380, 20, BLACK);
     tft.setTextColor(colTxt);  
     tft.setTextSize(2);     
     tft.println(strDataM);     
     }
  
   if (sel == 'R') //row
    {
      //Serial.println("rest");
      int num = Serial.parseInt(); 
      
    // tft.setCursor(130, 115);
    // tft.fillRect(130, 115, 100, 50, BLACK); //B2
    // tft.setTextColor(WHITE);  
    // tft.setTextSize(5);     
    // tft.print(num); 
    // tft.print("%");
    pozYR = num*20+10;    
     
     }

 if (sel == 'r') //radek
    {
      //Serial.println("rest");
      int num = Serial.parseInt();  
      pozYr = num*12+10;      
     }     
     
      if (sel == 'S') //string na pozici a barvÄ›
    {
      for (int i=0;i<32;i++) {            strData[i]=0;      }     
     
      Serial.readBytesUntil('*', strData, sizeof(strData));
      //Serial.println(strData);      
     tft.setCursor(pozX, pozY);
     tft.fillRect(pozX, pozY, 300, 20, BLACK);
     tft.setTextColor(colTxt);  
     tft.setTextSize(2);     
     tft.println(strData);       
     }  
     
     
      if (sel == 't') //string na pozici Y
    {
      for (int i=0;i<64;i++) {            strDataM[i]=0;      }  
      Serial.readBytesUntil('*', strDataM, sizeof(strData));
      //tft.setCursor(pozX, pozY);
      tft.fillRect(pozX, pozY, 300, 10, BLACK);
      tft.setTextColor(colTxt);  
      tft.setTextSize(1);     
      tft.println(strDataM);     
     }
     
      if (sel == 'T') //string na pozici Y
    {
      for (int i=0;i<64;i++) {            strDataM[i]=0;      }  
      Serial.readBytesUntil('*', strDataM, sizeof(strData));
      //tft.setCursor(pozX, pozY);
      tft.fillRect(pozX, pozY, 300, 20, BLACK);
      tft.setTextColor(colTxt);  
      tft.setTextSize(2);     
      tft.println(strDataM);     
     }
  
     // U  
  
     //verze
     if (sel == 'V')  { Serial.println(VER); } 
     
     if (sel == 'v') //verticaL line
       {
       int sx = Serial.parseInt();      
       //int sy = Serial.parseInt();   
       //tft.fillCircle(sx,sy, 2, WHITE);  //PENRADIUS=2;
        tft.drawFastVLine(sx, 0, 240, colTxt); 
    }
    
    
     if (sel == 'W') //set barvy
    {     
       int col = Serial.parseInt();
       if (col==0) colTxt = BLACK; 
       if (col==1) colTxt = WHITE;
       if (col==2) colTxt = YELLOW;
       if (col==3) colTxt = RED;
       if (col==4) colTxt = GREEN;
       if (col==5) colTxt = MAROO;
       if (col==6) colTxt = MAGENTA;
       if (col==7) colTxt = CYAN;
       if (col==8) colTxt = NAVY;
       if (col==9) colTxt = DIMGRAY;
     } 

 if (sel == 'c') //set barvy
    {     
       int col = Serial.parseInt();
       if (col==0) colTxt = BLACK; 
       if (col==1) colTxt = WHITE;
       if (col==2) colTxt = YELLOW;
       if (col==3) colTxt = RED;
       if (col==4) colTxt = GREEN;
       if (col==5) colTxt = MAROO;
       if (col==6) colTxt = MAGENTA;
       if (col==7) colTxt = CYAN;
       if (col==8) colTxt = NAVY;
       if (col==9) colTxt = DIMGRAY;
     }   

     
     
      if (sel == 'X')     {  int num = Serial.parseInt();  pozX = num; } //set pozice z    
      if (sel == 'Y')     {  int num = Serial.parseInt();  pozY = num; } //set pozice y

      if (sel == 'x')     {  int num = Serial.parseInt();  pozix = num; } //set pozice z ikony   
      if (sel == 'y')     {  int num = Serial.parseInt();  poziy = num; } //set pozice y ikony
     
     
     if (sel == 'Z') //lock uart
    {
      int verif = Serial.parseInt(); 
      if (verif==kodLock){ loadOk=0; }      
    }
    
     if (sel == 'z') //lock uart
    {
      int verif = Serial.parseInt(); 
      if (verif==1){ butEn=1; }
      else { butEn=0; }      
    }     
     
     }//LOK  
  }
}

//-----------------------------
void testLogo() 
{
  for (int y=0;y<16;y++)
  {
     for (int x=0;x<8;x++)  
     {     
       //if (logo[x*16+y]==0)  tft.drawPixel(x*2, y*2, WHITE); 
       int b =0;  
       for (byte mask = 0000000000000001; mask>0; mask <<= 1) { //iterate through bit mask
           b++;
           if (logo[x+y*16] & mask)
           { // if bitwise AND resolves to true
           tft.drawPixel(20+x*16+b*2, 20+y*2, YELLOW); 
           //tft.drawPixel(20+x*2*8+b+1, 20+y*2, WHITE); 
           //tft.drawPixel(20+x*2*8+b, 20+y*2+1, WHITE); 
           //tft.drawPixel(20+x*2*8+b+1, 20+y*2+1, WHITE); 
           }   
       }    
    }
  }
}  

void togoTxt() 
{
    tft.setCursor(75, 30);
    tft.setTextSize(5);
    //tft.setTextColor(RED);  
    //tft.print("3"); 
    //tft.setTextColor(WHITE); 
    //tft.print("DWARF"); 
    
    //tft.fillRect(20, 87, 279, 3, WHITE);
    
}  

void togoTxtMale() 
{
    //tft.setCursor(40, 15);
    //tft.setTextSize(2);
    //tft.setTextColor(RED);  
    //tft.print("3"); 
    //tft.setTextColor(WHITE); 
    //tft.print("DWARF - DLP printer"); 
    
    //tft.fillRect(15, 33, 280, 2, RED);
    
}  

void T1OnOff(int jak) {
if (jak){
       stavT1 = 1;
       //digitalWrite(13, LOW);       
       //tft.fillRect(xr, yr, wr, hr, DIMGRAY);
       //tft.drawFastHLine(xr+1, yr, wr-2, DIMGRAY); 
       //tft.drawFastVLine(xr+1, yr+1, hr-2, DIMGRAY); 
       //tft.drawFastHLine(xr+1, yr+hr, wr-1, WHITE); 
       //tft.drawFastVLine(xr+wr, yr+1, hr, WHITE); 
       
       tft.setCursor(80, 188);
       tft.setTextColor(WHITE);  
       tft.setTextSize(2);
       tft.println(butWait);   
}
else
{
      stavT1 = 0;
      //digitalWrite(13, HIGH);
      
      
      
  }
}

void resetButLR() {
    /*
           tft.drawFastHLine(xrL+1, yLR, wLR-2, BLACK); 
           tft.drawFastVLine(xrL+1, yLR+1, hr-2, BLACK);          
           tft.drawFastHLine(xrL+1, yLR+hr, wLR-1, BLACK); 
           tft.drawFastVLine(xrL+wLR, yLR, hr-1, BLACK);
           
           tft.drawFastHLine(xrR+1, yLR, wLR-2, BLACK); 
           tft.drawFastVLine(xrR+1, yLR+1, hr-2, BLACK);          
           tft.drawFastHLine(xrR+1, yLR+hr, wLR-1, BLACK); 
           tft.drawFastVLine(xrR+wLR, yLR, hr-1, BLACK); 
           */       
      }   

void setButL(int jak) {;}
void setButR(int jak) {;}
void T2OnOff(int jak) {
if (jak){
       
       //digitalWrite(13, LOW);
       if (numBut==2) { stavT2 = 1;  }       
       if (numBut==3) {
         if (sideL)  {
           //tft.fillRect(xrL, yLR, wLR, hr, RED);
           setButL(1);
           Serial.println("t2L"); 
           stavT2 = 1;  
     }
         if (sideR)  {
           //tft.fillRect(yeR, yLR, wLR, hr, RED);
           setButR(1);
           Serial.println("t2R");
           stavT3 = 1;   
      }
     }
      
}
else
{
      stavT2 = 0;
      stavT3 = 0;
      //tft.drawFastHLine(xrL+1, yLR, wLR-2, BLACK); 
      //tft.drawFastVLine(xrL+1, yLR+1, hr-2, BLACK);  
      //tft.drawFastHLine(xrR+1, yLR, wLR-2, BLACK); 
      //tft.drawFastVLine(xrR+1, yLR+1, hr-2, BLACK);
      
      //digitalWrite(13, HIGH);
      //tft.fillRect(20, 100, 280, 60, BLACK); 
      ///SEcho();  
  }
}

//------------------------------8x8
void icon(byte co[],int kamx, int kamy)
{
  //lc.setRow(0,i,co[i]);
  int x=0;
  for (int y = 0; y < 8; y++)  
  {
    //lc.setRow(0,i,co[i]);    
       //if (co[x*8+y]==1) 
        x=8;      
       for (byte mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
         x--;
         int sx = kamx+x*3;      
         int sy = kamy+y*3;   
         if (co[y] & mask){  
        
         tft.drawPixel(sx, sy, colTxt);
         tft.drawPixel(sx+1, sy, colTxt);
         tft.drawPixel(sx, sy+1, colTxt);
         tft.drawPixel(sx+1, sy+1, colTxt);         
       
       } 
         else
       {             
         tft.drawPixel(sx, sy, BLACK);
         tft.drawPixel(sx+1, sy, BLACK);
         tft.drawPixel(sx, sy+1, BLACK);
         tft.drawPixel(sx+1, sy+1, BLACK);    
       }    
    }
}
}

void icon5(byte co[],int kamx, int kamy)
{
  //lc.setRow(0,i,co[i]);
  int x=0;
  for (int y = 0; y < 8; y++)  
  {
    //lc.setRow(0,i,co[i]);    
       //if (co[x*8+y]==1) 
        x=8;      
       for (byte mask = 00000001; mask>0; mask <<= 1) { //iterate through bit mask
         x--;
         int sx = kamx+x*5;      
         int sy = kamy+y*6;   
         if (co[y] & mask){  
        
         tft.drawPixel(sx, sy, colTxt);
         tft.drawPixel(sx+2, sy, colTxt);
         tft.drawPixel(sx, sy+3, colTxt);
         tft.drawPixel(sx+2, sy+3, colTxt);         
       
       } 
         else
       {             
         tft.drawPixel(sx, sy, BLACK);
         tft.drawPixel(sx+2, sy, BLACK);
         tft.drawPixel(sx, sy+3, BLACK);
         tft.drawPixel(sx+2, sy+3, BLACK);  
       }              
    }
}
}

void oebyte(byte co[])
{
  Serial.print("Q");  
  for (int x = 0; x < 8; x++)  
  {
    //lc.setRow(0,i,co[i]);      
    Serial.print(co[x]);
    Serial.print(".");
    //delay(10);
  }
    Serial.print("*"); 
}
