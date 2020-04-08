#include "H.h"
#include <OneWire.h>
#include <DallasTemperature.h>

float Temperatura[4];


// GPIO where the DS18B20 is connected to
#define ONE_WIRE_BUS J5_PIN_3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// Number of temperature devices found
int numberOfDevices;

// We'll use this variable to store a found device address
DeviceAddress tempDeviceAddress;

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void Task_Sensores_temperatura  (void *parametro_task) {

  static float Temperatura_anterior1[4];
  static float Temperatura_anterior2[4];
  static float Temperatura_anterior3[4];
  static float Temperatura_pd[4];
  // Start up the library
  sensors.begin();

  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();

  Serial.printf("Se encontraron %d sensores de temperatura\n", numberOfDevices);

  // Loop through each device, print out address
  for (int i = 0; i < numberOfDevices; i++) {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      sensors.setResolution(tempDeviceAddress, 12);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }
  sensors.requestTemperatures(); // Send the command to get temperatures
  for (int i = 0; i < numberOfDevices; i++) {
    if (sensors.getAddress(tempDeviceAddress, i)) {
      float tempC = sensors.getTempC(tempDeviceAddress);
      Temperatura_anterior3[i] = tempC;
      Temperatura_anterior2[i] = tempC;
      Temperatura_anterior1[i] = tempC;
      Temperatura[i] = tempC;
    }
  }

  while (1) {
    vTaskDelay(1);
    sensors.requestTemperatures(); // Send the command to get temperatures

    // Loop through each device, print out temperature data
    for (int i = 0; i < numberOfDevices; i++) {
      // Search the wire for address
      if (sensors.getAddress(tempDeviceAddress, i)) {
        float tempC = sensors.getTempC(tempDeviceAddress);
        Temperatura_anterior3[i] = Temperatura_anterior2[i] ;
        Temperatura_anterior2[i] = Temperatura_anterior1[i] ;
        Temperatura_anterior1[i] = Temperatura[i];
        Temperatura[i] = tempC;
        Temperatura_pd[i] = Temperatura[i] + (Temperatura[i] - Temperatura_anterior3[i]) * 2.5 ;
        if ( i == 2 ) {
          Serial.printf("T%d = %.1fºC %.1f°C", i, Temperatura[i], Temperatura_pd[i]);
        }
      }
    }
    Serial.println("");
    vTaskDelay(1000);
  }
}
