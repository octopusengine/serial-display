//arduino uno - clock with DS3231 module - for serial display
#include <DS3231.h>
#include <Wire.h>
//#include "U8glib.h"

//U8GLIB_SSD1306_132X64 u8g(10, 9, 12, 11, 8);
//U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 8);
//                        D0, D1,CS, DC, RST
int cnt=0;
char temp[9];
int second,minute,hour,date,month,year,temperature; 

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

byte yearC, monthC, dateC, DoW, hourC, minuteC, secondC;

long randNumber1; 
long randNumber2;

int xold = 0;
int xnew = 0;

int x2old = 0;
int x2new = 0;
int y2old = 0;
int y2new = 0;

void setup(void) {
  //randomSeed(analogRead(0)); 
  //Serial.begin(9600);
  //if (test){  Serial.println(tft.readID()); }
   delay(6000);
   Serial.begin(9600); 
   Serial.println("C");
   Serial.print("W7");
   Serial.print("h70");
   delay(100);
   Serial.print("h230");
   Serial.print("R0");
   Serial.println("Q SERIAL MONITOR - TIME*"); //prepis text na pozici 10/30/50/70/..
   delay(100);
   Serial.print("R1");
   Serial.print("W1");
   Serial.print("Q octopusengine.eu*");    

   Wire.begin();
   //-----------------nastaveni
   ///setupTime();
   
   // Start the serial interface  Serial.begin(9600); 
  
  //Serial.begin(115200);
}    

void setupTime() {
  // Start the I2C interface
  Wire.begin();
        Clock.setSecond(30);//Set the second 
        Clock.setMinute(59);//Set the minute 
        Clock.setHour(18);  //Set the hour 
        Clock.setDoW(5);    //Set the day of the week
        Clock.setDate(7);  //Set the date of the month
        Clock.setMonth(12);  //Set the month of the year
        Clock.setYear(15);  //Set the year (Last two digits of the year)    
   } 

void draw(void) {
  //second=Clock.getSecond();
  //minute=Clock.getMinute();
  //hour=Clock.getHour(h12, PM);
    
  //u8g.drawStr( 27, 49,  dtostrf(hourC, 2, 0, temp));
  //u8g.drawStr( 60, 45,  ":");
  //u8g.drawStr( 70, 49,  dtostrf(minuteC, 2, 0, temp));
  } 

void ReadDS3231()
{
  //int second,minute,hour,date,month,year,temperature; 
  secondC=Clock.getSecond();
  minuteC=Clock.getMinute();
  hourC=Clock.getHour(h12, PM);
  dateC=Clock.getDate();
  monthC=Clock.getMonth(Century);
  yearC=Clock.getYear();   
  
  /*
  Serial.print(' ');
  Serial.print(hourC,DEC);
  Serial.print(':');
  //Serial.print(minuteC,DEC);
  if (minuteC<10){Serial.print("0");}
  Serial.print(minuteC,DEC);
  
  Serial.print(':');
  Serial.print(secondC,DEC);
  Serial.print("*");
  //Serial.print('\n');
  */
  if (secondC%10==0){
  temperature=Clock.getTemperature();
  Serial.print("R9");  //row9
  Serial.print("W2");  //change color
  Serial.print("Q");   //Q simple string
  Serial.print("20");  //year 20xx
  Serial.print(yearC,DEC);
  Serial.print('-');
  if (monthC<10){Serial.print("0");}
  Serial.print(monthC,DEC);
  Serial.print('-');
  if (dateC<10){Serial.print("0");}
  Serial.print(dateC,DEC);
  Serial.print("*");
    
  Serial.print("R10"); //row10
  Serial.print("W6");  //change color
  Serial.print("Q");
  Serial.print("Temperature=");
  Serial.print(temperature);
  Serial.print("*"); 
  }
  //Serial.print('\n');

Serial.print("W4");
//:
 Serial.print("P107,120"); 
 Serial.print("P107,138"); 
//hh
 
int pozH = 20;
 if (hourC<10) {
   Serial.print("x"); //big clock nubers 
   Serial.print(pozH); 
   Serial.print("i0");
   Serial.print("x"); 
   Serial.print(pozH+40); 
   Serial.print("i");
   Serial.print(hourC);
  }
  else
  {
  Serial.print("x"); 
  Serial.print(pozH); 
  Serial.print("i");
  Serial.print(int(hourC/10));
  Serial.print("x"); 
  Serial.print(pozH+40); 
  Serial.print("i");
  Serial.print(int(hourC%10));
  }  

//mm
 if (minuteC<10) {
   Serial.print("x"); 
   Serial.print(pozH+95); 
   Serial.print("i0");
   Serial.print("x"); 
   Serial.print(pozH+132); //+130 
   Serial.print("i");
   Serial.print(minuteC);
  }
  else
  {
  Serial.print("x"); 
  Serial.print(pozH+95); 
  Serial.print("i");
  Serial.print(int(minuteC/10));
  Serial.print("x"); 
  Serial.print(pozH+132); 
  Serial.print("i");
  Serial.print(int(minuteC%10));
  } 


//ss
  Serial.print("W6");
  //Serial.print("i");
  if (secondC<10) {
  Serial.print("x"); 
  Serial.print(pozH+185); 
   Serial.print("i0");
   Serial.print("x"); 
  Serial.print(pozH+223); 
   Serial.print("i");
   Serial.print(secondC);
  }
  else
  {
  Serial.print("x"); 
  Serial.print(pozH+185); 
  Serial.print("i");
  Serial.print(int(secondC/10));
  Serial.print("x"); 
  Serial.print(pozH+223); 
  Serial.print("i");
  Serial.print(int(secondC%10));
  }   
}

