/**
* @file    LIS2DH12.h
* @version 0.0.1
* @author  Jurica Resetar, Rafaella Neofytou (changes)
* @brief   Header file of the Lis2dh12 driver module. Changed to fit cav project. 
* 
*/

#ifndef LIS2DH12_H
#define LIS2DH12_H
 
#include "mbed.h"
#include "aconno_i2c.h"
#include "Lis2dh12_regs.h"
#include <cstdint>
 
enum Mode
{
    HIGH_RES = 0,
    NORMAL,
    LOW_POWER,
};
 
enum Axis
{
    X_axis = 0x01,
    Y_axis = 0x02,
    Z_axis = 0x04,
};
 
enum Odr
{
    PowerDown = 0x00,
    ODR_1Hz = 0x01,
   // ODR_10Hz = 0x02,
    ODR_25Hz = 0x03,
    ODR_50Hz = 0x04,
    ODR_100Hz = 0x05,
    ODR_200Hz = 0x06,
    ODR_400Hz = 0x07,
    ODR_1620Hz = 0x08,
    ODR_Max = 0x09,         // HighRes/Normal -> 1.344kHz, LowPower -> 5.376kHz
};
 
enum Scale
{
    _2g = 0x00,
    _4g = 0x01,
    _8g = 0x02,
    _16g = 0x03,
};

enum ERROR_RETURN
{
    SUCCESS = 0,
    READ_FAILURE,
    WRITE_FAILURE,
};
 
class Lis2dh12
{
    public:
        Lis2dh12(I2C *i2c_, char address);
        Lis2dh12(SPI *_spi, DigitalOut *_cs);
        uint8_t whoIAm();
        uint8_t setMode(Mode mode);
        uint8_t enableAxes(Axis axis);
        uint8_t disableAxes(Axis axis);
        int16_t readXAxis();
        int16_t readYAxis();
        int16_t readZAxis();
        uint8_t setODR(Odr odr);
        uint8_t setScale(Scale scale);
        uint8_t int1Setup(uint8_t setup);
        uint8_t int1Latch(uint8_t enable);
        uint8_t int1Duration(uint8_t duration);
        uint8_t int1Threshold(uint8_t threshold);
        uint8_t int1Config(uint8_t config);
        void clearIntFlag();
        uint8_t ReadInt();
        uint8_t InitInterrupt();
        uint8_t ClearInterrupt();
        uint8_t ThresholdConfigure(char u8Level, char u8Duration, char u8Mode);
        uint8_t LowPowerMode();
        uint8_t InterruptStatus();
        bool DetectInactive();


    private:
        aconno_i2c i2c;
        SPI *spi;
        DigitalOut *cs;
        bool spiInterface;
        uint8_t readFromReg(uint8_t regAddr, uint8_t *buff, size_t buffSize);
        uint8_t writeToReg(uint8_t regAddr, uint8_t *buff, size_t buffSize);
 
};
 
 
#endif