# serial-display
Arduino UNO with 324x240 TTF color display - as a serial "inteligent" UART terminal (or monitor)<br />
easy connection to a UART - Tx (I dont use the touchscreen)<br />
<b>it works with:</b><br />
<li ><b>Raspberry Pi</b> (A, B, B2..) | PC (Arduino serial monitor) | Mac</li>
<li >microcontrollers PIC / Atmel</li>
<li >Arduino Nano / Uno / Mega...</li>

<hr />
Example - serial display with Raspberry Pi (get IP function)<br />
<img src=https://raw.githubusercontent.com/octopusengine/serial-display/master/images/sd-rpi-get-ip.jpg width=800>
<br />

next examples of use:
https://www.instagram.com/p/_uHGhZR7VS/?tagged=serialdisplay<br />
or <b>#serialdisplay </b> https://www.instagram.com/explore/tags/serialdisplay/<br />
<img src=https://raw.githubusercontent.com/octopusengine/serial-display/master/images/sd-examples.png width=800><br />

code for Arduino and Raspberry Pi is in directory: <b>examples-of-use</b><br />

<hr />
I use "old type" of <a href=http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2047675.m570.l1313.TR0.TRC0.H0.X+2%2C4%22+TFT+320x240p+LCD+Modul+Touch+Panel+Display.TRS0&_nkw=+2%2C4%22+TFT+320x240p+LCD+Modul+Touch+Panel+Display&_sacat=0>2,4" TFT 320x240p LCD Modul Touch Panel Display</a><br />
https://github.com/adafruit/TFTLCD-Library<br />
https://github.com/adafruit/Adafruit-GFX-Library<br />
<hr />

there are icons and big numbers ( c0[] -  c9[]) definitions at <b>oe8x8max.h</b><br />
icon.. for example invader1a[], invader1b[], invader2a[]...
<hr />
<code>Serial.begin(9600);</code><br />
<code>tft.reset();</code><br />  
<code>uint16_t identifier = tft.readID();</code><br />
<code>if (test){  Serial.println(tft.readID()); } </code><br />
<br />
type: 340 | 37672 | 37669 | 49344 ... library ADAFRUIT (2015) or SWIFT (2016) edition



