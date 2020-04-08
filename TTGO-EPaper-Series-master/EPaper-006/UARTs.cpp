#include "H.h"

void Task_UARTs (void *parametro_task) {
  static char Buffer_serie[50];
  while (1) {
    vTaskDelay(1);
    char i = 0;
    while (Serial.available())
    {
      char inChar = (char)Serial.read();
      if (inChar == 10)   // 10 es el ascci de nueva linea
      {
        Buffer_serie[i] = 0;
        String aux = Buffer_serie;
        Serial.println(aux);
        i = 0;
      }
      else
      {
        Buffer_serie[i] = inChar;
        i++;
      }
    }
  }
}
