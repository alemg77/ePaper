/*

  PrintHelloWorld.ino
  
  Use the (Arduino compatible) u8g2 function "print"  to draw a text.
  Also use the Arduino F() macro to place the text into PROGMEM area.

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

U8G2_IL3820_V2_296X128_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 19, /* reset=*/ 12);	// ePaper Display, lesser flickering and faster speed, enable 16 bit mode for this display!



// End of constructor list


void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.firstPage();
  u8g2.setTextSize(2);
  
  do {
    u8g2.setCursor(0, 40);
    u8g2.print(F("123456789"));
    u8g2.setCursor(0, 100);
    u8g2.print(F("Hola Mundo!"));
    
    
  } while ( u8g2.nextPage() );
  delay(1000);
}
