#include "H.h"

TaskHandle_t Task_Handle_ePaper;
TaskHandle_t Task_Handle_Sensor_temperatura;
TaskHandle_t Task_Handle_uart;
TaskHandle_t Task_Handle_ble;

xQueueHandle cola_ble_tx_1,cola_ble_tx_2,cola_ble_tx_3;

extern void Task_ePaper (void *parametro_task);
extern void Task_Sensores_temperatura  (void *parametro_task);
extern void Task_UARTs (void *parametro_task);
extern void Task_ble (void *parametro_task);

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

/*
  pinMode(PULSADOR_1, INPUT);
  pinMode(PULSADOR_2, INPUT);
  pinMode(PULSADOR_3, INPUT);

  pinMode(LED, OUTPUT);
  pinMode(J5_PIN_3, OUTPUT);
  pinMode(J5_PIN_4, OUTPUT);
*/

  /*
    if (SPEAKER_OUT > 0)
    {a
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


  cola_ble_tx_1 = xQueueCreate(5, 20);
  cola_ble_tx_2 = xQueueCreate(5, 20);
  cola_ble_tx_3 = xQueueCreate(5, 20);


  xTaskCreatePinnedToCore(
    Task_ePaper,
    "Task_ePaper",
    10000,
    NULL,
    1,
    &Task_Handle_ePaper,
    0);                           // Core

  xTaskCreatePinnedToCore(
    Task_ble,
    "Task BLE",
    10000,
    NULL,
    1,
    &Task_Handle_ble,
    1);                           // Core

  xTaskCreatePinnedToCore(
    Task_UARTs,
    "Task UART",
    2000,
    NULL,
    1,
    &Task_Handle_uart,
    1);                           // Core
    
  xTaskCreatePinnedToCore(
    Task_Sensores_temperatura,
    "Task Temperatura",
    10000,
    NULL,
    1,
    &Task_Handle_Sensor_temperatura,
    1);                           // Core

    

}

void loop()  {} 
