#include "H.h"

extern float Temperatura[4];

void Task_ePaper (void *parametro_task) {
  displayInit();

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

  Texto_grande("Hola mundo!!", (32 * 1) - 2, LEFT_ALIGNMENT);
  Texto_grande("TERCERA FILA", (32 * 3) - 2, LEFT_ALIGNMENT);
  Texto_grande("CUARTA FILA", (32 * 4) - 2, LEFT_ALIGNMENT);

  while (1) {
    vTaskDelay(1);
    Borrar_parcialmente(0, 0, 295, 128);
    char buffer_texto[50];

    sprintf(buffer_texto, "Temperaturas en centigrados", Temperatura[0]);
    displayText(buffer_texto, 18, LEFT_ALIGNMENT);
    
    sprintf(buffer_texto, "Exterior %.1f", Temperatura[0]);
    Texto_grande(buffer_texto, 55, LEFT_ALIGNMENT);

    sprintf(buffer_texto, "Interior %.1f",Temperatura[3]);
    Texto_grande(buffer_texto, 90, LEFT_ALIGNMENT);

    sprintf(buffer_texto, "PC  %.1f/%.1f", Temperatura[1],Temperatura[2]);
    Texto_grande(buffer_texto, 125, LEFT_ALIGNMENT);
    

    
    Actualizar_pantalla();
  }
}
