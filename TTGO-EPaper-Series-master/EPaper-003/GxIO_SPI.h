#ifndef _GxIO_SPI_H_
#define _GxIO_SPI_H_

#include <SPI.h>

class GxIO
{
  public:
    GxIO() {};
    const char* name = "GxIO";
    virtual void reset();
    virtual void init();
    virtual void setFrequency(uint32_t freq){}; // for SPI
    virtual void setClockDivider(uint32_t clockDiv){}; // for SPI
    virtual uint8_t transferTransaction(uint8_t d);
    virtual uint16_t transfer16Transaction(uint16_t d);
    virtual uint8_t readDataTransaction();
    virtual uint16_t readData16Transaction();
    virtual uint8_t readData();
    virtual uint16_t readData16();
    virtual void writeCommandTransaction(uint8_t c);
    virtual void writeDataTransaction(uint8_t d);
    virtual void writeData16Transaction(uint16_t d, uint32_t num = 1);
    virtual void writeCommand(uint8_t c);
    virtual void writeData(uint8_t d);
    virtual void writeData(uint8_t* d, uint32_t num);
    virtual void writeData16(uint16_t d, uint32_t num = 1);
    virtual void writeAddrMSBfirst(uint16_t d);
    virtual void startTransaction();
    virtual void endTransaction();
    virtual void selectRegister(bool rs_low) {}; // for generalized readData & writeData (RA8875)
    virtual void setBackLight(bool lit);
};

class GxIO_SPI : public GxIO
{
  public:
    GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
    const char* name = "GxIO_SPI";
    void reset();
    void init();
    void setFrequency(uint32_t freq); // for SPI
    uint8_t transferTransaction(uint8_t d);
    uint16_t transfer16Transaction(uint16_t d);
    uint8_t readDataTransaction();
    uint16_t readData16Transaction();
    uint8_t readData();
    uint16_t readData16();
    void writeCommandTransaction(uint8_t c);
    void writeDataTransaction(uint8_t d);
    void writeData16Transaction(uint16_t d, uint32_t num = 1);
    void writeCommand(uint8_t c);
    void writeData(uint8_t d);
    void writeData(uint8_t* d, uint32_t num);
    void writeData16(uint16_t d, uint32_t num = 1);
    void writeAddrMSBfirst(uint16_t d);
    void startTransaction();
    void endTransaction();
    void selectRegister(bool rs_low); // for generalized readData & writeData (RA8875)
    void setBackLight(bool lit);
  protected:
    SPIClass& _spi;
    SPISettings _spi_settings;
    int8_t _cs, _dc, _rst, _bl; // Control lines
};


#endif
