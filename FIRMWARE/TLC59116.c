/****************************************************************************
       Module: TLC59116.c
     Engineer: Martin Hannon
  Description: Contains routines for accessing the TLC59116 LED driver
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/
#include "includes.h"

// TLC59116 slave address....
#define TLC59116_DEVICE_ADDR         0x60

// TLC59116 registers...
#define TLC59116_MODE1           0x00
#define TLC59116_MODE2           0x01
#define TLC59116_PWM0            0x02
#define TLC59116_PWM1            0x03
#define TLC59116_PWM2            0x04
#define TLC59116_PWM3            0x05
#define TLC59116_PWM4            0x06
#define TLC59116_PWM5            0x07
#define TLC59116_PWM6            0x08
#define TLC59116_PWM7            0x09
#define TLC59116_PWM8            0x0A
#define TLC59116_PWM9            0x0B
#define TLC59116_PWM10           0x0C
#define TLC59116_PWM11           0x0D
#define TLC59116_PWM12           0x0E
#define TLC59116_PWM13           0x0F
#define TLC59116_PWM14           0x10
#define TLC59116_PWM15           0x11
#define TLC59116_GRPPWM          0x12
#define TLC59116_GRPFREQ         0x13
#define TLC59116_LEDOUT0         0x14
#define TLC59116_LEDOUT1         0x15
#define TLC59116_LEDOUT2         0x16
#define TLC59116_LEDOUT3         0x17

// TLC59116 register values...
#define TLC59116_MODE1_DEFAULT    0x00   // Default (no sub or all call) + OSC on
#define TLC59116_MODE2_DEFAULT    0x20   // Default (output change on stop)
#define TLC59116_LEDOUT_PWM       0xAA   // LDRx = 10 -> PWM; 4 leds per reg: 10101010b -> 0xAA
#define TLC59116_LEDOUT_PWM_BLINK 0xFF   // LDRx = 11 -> PWM+BLINK; 4 leds per reg: 11111111b -> 0xFF

#define TLC59116_BLINK_500MS_SEC_FREQ  12

/****************************************************************************
     Function: TLC59116_Initialise
     Engineer: Martin Hannon
        Input: N/A
       Output: TRUE: Success, FALSE: Failure.
  Description: Initialises the TLC59116 LED controller
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/
unsigned char TLC59116_Initialise(void)
{
   unsigned char i;
   unsigned char pucTxRxData[0x2];

   // Program the Mode 1 register....
   pucTxRxData[0] =  TLC59116_MODE1;
   pucTxRxData[1] =  TLC59116_MODE1_DEFAULT;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   // Program the Mode 2 register....
   pucTxRxData[0] =  TLC59116_MODE2;
   pucTxRxData[1] =  TLC59116_MODE2_DEFAULT;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }


   // Set all PWM values to 0x00 (off)....
   for (i=0; i < 16; i++)
      {
      pucTxRxData[0] =  TLC59116_PWM0 + i;
      pucTxRxData[1] =  0;

      if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
         {
         return FALSE;
         }
      }

   // Set leds to PWM control....
   for (i=0; i < 4; i++)
      {
      pucTxRxData[0] =  TLC59116_LEDOUT0 + i;
      pucTxRxData[1] =  TLC59116_LEDOUT_PWM;

      if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
         {
         return FALSE;
         }
      }


   // Set the default blink frequency....
   pucTxRxData[0] =  TLC59116_GRPFREQ;
   pucTxRxData[1] =  TLC59116_BLINK_500MS_SEC_FREQ;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   // Set the default blink duty cycle....
   pucTxRxData[0] =  TLC59116_GRPPWM;
   pucTxRxData[1] =  TLC59116_BLINK_500MS_SEC_FREQ * 2;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   return TRUE;
}


/****************************************************************************
     Function: TLC59116_LedColourIntensity
     Engineer: Martin Hannon
        Input: TyLedBank tyLedBank: LED bank to control (0 to 3)
               TyLedColour tyLedColour: LED colour to control (red, green or blue).
               TyLedIntensity tyLedIntensity: 100%, 75%, 50%, 25% or 0%.
       Output: TRUE: Success, FALSE: Failure.
  Description: Configures the intensity of the specified LED colour in the 
               specified bank.
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/
unsigned char TLC59116_LedColourIntensity(TyLedBank tyLedBank, TyLedColour tyLedColour, TyLedIntensity tyLedIntensity)
{
   unsigned char pucTxRxData[0x2];

   pucTxRxData[0]  = TLC59116_PWM0;
   pucTxRxData[0] += ((unsigned char)tyLedBank * 4); // Bump the address by the bank number.
   pucTxRxData[0] += (unsigned char)tyLedColour;     // Bump the address by the LED colour.
   pucTxRxData[1] =  (unsigned char)tyLedIntensity;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   return TRUE;
}



/****************************************************************************
     Function: TLC59116_LedBankBlinkControl
     Engineer: Martin Hannon
        Input: TyLedBank tyLedBank: LED bank to control (0 to 3)
               unsigned char bEnableBlinking: TRUE = Enable Blinking
       Output: TRUE: Success, FALSE: Failure.
  Description: Enables / disables blinking for the specified bank.
               specified bank.
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/
unsigned char TLC59116_LedBankBlinkControl(TyLedBank tyLedBank, unsigned char bEnableBlinking)
{
   unsigned char pucTxRxData[0x2];

   pucTxRxData[0] =  TLC59116_LEDOUT0 + (unsigned char)tyLedBank;

   if (bEnableBlinking)
      {
      pucTxRxData[1] =  TLC59116_LEDOUT_PWM_BLINK;
      }
   else
      {
      pucTxRxData[1] =  TLC59116_LEDOUT_PWM;
      }


   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   return TRUE;
}


/****************************************************************************
     Function: TLC59116_GlobalBlinkRate
     Engineer: Martin Hannon
        Input: unsigned char ucFrequency: 0 = 24Hz. 0xFF = 10.73 seconds
               unsigned char ucDutyCycle: 0 = 24Hz. 0xFF = 10.73 seconds
       Output: TRUE: Success, FALSE: Failure.
  Description: Configures the blink rate used by all LED banks.
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/
unsigned char TLC59116_GlobalBlinkRate(unsigned char ucFrequency, unsigned char ucDutyCycle)
{
   unsigned char pucTxRxData[0x2];

   pucTxRxData[0] =  TLC59116_GRPFREQ;
   pucTxRxData[1] =  ucFrequency;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   pucTxRxData[0] =  TLC59116_GRPPWM;
   pucTxRxData[1] =  ucDutyCycle;

   if (I2C_IF_Write(TLC59116_DEVICE_ADDR,pucTxRxData,2,1) != SUCCESS)
      {
      return FALSE;
      }

   return TRUE;
}
