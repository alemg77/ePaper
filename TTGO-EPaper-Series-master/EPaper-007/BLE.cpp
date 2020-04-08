#include "H.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define NOMBRE_BLUETOOTH          "A6 ePaper"
#define SERVICE_UUID              "00000001-0001-1111-2222-333333333333"
#define CHARACTERISTIC_UUID_1     "00000002-0001-1111-2222-333333333333"
#define CHARACTERISTIC_UUID_2     "00000003-0001-1111-2222-333333333333"
#define CHARACTERISTIC_UUID_3     "00000004-0001-1111-2222-333333333333"

#define MAXIMUN_HANDLES         10

extern xQueueHandle cola_ble_tx_1, cola_ble_tx_2, cola_ble_tx_3;

unsigned long clock_tx;

char buffer_bluetooth[2048];
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool nuevo_dato_bluetooth;

BLEServer *pServer = NULL;
BLECharacteristic * pBLE_1;
BLECharacteristic * pBLE_2;
BLECharacteristic * pBLE_3;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      // Serial.println("BLE CONECTADO!!");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      // Serial.println("BLE DESCONECTADO!!");
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        //Serial.print("Llego por Bluetooth");
        //Serial.print(rxValue.length());
        // Serial.println("bytes");

        unsigned int i;
        for (i = 0; i < (rxValue.length() - 2); i++)
        {
          buffer_bluetooth[i] = rxValue[i];
        }
        buffer_bluetooth[i] = 0;
        nuevo_dato_bluetooth = true;
      }
    }

    void onRead(BLECharacteristic *pCharacteristic) {
      Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>");
    }

};

void Enviar_a_cola_ble_1 (char *vector) {
  int bytes = strlen(vector);
  if ( bytes > 20 )
  {
    vector[20] = 0;
  }
  xQueueSend(cola_ble_tx_1, vector, 0);
}
void Enviar_a_cola_ble_2 (char *vector) {
  int bytes = strlen(vector);
  if ( bytes > 20 )
  {
    vector[20] = 0;
  }
  if ( pdTRUE != xQueueSend(cola_ble_tx_2, vector, 0) )
  {
    Serial.println("cola_ble_tx_2 esta llena");
  }
}
void Enviar_a_cola_ble_3 (char *vector) {
  int bytes = strlen(vector);
  if ( bytes > 20 )
  {
    vector[20] = 0;
  }
  xQueueSend(cola_ble_tx_3, vector, 0);
}

void Enviar_bluetooth_1 (const char *vector) {
  int bytes = strlen(vector);
  int i = 0;
  while ( i < bytes )
  {
    if (( i + 20 ) < bytes )
    {
      pBLE_1->setValue((uint8_t *)&vector[i], 20 );
    }
    else
    {
      pBLE_1->setValue((uint8_t *)&vector[i], bytes - i );
    }
    pBLE_1->notify();
    i += 20;
  }
}
void Enviar_bluetooth_2 (const char *vector) {
  int bytes = strlen(vector);
  int i = 0;
  while ( i < bytes )
  {
    if (( i + 20 ) < bytes )
    {
      pBLE_2->setValue((uint8_t *)&vector[i], 20 );
    }
    else
    {
      pBLE_2->setValue((uint8_t *)&vector[i], bytes - i );
    }
    pBLE_2->notify();
    i += 20;
  }
}
void Enviar_bluetooth_3 (const char *vector) {
  int bytes = strlen(vector);
  int i = 0;
  while ( i < bytes )
  {
    if (( i + 20 ) < bytes )
    {
      pBLE_3->setValue((uint8_t *)&vector[i], 20 );
    }
    else
    {
      pBLE_3->setValue((uint8_t *)&vector[i], bytes - i );
    }
    pBLE_3->notify();
    i += 20;
  }
}

void Task_ble (void *parametro_task) {
  // Create the BLE Device
  BLEDevice::init(NOMBRE_BLUETOOTH);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);


  pBLE_3 = pService->createCharacteristic(CHARACTERISTIC_UUID_3, BLECharacteristic::PROPERTY_NOTIFY);
  pBLE_3->addDescriptor(new BLE2902());
  vTaskDelay(250);

  // Create a BLE Characteristic
  pBLE_2 = pService->createCharacteristic(CHARACTERISTIC_UUID_2, BLECharacteristic::PROPERTY_NOTIFY);
  pBLE_2->addDescriptor(new BLE2902());
  vTaskDelay(250);

  // Create a BLE Characteristic
  pBLE_1 = pService->createCharacteristic(CHARACTERISTIC_UUID_1, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
  pBLE_1->addDescriptor(new BLE2902());
  pBLE_1->setCallbacks(new MyCallbacks());
  vTaskDelay(250);

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  Serial.print("Server BLE: ");
  Serial.println(NOMBRE_BLUETOOTH);

  while (1) {
    vTaskDelay(1);

    if (deviceConnected) {
      if ( ( millis() - clock_tx ) > 10000 )   {
        if ( pdPASS != xQueueSend(cola_ble_tx_3, "Salida 3\n", 0) )
        {
          Serial.println("Cola ble 3 llena!");
        }
        clock_tx = millis();
      }
      else if ( nuevo_dato_bluetooth )
      {
        nuevo_dato_bluetooth = false;
        clock_tx = millis();
        if ( 0 == strcmp(buffer_bluetooth, "togle") )
        {
          Enviar_bluetooth_1("Comando togle\n");
          Serial.println("Comando togle");
        }
        else
        {
          Serial.print("Llego por ble: ");
          Serial.println(buffer_bluetooth);
        }
      }
      else {
        char vector_aux[21];
        if ( pdPASS == xQueueReceive( cola_ble_tx_1, vector_aux, 0 ) ) {
          Enviar_bluetooth_1(vector_aux);
        }
        else if ( pdPASS == xQueueReceive( cola_ble_tx_2, vector_aux, 0 ) ) {
          Enviar_bluetooth_2(vector_aux);
        }
        else if ( pdPASS == xQueueReceive( cola_ble_tx_3, vector_aux, 0 ) ) {
          Enviar_bluetooth_3(vector_aux);
        }
      }
    }

    if (!deviceConnected && oldDeviceConnected) {
      Serial.print("Dispocitivo desconectado...  ");
      vTaskDelay(1000); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      Serial.println("  listo para nueva coneccion.");
      oldDeviceConnected = deviceConnected;
    }

    if (deviceConnected && !oldDeviceConnected) {
      vTaskDelay(1000); // give the bluetooth stack the chance to get things ready
      Serial.println("Dispocitivo conectado");
      xQueueReset(cola_ble_tx_1);
      xQueueReset(cola_ble_tx_2);
      xQueueReset(cola_ble_tx_3);
      Enviar_a_cola_ble_1("Bienvenido a 1\n");
      Enviar_a_cola_ble_2("Bienvenido a 2\n");
      Enviar_a_cola_ble_3("Bienvenido a 3\n");

      oldDeviceConnected = deviceConnected;
      clock_tx = millis();
    }
  }
}
