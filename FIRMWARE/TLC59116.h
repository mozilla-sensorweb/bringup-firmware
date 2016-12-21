/****************************************************************************
       Module: TLC59116.h
     Engineer: Martin Hannon
  Description: Contains function prototypes for accessing the TLC59116 
               LED driver.
Date           Initials    Description
10-DEC-2016    MH          Initial
****************************************************************************/

typedef enum
{
   LED_BANK_0 = 0,
   LED_BANK_1 = 1,
   LED_BANK_2 = 2,
   LED_BANK_3 = 3

} TyLedBank;

typedef enum
{
   LED_BLUE = 0,
   LED_GREEN = 1,
   LED_RED = 2
} TyLedColour;

typedef enum
{
   LED_100 = 130,
   LED_90  = 117,
   LED_80  = 104,
   LED_70  = 91,
   LED_60  = 78,
   LED_50  = 65,
   LED_40  = 52,
   LED_30  = 39,
   LED_20  = 26,
   LED_10  = 13,
   LED_0   = 0

} TyLedIntensity;


unsigned char TLC59116_Initialise(void);
unsigned char TLC59116_LedColourIntensity(TyLedBank tyLedBank, TyLedColour tyLedColour, TyLedIntensity tyLedIntensity);
unsigned char TLC59116_LedBankBlinkControl(TyLedBank tyLedBank, unsigned char bEnableBlinking);
unsigned char TLC59116_GlobalBlinkRate(unsigned char ucFrequency, unsigned char ucDutyCycle);
