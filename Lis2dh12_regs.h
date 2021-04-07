/**
* @file    LIS2DH12.h
* @version 0.0.1
* @author  Jurica Resetar, Rafaella Neofytou (changes)
* @brief   Header file of the Lis2dh12 driver module. Changed to fit cav project. 
* 
*/ 

#ifndef LIS2DH12_REGS_H
#define LIS2DH12_REGS_H

#define LIS2DH12_ADRESS (0x19)
#define I2C_ADDRESS     (0b00110010)
#define WHO_AM_I        (0x0F)
#define CTRL_REG0       (0x1E)
#define CTRL_REG1       (0x20)
#define CTRL_REG2       (0x21)
#define CTRL_REG3       (0x22)
#define CTRL_REG4       (0x23)
#define CTRL_REG5       (0x24)
#define CTRL_REG6       (0x25)
#define REFERENCE       (0x26)
#define STATUS          (0x27)
#define OUT_X_L         (0x28)
#define OUT_X_H         (0x29)
#define OUT_Y_L         (0x2A)
#define OUT_Y_H         (0x2B)
#define OUT_Z_L         (0x2C)
#define OUT_Z_H         (0x2D)
#define FIFO_CTRL_REG   (0x2E)
#define FIFO_SRC_REG    (0x2F)
#define INT1_CFG        (0x30)
#define INT1_SRC        (0x31)
#define INT1_THS        (0x32)
#define INT1_DURATION   (0x33)
#define INT2_CFG        (0x34)
#define INT2_SRC        (0x35)
#define INT2_THS        (0x36)
#define INT2_DURATION   (0x37)
#define CLICK_CFG       (0x38)
#define CLICK_SRC       (0x39)
#define CLICK_THS       (0x3A)
#define TIME_LIMIT      (0x3B)
#define TIME_LATENCY    (0x3C)
#define TIME_WINDOW     (0x3D)
#define ACT_THS         (0x3E)
#define ACT_DUR         (0x3F)


#define X_EN				0x01
#define Y_EN				0x02
#define Z_EN				0x04
#define LPEN				0x08
#define ODR_10Hz			0x20

#define	HPF_CUTOFF_F0		0x00
#define	HP_IA1				0x01

#define	I1_IA1			    0x40

#define HIRES_MODE	        0x08
#define FS_2G				0x00


#define LIR_INT1		    0x08

// Threshold event status bits
#define	XLIE			0x01
#define	XHIE			0x02
#define	YLIE			0x04
#define	YHIE			0x08
#define	ZLIE			0x10
#define	ZHIE			0x20

 
 
#endif