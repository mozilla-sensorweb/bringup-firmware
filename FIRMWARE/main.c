/****************************************************************************
       Module: main.c
     Engineer: Martin Hannon
  Description: Contains the main high level function for the firmware.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
#include "includes.h"


#define LED_INTENSITY_DELAY_STEP  300000  // 300000 microseconds

//*****************************************************************************
//                  Local variables for the PPD42NJ sensor
//*****************************************************************************
static double        dLocalPPD42NJ_P1Accumulative;
static double        dLocalPPD42NJ_P2Accumulative;
static unsigned long ulLocalPPD42NJ_TimeStamp;
static unsigned char bLocalPPD42NJ_DataAvailable;


//*****************************************************************************
//                      Global Variables for Vector Table
//*****************************************************************************
#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

/****************************************************************************
     Function: BoardInit
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Initialises the processor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
static void BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs) || defined(gcc)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


/****************************************************************************
     Function: PPD42NJNotificationCallback
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Callback function invoked when MAXIMUM_HISTORY_IN_SECONDS of
               data is available from the PPD42NJ device.
Date           Initials    Description
13-DEC-2016    MH          Initial
****************************************************************************/
void PPD42NJNotificationCallback(void)
{
   unsigned char i;
   TyAirQualityMeasurements tyAirQualityMeasurements;

   dLocalPPD42NJ_P1Accumulative = 0;
   dLocalPPD42NJ_P2Accumulative = 0;

   if (PPD42NJ_GetAirQualityMeasurements(&tyAirQualityMeasurements) == TRUE)
      {
      for (i=0; i < MAXIMUM_HISTORY_IN_SECONDS; i++)
         {
         dLocalPPD42NJ_P1Accumulative += tyAirQualityMeasurements.pulP1Times[i];
         dLocalPPD42NJ_P2Accumulative += tyAirQualityMeasurements.pulP2Times[i];
         }

      // Divide by MAXIMUM_HISTORY_IN_SECONDS to get a PER second value....
      dLocalPPD42NJ_P1Accumulative /= MAXIMUM_HISTORY_IN_SECONDS;
      dLocalPPD42NJ_P2Accumulative /= MAXIMUM_HISTORY_IN_SECONDS;

      ulLocalPPD42NJ_TimeStamp = tyAirQualityMeasurements.ulSecondsElapsed;

      bLocalPPD42NJ_DataAvailable = TRUE;
      }

}


