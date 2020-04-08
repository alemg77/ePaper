// Display 2,9 pulgadas 296 x 128 píxeles

// Coneccion del ePaPer
#define ELINK_BUSY      4
#define ELINK_RESET     12
#define ELINK_DC        19
#define ELINK_SS        5

// Coneccion de la memoria SD
#define SPI_MOSI        23
#define SPI_MISO        2
#define SPI_CLK         18
#define SDCARD_SS       13


#define BUTTON_1        38
#define BUTTON_2        37
#define BUTTON_3        39


#define PULSADOR_1      37      // Tiene pull up externo 
#define PULSADOR_2      38      // Tiene pull up externo 
#define PULSADOR_3      39      // Tiene pull up externo 
#define LED             26


#define SPEAKER_OUT     25

// Conector J5
// PIN 1 --> GND
// PIN 2 --> +5V
// PIN 3 --> IO21
// PIN 4 --> IO22
// PIN 5 --> +3,3V

#define J5_PIN_3        21
#define J5_PIN_4        22

// Conetor JP1
  #define JP1_PIN_1       S
  #define JP1_PIN_2       0
//#define JP1_PIN_3       +3,3Vcc
//#define JP1_PIN_4       +5Vcc
//#define JP1_PIN_5       U0TXD   // Serial programacion 
//#define JP1_PIN_6       U0RXD   // Serial programacion 
//#define JP1_PIN_7       SPI_MISO // 2
  #define JP1_PIN_8       15
//#define JP1_PIN_9       SDCARD_SS // 13
  #define JP1_PIN_10      14
  #define JP1_PIN_11      27
  #define JP1_PIN_12      26
  #define JP1_PIN_13      34
  #define JP1_PIN_14      33
  #define JP1_PIN_15      32
//#define JP1_PIN_16      ELINK_BUSY  // 4
//#define JP1_PIN_17      ELINK_RESET
//#define JP1_PIN_18      ELINK_DC
//#define JP1_PIN_19      ELINK_SS
//#define JP1_PIN_20      SPI_CLK // 18
//#define JP1_PIN_21      SPI_MOSI // 23
//#define JP1_PIN_22      GND
//#define JP1_PIN_23      VBAT
//#define JP1_PIN_24      P




#define FILESYSTEM SPIFFS

/*100 * 100 bmp fromat*/
//https://www.onlineconverter.com/jpg-to-bmp
#define BADGE_CONFIG_FILE_NAME "/badge.data"
#define DEFALUT_AVATAR_BMP "/avatar.bmp"
#define DEFALUT_QR_CODE_BMP "/qr.bmp"
#define CHANNEL_0 0
