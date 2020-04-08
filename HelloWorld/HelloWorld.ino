#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_IL3820_V2_296X128_4W_SW_SPI u8x8(/* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ 19, /* reset=*/ 12);	// eInk/ePaper Display, optimized (lesser screen flicker)


// End of constructor list



void setup(void)
{
 
  u8x8.begin();
  u8x8.setPowerSave(0);
//  u8x8.setFont(u8x8_font_chroma48medium8_r);  
  u8x8.setFont(u8x8_font_artosserif8_u);  

  
}

void loop(void)
{

  u8x8.drawString(0,0,"Hello World!");
  u8x8.refreshDisplay();		// only required for SSD1606/7  
  delay(2000);

  u8x8.drawString(10,0,"Hola mundo!");
  u8x8.refreshDisplay();    // only required for SSD1606/7  
 
  delay(2000);
}