/****************************************************************************
     Function: main
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Min firmware function.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
void main(void)
{
   unsigned char i, ucIntensity;
   double dTemperature, dHumidity, dPPD42NJ_P1Accumulative, dPPD42NJ_P2Accumulative;

   // Global variable initialisation....
   dLocalPPD42NJ_P1Accumulative = 0.0;
   dLocalPPD42NJ_P2Accumulative = 0.0;
   bLocalPPD42NJ_DataAvailable  = FALSE;

   // Function variable initialisation....
   dPPD42NJ_P1Accumulative = 0.0;
   dPPD42NJ_P2Accumulative = 0.0;

   // Initialize board configurations...
   BoardInit();
   //
   // Pinmuxing...
   PinMuxConfig();

   // Configure the UART...
   InitTerm();

   UART_PRINT("Firmware Startup.\n\r\n\r");

   // I2C Init...
   I2C_IF_Open(I2C_MASTER_MODE_FST);

   // Initialise the HDC1080 device...
   if (HDC1080_Initialise() != TRUE)
      {
	   UART_PRINT("Failed to initialise the HDC1080 device\n\r");
      return;
      }
   UART_PRINT("HDC1080 Device Initialised.\n\r");

   // Initialise the PPD42NJ device...
   if (PPD42NJ_Initialise() != TRUE)
      {
	   UART_PRINT("Failed to initialise the PPD42NJ device\n\r");
      return;
      }
   // Configure the max history callback...
   if (PPD42NJ_SetupNotifications(NOTIFICATION_MAX_HISTORY_UPDATE, PPD42NJNotificationCallback) != TRUE)
      {
	   UART_PRINT("Failed to initialise the PPD42NJ callback\n\r");
      return;
      }

   UART_PRINT("PPD42NJ Device Initialised.\n\r");

   // Initialise the TLC59116 device...
   if (TLC59116_Initialise() != TRUE)
      {
	   UART_PRINT("Failed to initialise the TLC59116 device\n\r");
      return;
      }

   // Set the LED blink control for each bank...
   if ((TLC59116_LedBankBlinkControl(LED_BANK_0, FALSE) == FALSE) ||
       (TLC59116_LedBankBlinkControl(LED_BANK_1, FALSE) == FALSE) ||
       (TLC59116_LedBankBlinkControl(LED_BANK_2, FALSE) == FALSE) ||
       (TLC59116_LedBankBlinkControl(LED_BANK_3,  TRUE) == FALSE))
      {
	   UART_PRINT("Failed to set the LED blink control.\n\r");
      return;
      }

   // Set the LED intensity for Bank 3 (Blue + Green + Red)....
   if ((TLC59116_LedColourIntensity(LED_BANK_3, LED_BLUE , LED_50 ) == FALSE) ||
       (TLC59116_LedColourIntensity(LED_BANK_3, LED_GREEN, LED_50) == FALSE) ||
       (TLC59116_LedColourIntensity(LED_BANK_3, LED_RED  , LED_50  ) == FALSE))
      {
	   UART_PRINT("\n\rFailed to set intensity level for Bank 3\n\r");
      return;
      }

   UART_PRINT("TLC59116 Device Initialised.\n\r");

	while(1)
	   {
      for (i=0; i <= 10; i++)
         {
         switch (i)
            {
            case 0:
               ucIntensity = LED_0;
            break;
            case 1:
               ucIntensity = LED_10;
            break;
            case 2:
               ucIntensity = LED_20;
            break;
            case 3:
               ucIntensity = LED_30;
            break;
            case 4:
               ucIntensity = LED_40;
            break;
            case 5:
               ucIntensity = LED_50;
            break;
            case 6:
               ucIntensity = LED_60;
            break;
            case 7:
               ucIntensity = LED_70;
            break;
            case 8:
               ucIntensity = LED_80;
            break;
            case 9:
               ucIntensity = LED_90;
            break;
            case 10:
               ucIntensity = LED_100;
            break;
            default:
            break;
            }

         // Set the LED intensity for Bank 0 (Blue)....
         if (TLC59116_LedColourIntensity(LED_BANK_0, LED_BLUE , (TyLedIntensity)ucIntensity ) == FALSE)
            {
	         UART_PRINT("\n\rFailed to set intensity level for Bank 0\n\r");
            return;
            }
         // Set the LED intensity for Bank 1 (Green)....
         if (TLC59116_LedColourIntensity(LED_BANK_1, LED_GREEN , (TyLedIntensity)ucIntensity ) == FALSE)
            {
	         UART_PRINT("\n\rFailed to set intensity level for Bank 1\n\r");
            return;
            }

         // Set the LED intensity for Bank 2 (Red)....
         if (TLC59116_LedColourIntensity(LED_BANK_2, LED_RED , (TyLedIntensity)ucIntensity ) == FALSE)
            {
	         UART_PRINT("\n\rFailed to set intensity level for Bank 2\n\r");
            return;
            }

         TIMER_Delay(LED_INTENSITY_DELAY_STEP);
         }

      if (bLocalPPD42NJ_DataAvailable)
         {
         // Capture new data from the PPD42NJ...
         dPPD42NJ_P1Accumulative = dLocalPPD42NJ_P1Accumulative;
         dPPD42NJ_P2Accumulative = dLocalPPD42NJ_P2Accumulative;

         // Read the current temperature from the HDC1080...
         if (HDC1080_ReadTemperature(&dTemperature) == FALSE)
            {
	         UART_PRINT("\n\rFailed to read temperature from the HDC1080\n\r");
            return;
            }
         // Read the current humidity from the HDC1080...
         if (HDC1080_ReadHumidity(&dHumidity) == FALSE)
            {
	         UART_PRINT("\n\rFailed to read humidity from the HDC1080\n\r");
            return;
            }

         #if 0
         // Not sure why, but vsnprintf doesn't seem to be dealing with %f properly
	      UART_PRINT("Temperature %.2f Humidity %.2f P1_Total %.2f P2_Total %.2f, Timestamp %ld\n\r", dTemperature, dHumidity, dPPD42NJ_P1Accumulative, dPPD42NJ_P2Accumulative, ulLocalPPD42NJ_TimeStamp);
         #else
         {
            int temp = dTemperature * 100.0;
            int humidity = dHumidity * 100.0;
            int accum1 = dPPD42NJ_P1Accumulative * 100.0;
            int accum2 = dPPD42NJ_P2Accumulative * 100.0;
            UART_PRINT("Temperature %d.%02d Humidity %d.%02d P1_Total %d.%02d P2_Total %d.%02d, Timestamp %ld\n\r",
                       temp / 100, temp % 100, humidity / 100, humidity % 100,
                       accum1 / 100, accum1 % 100, accum2 / 100, accum2 % 100, ulLocalPPD42NJ_TimeStamp);
         }
         #endif

         bLocalPPD42NJ_DataAvailable = FALSE;
         }
	   }
}



