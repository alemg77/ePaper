// class GxFont_GFX : Font Rendering Graphics Switch and Bridge Class
//
// This class allows to connect GxEPD to additional font rendering classes.
//
// U8G2_FOR_ADAFRUIT_GFX: Arduino Library that makes all U8G2 fonts available (Oliver Kraus)
// avaliable from: https://github.com/olikraus/U8g2_for_Adafruit_GFX
//
// GxFont_GFX_TFT_eSPI: fonts and font rendering of TFT_eSPI library (Bodmer)
// available here: https://github.com/ZinggJM/GxFont_GFX_TFT_eSPI
//
// Adafruit_ftGFX: a Adafruit_GFX variant with different fonts.
// need to use modified clone from: https://github.com/ZinggJM/Adafruit_ftGFX
// (no additional fonts, as all are now part of Adafruit_GFX, but fonts above 7bit character set)
//
// Author : J-M Zingg
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// Library: https://github.com/ZinggJM/GxEPD
//
// NOTE: you need to SAVE any modified example to a saveable location for UTF-8 characters to work
//       e.g. for Umlauts
//
//#define DIAG_UTF8(x) x // uncomment for Serial diagnostic of character codes > 127

#ifndef _GxFont_GFX_H_
#define _GxFont_GFX_H_

#include <Arduino.h>
#include <SPI.h>
#include "GxIO_SPI.h"
#include <Adafruit_GFX.h>
#include "GxFont_GFX.h"

#define GxEPD_BLACK     0x0000
#define GxEPD_WHITE     0xFFFF
#define GxEPD_RED       0xF800      /* 255,   0,   0 */


// select the library/libraries to add, none to preserve code space
//#include <U8g2_for_Adafruit_GFX.h>
//#include <Adafruit_ftGFX.h>
//#include <GxFont_GFX_TFT_eSPI.h>

