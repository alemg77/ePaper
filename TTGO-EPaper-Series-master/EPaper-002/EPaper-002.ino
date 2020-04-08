#include "H.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n ************** Inicio del programa EPaper-001 *******************\n");

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

  SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, -1);


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
  displayText("La pantalla se borro dos veces", 32, 1);
  displayText("Para eliminar un poco las marcas", 48, 1);
  displayText("DDDDDDDDDDDDDDDDDDDDDD", 64, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 80, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 96, 1);
  displayText("EEEEEEEEEEEEEEEEEEEEEE", 112, 1);
  Actualizar_pantalla();
  
  delay(2000);
  
}

int inicio_x = 0;
int inicio_y = 16;
int ancho_x = 296;
int altura_y = 33;

void loop()
{

  Borrar_parcialmente(inicio_x,inicio_y, 296,17);
  displayText("1234567890ASDFGHIJKLMOPQR", inicio_y+16, 1);
  Actualizar_pantalla();  


  Borrar_parcialmente(inicio_x,inicio_y, 296,17);
  displayText("ZXCVBNMQWERTYUIO", inicio_y+16, 1);
  Actualizar_pantalla();    


  drawBitmap(DEFALUT_QR_CODE_BMP, 10, 10, true);

  Actualizar_pantalla();  

}
