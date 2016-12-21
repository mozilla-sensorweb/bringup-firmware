/****************************************************************************
       Module: HDC1080.c
     Engineer: Martin Hannon
  Description: Contains routines for accessing the HDC1080 
               temperature / humidity sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
#include "includes.h"

// HDC1080 slave address....
#define HDC1080_DEVICE_ADDR         0x40

// HDC1080 registers...
#define TEMPERATURE_REG 	0x00
#define HUMIDITY_REG 		0x01
#define CONFIGURATION_REG 	0x02

// HDC1080 configuration word....
#define CONFIG_HIGH_BYTE  0x00 // Default Reset value (Heater disabled, 14 bit resolution)
#define CONFIG_LOW_BYTE   0x00 // All reserved bits.

#define RESET_BIT_MASK    0x80 // Bit mask to do a soft reset in CONFIG_HIGH_BYTE
#define HEAT_BIT_MASK     0x20 // Bit mask to enable the heater in CONFIG_HIGH_BYTE.

// HDC1080 delay times for powerup to readiness state (15ms)...
// Delay values are as per the HDC1080 datasheet.
#define POWERUP_DELAY          15000 // 15000 microseconds


/****************************************************************************
     Function: HDC1080_Initialise
     Engineer: Martin Hannon
        Input: N/A
       Output: TRUE: Success, FALSE: Failure.
  Description: Initialises the HDC1080 sensor
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char HDC1080_Initialise(void)
{
   unsigned char pucTxRxData[0x3];

   // Program the configuration register....
   pucTxRxData[0] =  CONFIGURATION_REG;
   pucTxRxData[1] =  CONFIG_HIGH_BYTE;

   // Set the reset bit to do a soft reset....
   pucTxRxData[1] |= RESET_BIT_MASK;
   
   pucTxRxData[2] =  CONFIG_LOW_BYTE;

   if (I2C_IF_Write(HDC1080_DEVICE_ADDR,pucTxRxData,3,1) != SUCCESS)
   {
      return FALSE;
   }


   // Wait for the device to complete the powerup sequence...
   TIMER_Delay(POWERUP_DELAY);

   return TRUE;
}

/****************************************************************************
     Function: HDC1080_HeaterControl
     Engineer: Martin Hannon
        Input: unsigned char bEnable: 
                    TRUE = Enable heater. FALSE = Disable heater.
       Output: TRUE: Success, FALSE: Failure.
  Description: Control function for enabling / disabling the heater.
Date           Initials    Description
12-DEC-2016    MH          Initial
****************************************************************************/
unsigned char HDC1080_HeaterControl(unsigned char bEnable)
{
   unsigned char pucTxRxData[0x3];

   // Program the configuration register....
   pucTxRxData[0] =  CONFIGURATION_REG;
   pucTxRxData[1] =  CONFIG_HIGH_BYTE;

   if (bEnable)
   {
      pucTxRxData[1] |= HEAT_BIT_MASK;
   }

   pucTxRxData[2] =  CONFIG_LOW_BYTE;

   if (I2C_IF_Write(HDC1080_DEVICE_ADDR,pucTxRxData,3,1) != SUCCESS)
   {
      return FALSE;
   }

   return TRUE;
}

/****************************************************************************
     Function: HDC1080_ReadTemperature
     Engineer: Martin Hannon
        Input: double *pdTemperature: Storage for temperature value.
       Output: TRUE: Success, FALSE: Failure.
  Description: Reads the temperature value (in degrees C) from the HDC1080 
               sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char HDC1080_ReadTemperature(double *pdTemperature)
{
   unsigned char pucTxRxData[0x2];
   double dTemperature;

   pucTxRxData[0] =  TEMPERATURE_REG;

   // Trigger the measurement by writing TEMPERATURE_REG to the pointer register...
   if (I2C_IF_Write(HDC1080_DEVICE_ADDR,pucTxRxData,1,0) != SUCCESS)
   {
      return FALSE;
   }

   // Read the result...
   while (I2C_IF_Read(HDC1080_DEVICE_ADDR,pucTxRxData,2) != SUCCESS)
   {
   ;;
   }

   dTemperature = pucTxRxData[0x0];
   dTemperature *= 0x100;
   dTemperature += pucTxRxData[0x1];

   dTemperature = (dTemperature / 0x10000) * 165 - 40; // As per HDC1080 datasheet

   *pdTemperature = dTemperature;

   return TRUE;
}

/****************************************************************************
     Function: HDC1080_ReadHumidity
     Engineer: Martin Hannon
        Input: double *pdHumidity: Storage for humidity.
       Output: TRUE: Success, FALSE: Failure.
  Description: Reads the humidity value (in %) from the HDC1080 sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char HDC1080_ReadHumidity(double *pdHumidity)
{
   unsigned char pucTxRxData[0x2];
   double dHumidity;

   pucTxRxData[0] =  HUMIDITY_REG;

   // Trigger the measurement by writing HUMIDITY_REG to the pointer register...
   if (I2C_IF_Write(HDC1080_DEVICE_ADDR,pucTxRxData,1,0) != SUCCESS)
   {
      return FALSE;
   }

   // Read the result...
   while (I2C_IF_Read(HDC1080_DEVICE_ADDR,pucTxRxData,2) != SUCCESS)
   {
   ;;
   }

   dHumidity = pucTxRxData[0x0];
   dHumidity *= 0x100;
   dHumidity += pucTxRxData[0x1];

   dHumidity = (dHumidity / 0x10000) * 100; // As per HDC1080 datasheet

   *pdHumidity    = dHumidity;

   return TRUE;
}

