

#include "H.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n ************** Inicio del programa EPaper-001 *******************\n");

  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);

  if (SDCARD_SS > 0)
  {
    if (!SD.begin(SDCARD_SS))
    {
      Serial.println("Error en la tarjeta SD");
    }
    else
    {
      uint32_t cardSize = SD.cardSize() / (1024 * 1024);
      Serial.printf("SD = %d MB \n", cardSize);
    }
  }

  pinMode(PULSADOR_1, INPUT);
  pinMode(PULSADOR_2, INPUT);
  pinMode(PULSADOR_3, INPUT);

  pinMode(LED,OUTPUT);
  pinMode(J5_PIN_3,OUTPUT);
  pinMode(J5_PIN_4,OUTPUT);


  /*
    if (SPEAKER_OUT > 0)
    {
      ledcSetup(CHANNEL_0, 1000, 8);
      ledcAttachPin(SPEAKER_OUT, CHANNEL_0);
      int i = 3;
      while (i--)
      {
        ledcWriteTone(CHANNEL_0, 500);
        delay(200);
        ledcWriteTone(CHANNEL_0, 0);
      }
    }
  */




  if (!FILESYSTEM.begin())
  {
    Serial.println("FILESYSTEM is not database");
    Serial.println("Please use Arduino ESP32 Sketch data Upload files");
    while (1)
    {
      delay(1000);
    }
  }

  displayInit();

  //Borrar_display();
  displayText("Hola mundo!!!   ", 16, 1);
  displayText("Hola mundo!!!   ", 32, 1);
  displayText("Para eliminar un poco las marcas", 48, 1);
  displayText("DDDDDDDDDDDDDDDDDDDDDD", 64, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 80, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 96, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 112, 1);
  Actualizar_pantalla();

  delay(2000);

  Texto_grande("Hola mundo!!", (32*1)-2, LEFT_ALIGNMENT);
  
  Texto_grande("TERCERA FILA", (32*3)-2, LEFT_ALIGNMENT);
  Texto_grande("CUARTA FILA", (32*4)-2, LEFT_ALIGNMENT);

}



uint32_t inicio;
void loop()
{
  /*
   if  ( digitalRead(PULSADOR_1)  ) {
    digitalWrite(J5_PIN_3,HIGH);
   }
   else {
    digitalWrite(J5_PIN_3,LOW);
   }

   if  ( digitalRead(PULSADOR_2)  ) {
    digitalWrite(J5_PIN_4,HIGH);
   }
   else {
    digitalWrite(J5_PIN_4,LOW);
   }

   if  ( digitalRead(PULSADOR_3)  ) {
    digitalWrite(LED,HIGH);
   }
   else {
    digitalWrite(LED,LOW);
   }
   */


  Texto_grande("12345678901234", (32*2)-2, LEFT_ALIGNMENT);
  Actualizar_pantalla();


  Texto_grande("ABCDEFGHIJKL", (32*2)-2, LEFT_ALIGNMENT);
  Actualizar_pantalla();

  /*
    drawBitmap(DEFALUT_QR_CODE_BMP, 10, 10, true);
    Actualizar_pantalla();
  */

}