class GxFont_GFX : public Adafruit_GFX{
  public:
    GxFont_GFX(int16_t w, int16_t h);
    void setFont(const GFXfont *f = NULL);
#if defined(U8g2_for_Adafruit_GFX_h)
    void setFont(const uint8_t *font); // set u8g2 font
#endif
#if defined(_ADAFRUIT_TF_GFX_H_)
    void setFont(uint8_t f);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
#ifdef LOAD_GFXFF
    void setFreeFont(const GFXfont *f = NULL);
    void setTextFont(uint8_t font);
#else
    void setFreeFont(uint8_t font);
    void setTextFont(uint8_t font);
#endif
#endif
#if defined(U8g2_for_Adafruit_GFX_h) || defined(_ADAFRUIT_TF_GFX_H_) || defined(_GxFont_GFX_TFT_eSPI_H_)
    void setCursor(int16_t x, int16_t y);
    size_t write(uint8_t);
    int16_t getCursorX(void) const;
    int16_t getCursorY(void) const;
#endif
#if defined(U8g2_for_Adafruit_GFX_h)
    void home(void);
    void setFontMode(uint8_t is_transparent);      // is_transparent==0: Background is not drawn
    void setFontDirection(uint8_t d);              // 0; 0 degree, 1: 90 degree, 2: 180 degree, 3: 270 degree
    void setForegroundColor(uint16_t fg);           // Use this color to draw the text
    void setBackgroundColor(uint16_t bg);           // only used for setFontMode(0)
    int8_t getFontAscent(void);
    int8_t getFontDescent(void);
    int8_t getFontHeight(void);
    int16_t drawGlyph(int16_t x, int16_t y, uint16_t e);
    int16_t drawStr(int16_t x, int16_t y, const char *s);
    int16_t drawUTF8(int16_t x, int16_t y, const char *str);
    uint16_t utf8_next(uint8_t b);
#endif
#if defined(_ADAFRUIT_TF_GFX_H_) || defined(_GxFont_GFX_TFT_eSPI_H_)
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
    void setTextColor(uint16_t c);
    void setTextColor(uint16_t c, uint16_t bg);
    void setTextSize(uint8_t s);
    void setTextWrap(boolean w);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    void setTextDatum(uint8_t datum);
    void setTextPadding(uint16_t x_width);
    uint8_t getTextDatum(void);
    uint8_t color16to8(uint16_t color565); // Convert 16 bit colour to 8 bits
    uint16_t fontsLoaded(void);
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
    uint16_t color8to16(uint8_t color332);  // Convert 8 bit colour to 16 bits
    int16_t drawNumber(long long_num, int poX, int poY, int font);
    int16_t drawNumber(long long_num, int poX, int poY);
    int16_t drawFloat(float floatNumber, int decimal, int poX, int poY, int font);
    int16_t drawFloat(float floatNumber, int decimal, int poX, int poY);
    // Handle char arrays
    int16_t drawString(const char *string, int poX, int poY, int font);
    int16_t drawString(const char *string, int poX, int poY);
    // Handle String type
    int16_t drawString(const String& string, int poX, int poY, int font);
    int16_t drawString(const String& string, int poX, int poY);
    int16_t textWidth(const char *string, int font);
    int16_t textWidth(const char *string);
    int16_t textWidth(const String& string, int font);
    int16_t textWidth(const String& string);
    int16_t fontHeight(int16_t font);
#endif
  private:
#if defined(U8g2_for_Adafruit_GFX_h)
    class U8G2_FONTS_GFX : public U8G2_FOR_ADAFRUIT_GFX
    {
      public:
        U8G2_FONTS_GFX(Adafruit_GFX& gfx) : _gfx(gfx)
        {
          begin(gfx);
        };
        void drawPixel(int16_t x, int16_t y, uint16_t color)
        {
          _gfx.drawPixel(x, y, color);
        };
        size_t write(uint8_t v)
        {
          if (v == '\n') // Newline?
          {
            switch (u8g2.font_decode.dir)
            {
              case 0:
                tx = 0;
                ty += u8g2.font_info.max_char_height;
                break;
              // these need to be verified
              case 1:
                tx += u8g2.font_info.max_char_height;
                ty = 0;
                break;
              case 2:
                tx = 0;
                ty -= u8g2.font_info.max_char_height;
                break;
              case 3:
                tx -= u8g2.font_info.max_char_height;
                ty = 0;
                break;
            }
            return 1;
          }
          else
          {
            return U8G2_FOR_ADAFRUIT_GFX::write(v);
          }
        };
      private:
        Adafruit_GFX& _gfx;
    };
    U8G2_FONTS_GFX _U8G2_FONTS_GFX;
#endif
#if defined(_ADAFRUIT_TF_GFX_H_)
    class GxF_Adafruit_ftGFX : public Adafruit_ftGFX
    {
      public:
        GxF_Adafruit_ftGFX(GxFont_GFX& container, int16_t w, int16_t h) : Adafruit_ftGFX(w, h), _container(container) {};
        void drawPixel(int16_t x, int16_t y, uint16_t color);
      private:
        GxFont_GFX& _container;
    };
    GxF_Adafruit_ftGFX _GxF_Adafruit_ftGFX;
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    class GxF_GxFont_GFX_TFT_eSPI : public GxFont_GFX_TFT_eSPI
    {
      public:
        GxF_GxFont_GFX_TFT_eSPI(GxFont_GFX& container, int16_t w, int16_t h) : GxFont_GFX_TFT_eSPI(w, h), _container(container) {};
        void drawPixel(uint32_t x, uint32_t y, uint32_t color);
        void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
        void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
      private:
        GxFont_GFX& _container;
    };
    GxF_GxFont_GFX_TFT_eSPI _GxF_GxFont_GFX_TFT_eSPI;
#endif
    uint16_t _font_gfx;
};


class GxEPD : public GxFont_GFX{
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
