//arduino nano - voltmeter - for serial display
int analogInput = 0;
long randNumber1; 
long randNumber2;
int y0 = 260;
int value = 0;
int anvalue = 0;
int oldvalue = 0;
int rele=1;

unsigned long previousMillis = 0;
long interval = 1000;

int cnt = 0;
int cntx = 0;
int cntm = 0;
int xold = 0;
int xnew = 0;

int x2old = 0;
int x2new = 0;
int y2old = 0;
int y2new = 0;

//----------------------------
void setup(void) {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13, rele);
  randomSeed(analogRead(0)); 
  Serial.begin(9600);
  delay(8000); //pause.. waiting for device
   
   //communication with serial monitor:
   Serial.println("C"); //clear
   Serial.print("W7");  //change color
   Serial.print("h");   //horizontal line
   Serial.print(y0);    //set y position 

   Serial.print("W8");  //change color
   for (int vv=20;vv<80;vv++){
   Serial.print("h");   //lines
   Serial.print(volt2gr120(float(vv*2))); //
   delay(20);}

   Serial.print("W8"); //a 10 min
   for (int tt=0;tt<32;tt++){
   Serial.print("v");
   Serial.print(tt*15); //tt*30> sum cca 2 hour. ///
   delay(20);}

   Serial.print("W7");
   
   //after 1 hour
   for (int tt=0;tt<6;tt++){
   Serial.print("v");
   Serial.print(tt*15*6);
   delay(20);}

   Serial.print("W7");
   for (int vv=10;vv<15;vv++){
   Serial.print("h");
   Serial.print(volt2gr12(vv));
   delay(20);}
   /*Serial.print("h");
   Serial.print(volt2gr12(13));
   delay(10);
   Serial.print("h");
   Serial.print(volt2gr12(14));
   delay(10);*/

   Serial.print("R0");
   Serial.println("Q SERIAL MONITOR (12 Volt)*"); //on position 10/30/50/70/..
   delay(30);   
   Serial.print("R10");
   //delay(100);
   Serial.print("Q11.12.13 V     3 hour.*");   
   }

float num2v5(int value) {
  float volt = (value * 5.0) / 1024.0; // see text
  return volt; 
}

float num2v12(int value) {
  float volt = ((value * 5.0) / 1024.0)*2.93; // 3mo / 2.9 malo
  return volt; 
}   

int num2gr(int value) {
  float volt = num2v5(value); // see text
  float gpom = y0-volt*24;
  int gr = int(gpom);
  //Serial.print(num);
  //Serial.print(" - ");
  //Serial.print(gf);
  //Serial.println();
  return gr; 
}

int volt2gr5(float volt) {
  //float volt = num2v(value); // see text
  float gpom = y0-volt*30;
  int gr = int(gpom);
  //Serial.print(num);
  //Serial.print(" - ");
  //Serial.print(gf);
  //Serial.println();
  return gr; 
}

int volt2gr12(float volt) {
  //float volt = num2v(value); // see text
  float gpom = 105+y0*2-volt*40; //230+...*50 //200+...*46//
  int gr = int(gpom);
  //Serial.print(num);
  //Serial.print(" - ");
  //Serial.print(gf);
  //Serial.println();
  return gr; 
}

int volt2gr120(float volt) {
  //float volt = num2v(value); // see text
  float gpom = 105+y0*2-volt*4;
  int gr = int(gpom);
  //Serial.print(num);
  //Serial.print(" - ");
  //Serial.print(gf);
  //Serial.println();
  return gr; 
}

void sdWrite(){
  Serial.print("W2");
  Serial.print("R1");
  Serial.print("Q");
  Serial.print(cntm);
  Serial.print(":");
  Serial.print(cnt);
  Serial.print(" >");
  Serial.print(value);
  Serial.print("*");

  Serial.print("W1");
  Serial.print("R2");
  Serial.print("Q");
  Serial.print(num2v5(value));
  Serial.print(" ... ");
  Serial.print(num2v12(value));
  Serial.print("V*");
  //Serial.print("W2");  
}
   
 
//===========================================================
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
  previousMillis = currentMillis;  
  cnt++;
  cntx++;
  if (cnt==60){
    cnt=0;cntm++;
    rele=!rele;
    digitalWrite(13, rele); 
    digitalWrite(12, !rele);    
    }

  int value1 = analogRead(analogInput);
  int value2 = analogRead(analogInput);
  int value3 = analogRead(analogInput);
  int value4 = analogRead(analogInput);
  oldvalue = anvalue;
  anvalue = (value1+value2+value3+value4)/4;
  value = (oldvalue+anvalue)/2;
  //value = 900;
  //float vout = (value * 5.0) / 1024.0; // see text
  //vin = vout / (R2/(R1+R2))  
  //randNumber = random(300);
  //randNumber1 = random(120, 200);
  sdWrite();

  Serial.print("W2"); 
  int x = cntx/40; // cntx/20>po2hod. ///
  //int y = y0-vout*10;
  //int y = volt2gr5(num2v5(value));
  int y = volt2gr12(num2v12(value));
  Serial.print("P");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);

  if (cntx<1200){
  Serial.print("W7");   
  int x = cntx/4;
  //int y = y0-vout*10;
  //int y = volt2gr5(num2v5(value));
  int y = volt2gr12(num2v12(value));
  Serial.print("P");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  }  
  }  

} 




