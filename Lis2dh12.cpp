/**
* @file    LIS2DH12.cpp
* @version 0.0.1
* @author  Jurica Resetar, Rafaella Neofytou (changes)
* @brief   C++ file of the Lis2dh12 driver module. Changed to fit cav project
*/
 
#include "Lis2dh12.h"
#include "Lis2dh12_regs.h"
#include <cstdint>

uint8_t success = SUCCESS; /* 0 on success (ack), non-0 on failure (nack) */

Lis2dh12::Lis2dh12(I2C *i2c_, char address) : i2c(i2c_, address)
{
}
uint8_t Lis2dh12::whoIAm()
{
    char regAddr = (char)WHO_AM_I;
    char regData = 0;
    success = i2c.readFromReg(regAddr, &regData, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    
    return (uint8_t)regData;
}
 
uint8_t Lis2dh12::setMode(Mode mode)
{
    char ctrl1Copy;
    char ctrl4Copy;
    
    success = i2c.readFromReg((char)CTRL_REG1, &ctrl1Copy, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    success = i2c.readFromReg((char)CTRL_REG4, &ctrl4Copy, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    switch(mode){
        case HIGH_RES:
            ctrl1Copy &= 0xF7;
            ctrl4Copy |= 0x08;
            break;
        case NORMAL:
            ctrl1Copy &= 0xF7;
            ctrl4Copy &= 0xF7;
            break;
        case LOW_POWER:
            ctrl1Copy |= 0x08;
            ctrl4Copy &= 0xF7;
            break;
        default:
            return 0;
    }
    success = i2c.writeToReg((char)CTRL_REG1, &ctrl1Copy, 1);
    if (success != SUCCESS)
    {
        return WRITE_FAILURE;
    }
    success = i2c.writeToReg((char)CTRL_REG4, &ctrl4Copy, 1);
    if (success != SUCCESS)
    {
        return WRITE_FAILURE;
    }
    return SUCCESS;
}
 
uint8_t Lis2dh12::enableAxes(Axis axis)
{
    char ctrl1Copy;
    
    success = i2c.readFromReg((char)CTRL_REG1, &ctrl1Copy, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    ctrl1Copy |= axis;
    success = i2c.writeToReg((char)CTRL_REG1, &ctrl1Copy, 1);
    if (success != SUCCESS)
    {
        return WRITE_FAILURE;
    }
    return success;
}
 
uint8_t Lis2dh12::disableAxes(Axis axis)
{
    char ctrl1Copy;
    success = i2c.readFromReg((char)CTRL_REG1, &ctrl1Copy, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    
    ctrl1Copy &= ~(1 << axis);
    i2c.writeToReg((char)CTRL_REG1, &ctrl1Copy, 1);
    return 0;
}
 
int16_t Lis2dh12::readXAxis()
{
    int16_t rawData;
    char tempData;
    // Make sure new data is ready
    
    // do{
    //     i2c.readFromReg((char)STATUS, &tempData, 1);
       
    // }while(!(tempData & 0x08));
    // do{
    //     i2c.readFromReg((char)STATUS, &tempData, 1);
       
    // }while(!(tempData & 0x80));

    // Same data have been overwritten
    
    // i2c.readFromReg((char)OUT_X_H, &tempData, 1);
    // rawData = (int8_t)tempData << 8;
    success = i2c.readFromReg((char)OUT_X_L, (char*)&rawData, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }

    success = i2c.readFromReg((char)OUT_X_H, ((char*)&rawData)+1, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    
    if (rawData >= 0)
        rawData = (rawData>>4);
    else
        rawData = (rawData>>4) | 0xF000;
        
    return rawData;
}
 
int16_t Lis2dh12::readYAxis()
{
    int16_t rawData;
    char tempData;
    //i2c.readFromReg((char)OUT_Y_H, &tempData, 1);
    //rawData = (int8_t)tempData << 8;
    success=i2c.readFromReg((char)OUT_Y_L, (char*)&rawData, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    success=i2c.readFromReg((char)OUT_Y_H, ((char*)&rawData)+1, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    
    if (rawData >= 0)
        rawData = (rawData>>4);
    else
        rawData = (rawData>>4) | 0xF000;
        
    return rawData;
}
 
int16_t Lis2dh12::readZAxis()
{
    int16_t rawData = 0;
    char tempData;
    //i2c.readFromReg((char)OUT_Z_H, &tempData, 1);
    //rawData = (int8_t)tempData << 8;
    success = i2c.readFromReg((char)OUT_Z_L, (char*)&rawData, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }

    success = i2c.readFromReg((char)OUT_Z_H, ((char*)&rawData)+1, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    
    if (rawData >= 0)
        rawData = (rawData>>4);
    else
        rawData = (rawData>>4) | 0xF000;
        
    return rawData;
}
 
uint8_t Lis2dh12::setODR(Odr odr)
{
    char ctrl1Copy;
    i2c.readFromReg((char)CTRL_REG1, &ctrl1Copy, 1);
    ctrl1Copy |= (odr << 4);
    i2c.writeToReg((char)CTRL_REG1, &ctrl1Copy, 1);
    return 0;
}
 
uint8_t Lis2dh12::setScale(Scale scale)
{
    char ctrl4Copy;
    i2c.readFromReg((char)CTRL_REG4, &ctrl4Copy, 1);
    ctrl4Copy |= (scale << 4);
    i2c.writeToReg((char)CTRL_REG4, &ctrl4Copy, 1);
    return 0;
}
 
/* Interrupt activity 1 driven to INT1 pad */
// TODO: Napraviti tako da postoji samo jedna metoda int1Setup koja prima gro 
// parametara: THS, DUR, Latch...
/*CTRL_REG3 [Interrupt CTRL register] (22h) 
    Default 0x0000000
    to enable 0x0001000 dec numb 8



*/
uint8_t Lis2dh12::int1Setup(uint8_t setup)
{
    char data = setup;
    i2c.writeToReg((char)CTRL_REG3, &data, 1); 
    return 0;
}
 
uint8_t Lis2dh12::int1Latch(uint8_t enable)
{
    char ctrl5Copy;
    i2c.readFromReg((char)CTRL_REG5, &ctrl5Copy, 1);
    ctrl5Copy |= enable;
    i2c.writeToReg((char)CTRL_REG5, &ctrl5Copy, 1);
    return 0; 
}
 
uint8_t Lis2dh12::int1Duration(uint8_t duration)
{
    char copy = duration;
    i2c.writeToReg((char)INT1_DURATION, &copy, 1);
    return 0;
}
 
uint8_t Lis2dh12::int1Threshold(uint8_t threshold)
{
    char copy = threshold;
    i2c.writeToReg((char)INT1_THS, &copy, 1);
    return 0;
}
 
uint8_t Lis2dh12::int1Config(uint8_t config)
{
    char copy = config;
    i2c.writeToReg((char)INT1_CFG, &copy, 1);
    return 0;
}
 
void Lis2dh12::clearIntFlag()
{
    char data;
    i2c.readFromReg((char)INT1_SRC, (char*)&data, 1);
}
 

 uint8_t Lis2dh12::ReadInt()
 {
    int16_t rawData;
    i2c.readFromReg((char)INT1_SRC, (char*)&rawData, 1);
    if (rawData >= 0)
    {
        rawData = (rawData>>4);
    }
        
    else{
        rawData = (rawData>>4) | 0xF000;
    }
    return rawData;
        
}

uint8_t Lis2dh12::InitInterrupt()
{

    char copy = 0x27;
    i2c.writeToReg((char)CTRL_REG1, &copy, 1); ///lowpower MODE LPEN 1

    copy = 0x00;
    i2c.writeToReg((char)CTRL_REG2, &copy, 1);

    copy = 0x40;
    i2c.writeToReg((char)CTRL_REG3, &copy, 1);

    copy = 0x90;
    i2c.writeToReg((char)CTRL_REG4, &copy, 1); ///NORMAL MODE HR 0

    copy = 0x08;
    i2c.writeToReg((char)CTRL_REG5, &copy, 1);

    copy = 0x10;
    i2c.writeToReg((char)INT1_THS, &copy, 1);

    copy = 0x00;
    i2c.writeToReg((char)INT1_DURATION, &copy, 1);

    copy = 0x6A;//A
    i2c.writeToReg((char)INT1_CFG, &copy, 1);

    // copy = 0x02;
    // i2c.writeToReg((char)CTRL_REG6, &copy, 1);

    // copy = 0x00;
    // i2c.writeToReg((char)ACT_THS , &copy, 1);

    // copy = 0x05;
    // i2c.writeToReg((char)ACT_DUR , &copy, 1);

    return SUCCESS;

}


uint8_t Lis2dh12::ThresholdConfigure(char u8Level, char u8Duration, char u8Mode)
{

    char copy;
     // Enable X,Y,Z sensors and set a default sample rate
    copy = (ODR_10Hz | X_EN | Y_EN | Z_EN);
    i2c.writeToReg((char)CTRL_REG1, &copy, 1);

    // Enable high-pass filtering with highest cut-off frequency
	// and unfiltered samples to the data registers

    copy = (HPF_CUTOFF_F0 | HP_IA1);
    i2c.writeToReg((char)CTRL_REG2, &copy, 1);

    // Enable INT1 interrupts
    copy = I1_IA1;
    i2c.writeToReg((char)CTRL_REG3, &copy, 1);
	
    // Select measurement range to +/- 2g, 12-bit resolution
    copy = HIRES_MODE | FS_2G;
    i2c.writeToReg((char)CTRL_REG4, &copy, 1);
    
    // Set wake-up threshold level
    
    i2c.writeToReg((char)INT1_THS, &u8Level, 1);
		
	// Set duration that threshold needs to be held
    // Set wake-up threshold level
    copy = u8Duration;
    i2c.writeToReg((char)INT1_DURATION, &u8Duration, 1);
	

	// Enable interrupt on INT1 pin
//	boInterruptEvent = false;
    copy = LIR_INT1;
    i2c.writeToReg((char)CTRL_REG5, &copy, 1);
	
	
	// Read reference register to force HP filters to current
	// acceleration/tilt value
    char data;
    i2c.readFromReg((char)REFERENCE, (char*)&data, 1);
	

    i2c.writeToReg((char)INT1_CFG, &u8Mode, 1);

    return 0;
}

bool Lis2dh12::DetectInactive()
{
    
    char tempData = 0;
    int temp, temporary = 0;
    int status=0;
   
    for(int i = 0; i <1000; i++)
    {
       ThisThread::sleep_for(20ms);
       uint8_t status = InterruptStatus();
       if(status & (XHIE | YHIE | ZHIE))
       {
           return 1;
       }
        // i2c.readFromReg((char)STATUS, &tempData, 1);
        // if (int(tempData & 0x08) != 0 )
        // {
        //    // ThisThread::sleep_for(200ms);
        //     i2c.readFromReg((char)STATUS, &tempData, 1);
        //     if(int(tempData & 0x80) != 0 ){
        //         temporary = 1;
        //         do
        //         {
        //             status=readXAxis();
        //            // ThisThread::sleep_for(200ms);

        //         }while(status == 1);
        //         do{
        //             status=readYAxis();

                    
        //         }while(status == 1);
        //         do
        //         {
        //             status=readZAxis();
        //             //ThisThread::sleep_for(200ms);
                    
        //         }while(status == 1);

        //         // char data;
        //         // i2c.readFromReg((char)REFERENCE, (char*)&data, 1);

                
        //         return 1;
        //     }
            
        //      ThisThread::sleep_for(5ms);
        // }

         //i2c.readFromReg((char)STATUS, &tempData, 1);
        // int temporary = int(tempData);
         temp = temp + temporary;
    }
   
    // if (temp == 0)
    // {
    //     return false;
    // }   
    return 0;
}


uint8_t Lis2dh12::InterruptStatus()
{

    char data;
    i2c.readFromReg((char)INT1_SRC, (char*)&data, 1);
	return data;
}


uint8_t Lis2dh12::ClearInterrupt()
{
    char data;
    char copy;

    i2c.readFromReg((char)INT1_SRC, (char*)&data, 1);
    if (success != SUCCESS)
    {
        return READ_FAILURE;
    }
    return 0;   
}

uint8_t Lis2dh12::LowPowerMode(){
    
    char copy;
    // ODR_PDOWN
    copy = 0x47;
    success = i2c.writeToReg((char)CTRL_REG1, &copy, 1);
    if (success != SUCCESS){
        return WRITE_FAILURE;
    }
    copy = 0x23;
    success = i2c.writeToReg((char)CTRL_REG4, &copy, 1);
    if (success != SUCCESS){
        return WRITE_FAILURE;
    }
    return 0;   
}