void loop(void) {
  // picture loop
  //cnt++;
  //if (cnt>100) cnt=0;
  ReadDS3231();
  draw();
  delay(1000);
  // rebuild the picture after some delay

}

void loop2() {ReadDS3231();delay(1000);
        //Serial.print(Clock.getMinute(), DEC);
  //Serial.print(':');
  //Serial.print(Clock.getSecond(), DEC);


  // send what's going on to the serial monitor.
  // Start with the year
/*  Serial.print("2");
  if (Century) {      // Won't need this for 89 years.
    Serial.print("1");
  } else {
    Serial.print("0");
  }
  Serial.print(Clock.getYear(), DEC);
  Serial.print('-');
  // then the month
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print('-');
  // then the date
  Serial.print(Clock.getDate(), DEC);
  Serial.print(' ');*/
  // and the day of the week
  /*Serial.print(Clock.getDoW(), DEC);
  Serial.print(' ');*/
  // Finally the hour, minute, and second
  /*Serial.print(Clock.getHour(h12, PM), DEC);
  Serial.print(':');
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(':');
  Serial.print(Clock.getSecond(), DEC);
  // Add AM/PM indicator
  if (h12) {
    if (PM) {
      Serial.print(" PM ");
    } else {
      Serial.print(" AM ");
    }
  } else {
    Serial.print(" 24h ");
  }
  // Display the temperature
  Serial.print("T=");
  Serial.print(Clock.getTemperature(), 2);
  // Tell whether the time is (likely to be) valid
  if (Clock.oscillatorCheck()) {
    Serial.print(" O+");
  } else {
    Serial.print(" O-");
  }*/
  // Indicate whether an alarm went off
  /*if (Clock.checkIfAlarm(1)) {
    Serial.print(" A1!");
  }
  if (Clock.checkIfAlarm(2)) {
    Serial.print(" A2!");
  }*/
  // New line on display
  //Serial.print('\n');
       // delay(1000);
  // Display Alarm 1 information
/*  Serial.print("Alarm 1: ");
  Clock.getA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);
  Serial.print(ADay, DEC);
  if (ADy) {
    Serial.print(" DoW");
  } else {
    Serial.print(" Date");
  }
  Serial.print(' ');
  Serial.print(AHour, DEC);
  Serial.print(' ');
  Serial.print(AMinute, DEC);
  Serial.print(' ');
  Serial.print(ASecond, DEC);
  Serial.print(' ');
  if (A12h) {
    if (Apm) {
      Serial.print('pm ');
    } else {
      Serial.print('am ');
    }
  }
  if (Clock.checkAlarmEnabled(1)) {
    Serial.print("enabled");
  }
  Serial.print('\n');
  // Display Alarm 2 information
  Serial.print("Alarm 2: ");
  Clock.getA2Time(ADay, AHour, AMinute, ABits, ADy, A12h, Apm);
  Serial.print(ADay, DEC);
  if (ADy) {
    Serial.print(" DoW");
  } else {
    Serial.print(" Date");
  }
  Serial.print(' ');
  Serial.print(AHour, DEC);
  Serial.print(' ');
  Serial.print(AMinute, DEC);
  Serial.print(' ');
  if (A12h) {
    if (Apm) {
      Serial.print('pm');
    } else {
      Serial.print('am');
    }
  }
  if (Clock.checkAlarmEnabled(2)) {
    Serial.print("enabled");
  }*/
  /* display alarm bits
  Serial.print('\n');
  Serial.print('Alarm bits: ');
  Serial.print(ABits, DEC);
  */
/*
  Serial.print('\n');
  Serial.print('\n');
  delay(1000);

  // Display the time once more as a test of the getTime() function
  Clock.getTime(year, month, date, DoW, hour, minute, second);
  
        Serial.print(year, DEC);
        Serial.print("/");
  Serial.print(month, DEC);
        Serial.print("/");
  Serial.print(date, DEC);
        Serial.print("day of the week :");
  Serial.println(DoW, DEC);
  Serial.print(hour, DEC);
        Serial.print(":");
  Serial.print(minute, DEC);
        Serial.print(":");
  Serial.println(second, DEC);*/
}




 


