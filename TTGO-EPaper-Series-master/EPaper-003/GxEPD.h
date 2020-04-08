// class GxEPD : Base Class for Display Classes for e-Paper Displays from Dalian Good Display Co., Ltd.: www.good-display.com
//

#ifndef _GxEPD_H_
#define _GxEPD_H_

#include <Arduino.h>
#include <SPI.h>
#include "GxIO_SPI.h"
#include <Adafruit_GFX.h>
#include "GxFont_GFX.h"

#define GxEPD_BLACK     0x0000
#define GxEPD_WHITE     0xFFFF
#define GxEPD_RED       0xF800      /* 255,   0,   0 */

//class GxEPD : public Adafruit_GFX
class GxEPD : public GxFont_GFX
{
  public:
    // bitmap presentation modes may be partially implemented by subclasses
    enum bm_mode //BM_ModeSet
    {
      bm_normal = 0,
      bm_default = 1, // for use for BitmapExamples
      // these potentially can be combined
      bm_invert = (1 << 1),
      bm_flip_x = (1 << 2),
      bm_flip_y = (1 << 3),
      bm_r90 = (1 << 4),
      bm_r180 = (1 << 5),
      bm_r270 = bm_r90 | bm_r180,
      bm_partial_update = (1 << 6),
      bm_invert_red = (1 << 7),
      bm_transparent = (1 << 8)
    };
  public:
    //GxEPD(int16_t w, int16_t h) : Adafruit_GFX(w, h) {};
    GxEPD(int16_t w, int16_t h) : GxFont_GFX(w, h) {};
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void init(uint32_t serial_diag_bitrate = 0) = 0; // = 0 : disabled
    virtual void fillScreen(uint16_t color) = 0; // to buffer
    virtual void update(void) = 0;
    // to buffer, may be cropped, drawPixel() used, update needed, subclass may support some modes
    virtual void drawBitmap(const uint8_t *bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t m = bm_normal) = 0;
    // to buffer, may be cropped, drawPixel() used, update needed, subclass may support some modes, default for example bitmaps
    virtual void drawExampleBitmap(const uint8_t *bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t m = bm_default)
    {
      drawBitmap(bitmap, x, y, w, h, color, m);
    };
    // monochrome or 4 gray or other to full screen, filled with white if size is less, no update needed
    virtual void drawPicture(const uint8_t *picture, uint32_t size) // b/w or grey is class specific
    {
      drawBitmap(picture, size); // default is monochrome
    };
    // to full screen, filled with white if size is less, no update needed, black  /white / red, for example bitmaps
    virtual void drawExamplePicture(const uint8_t* black_bitmap, const uint8_t* red_bitmap, uint32_t black_size, uint32_t red_size){};
    // to full screen, filled with white if size is less, no update needed, black  /white / red, general version
    virtual void drawPicture(const uint8_t* black_bitmap, const uint8_t* red_bitmap, uint32_t black_size, uint32_t red_size, int16_t mode = bm_normal){};
    // monochrome to full screen, filled with white if size is less, no update needed
    virtual void drawBitmap(const uint8_t *bitmap, uint32_t size, int16_t m = bm_normal) = 0; // monochrome
    virtual void drawExampleBitmap(const uint8_t *bitmap, uint32_t size, int16_t m = bm_default) // monochrome
    {
      drawBitmap(bitmap, size, m);
    };
    virtual void eraseDisplay(bool using_partial_update = false) {};
    // partial update of rectangle from buffer to screen, does not power off
    virtual void updateWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool using_rotation = true) {};
  protected:
    void drawBitmapBM(const uint8_t *bitmap, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color, int16_t m);
    static inline uint16_t gx_uint16_min(uint16_t a, uint16_t b) {return (a < b ? a : b);};
    static inline uint16_t gx_uint16_max(uint16_t a, uint16_t b) {return (a > b ? a : b);};
};

#endif