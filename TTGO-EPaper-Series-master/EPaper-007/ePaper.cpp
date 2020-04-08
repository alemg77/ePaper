#include "H.h"

#define LOGO_A6 "/Logo A6.bmp"
#define LOGO_BLE "/Logo BLE.bmp"

extern bool deviceConnected;

extern float Temperatura[4];

void Task_ePaper (void *parametro_task) {
  displayInit();
  drawBitmap(LOGO_A6, 0, 0, true);
  Actualizar_pantalla();
  delay(2000);

  while (1) {
    vTaskDelay(1);
    Borrar_parcialmente(0, 0, 295, 128);
    char buffer_texto[50];

    if ( deviceConnected )
    {
        drawBitmap(LOGO_BLE, 240, 0, true);
    }
    
    sprintf(buffer_texto, "Exterior %.1f", Temperatura[0]);
    Texto_grande(buffer_texto, 33, LEFT_ALIGNMENT);

    sprintf(buffer_texto, "Interior %.1f",Temperatura[3]);
    Texto_grande(buffer_texto, 68, LEFT_ALIGNMENT);

    sprintf(buffer_texto, "PC  %.1f/%.1f", Temperatura[1],Temperatura[2]);
    Texto_grande(buffer_texto, 103, LEFT_ALIGNMENT);
    
    sprintf(buffer_texto, "Temperaturas en centigrados", Temperatura[0]);
    displayText(buffer_texto, 123, LEFT_ALIGNMENT);


    
    Actualizar_pantalla();
  }
}
