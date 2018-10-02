#ifndef _INCLUDE_H_
#define _INCLUDE_H_
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"
#include "OLED.h"
#include "delay.h"
#include "stm32f4xx.h" 
#include "../HARDWARE/TIMER/timer.h"
#include "../HARDWARE/Driver.h"
#include "../Control/Schedule.h"
#include "../HARDWARE/PLOT/SDS.h"
#include "Config.h"
#include "Debug.h"
#include "../MPU6050/imu.h"
#include "../MPU6050/mpu6050_driver.h"
#include "../MPU6050/mpu6050_i2c.h"
#include "../MPU6050/mpu6050_interrupt.h"
#include "../MPU6050/mpu6050_process.h"
#include "../PLOT/DataScope_DP.H"
#include "../Control/Controller.h"
#include "../HARDWARE/SDRAM/SDRAM.h"
//#include "../HARDWARE/FATFS/ff.h"
//#include "../HARDWARE/FATFS/drivers/fatfs_sd_sdio.h"
////#include "../HARDWARE/FATFS/drivers/fatfs_flash_spi.h"
//#include "../HARDWARE/FATFS/integer.h"
//#include "../HARDWARE/FATFS/diskio.h"


#define	digitalHi(p,i)			{p->BSRRL=i;}			  //设置为高电平		
#define digitalLo(p,i)			{p->BSRRH=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态
#define GPIOAout(n) BIT_ADDR(GPIOA_ODR_Addr,n) //GPIOA ?????
#define GPIOAin(n) BIT_ADDR(GPIOA_IDR_Addr,n) //GPIOA ?????
#define GPIOBout(n) BIT_ADDR(GPIOB_ODR_Addr,n) //GPIOB ?????
#define GPIOBin(n) BIT_ADDR(GPIOB_IDR_Addr,n) //GPIOB ?????
#define GPIOCout(n) BIT_ADDR(GPIOC_ODR_Addr,n) //GPIOC ?????
#define GPIOCin(n) BIT_ADDR(GPIOC_IDR_Addr,n) //GPIOC ?????
#define GPIODout(n) BIT_ADDR(GPIOD_ODR_Addr,n) //GPIOD ?????
#define GPIODin(n) BIT_ADDR(GPIOD_IDR_Addr,n) //GPIOD ?????
#define GPIOEout(n) BIT_ADDR(GPIOE_ODR_Addr,n) //GPIOE ?????
#define GPIOEin(n) BIT_ADDR(GPIOE_IDR_Addr,n) //GPIOE ?????
#define GPIOFout(n) BIT_ADDR(GPIOF_ODR_Addr,n) //GPIOF ?????
#define GPIOFin(n) BIT_ADDR(GPIOF_IDR_Addr,n) //GPIOF ?????
#define GPIOGout(n) BIT_ADDR(GPIOG_ODR_Addr,n) //GPIOG ?????
#define GPIOGin(n) BIT_ADDR(GPIOG_IDR_Addr,n) //GPIOG ?????
#define GPIOHout(n) BIT_ADDR(GPIOH_ODR_Addr,n) //GPIOH ?????
#define GPIOHin(n) BIT_ADDR(GPIOH_IDR_Addr,n) //GPIOH ?????
#define GPIOIout(n) BIT_ADDR(GPIOI_ODR_Addr,n) //GPIOI ?????
#define GPIOIin(n) BIT_ADDR(GPIOI_IDR_Addr,n) //GPIOI ?????
#endif
