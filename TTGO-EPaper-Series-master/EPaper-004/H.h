#include "board_def.h"
#include "SD.h"
#include "Arduino.h"
#include "SPI.h"
#include <SPIFFS.h>
#include <FS.h>


typedef enum {
  RIGHT_ALIGNMENT = 0,
  LEFT_ALIGNMENT,
  CENTER_ALIGNMENT,
} Text_alignment;


extern void displayInit(void);
extern void Borrar_display (void);
extern void Actualizar_pantalla (void);
extern void displayText(const String &str, int16_t y, uint8_t alignment);
extern void Texto_grande(const String &str, int16_t y, uint8_t alignment);
extern void drawBitmap(const char *filename, int16_t x, int16_t y, bool with_color);
extern void Borrar_parcialmente ( uint16_t x, uint16_t y, uint16_t w, uint16_t h);
