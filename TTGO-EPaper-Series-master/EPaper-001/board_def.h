// Display 2,9 pulgadas 296 x 128 píxeles

#define TTGO_T5_2_2 1








#define ELINK_BUSY 4
#define ELINK_RESET 12
#define ELINK_DC 19
#define ELINK_SS 5

#define SPI_MOSI 23
#define SPI_MISO 2
#define SPI_CLK 18

#define SDCARD_SS 13
#define BUTTON_1 38
#define BUTTON_2 37
#define BUTTON_3 39

#define SPEAKER_OUT   25


#define FILESYSTEM SPIFFS

/*100 * 100 bmp fromat*/
//https://www.onlineconverter.com/jpg-to-bmp
#define BADGE_CONFIG_FILE_NAME "/badge.data"
#define DEFALUT_AVATAR_BMP "/avatar.bmp"
#define DEFALUT_QR_CODE_BMP "/qr.bmp"
#define CHANNEL_0 0
