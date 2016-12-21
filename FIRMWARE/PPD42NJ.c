/****************************************************************************
       Module: PPD42NJ.c
     Engineer: Martin Hannon
  Description: Contains routines for accessing the PPD42NJ
               particle sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
#include "includes.h"


#define P1_GPIO_BASE       GPIOA1_BASE
#define P1_GPIO_INTERRUPT  GPIO_INT_PIN_5

#define P2_GPIO_BASE       GPIOA1_BASE
#define P2_GPIO_INTERRUPT  GPIO_INT_PIN_4

static volatile unsigned long ulLocalSecondCounter;

static volatile unsigned long ulLocalP1FallTime;
static volatile unsigned long ulLocalP2FallTime;

static volatile unsigned long ulLocalP1Accumulated; // In 1 us units
static volatile unsigned long ulLocalP2Accumulated; // In 1 us units

static volatile TyAirQualityMeasurements tyLocalAirQualityMeasurements;

static TyNotificationCallback tyLocalOneSecondCallback;
static TyNotificationCallback tyLocalMaxHistoryCallback;


/****************************************************************************
     Function: PPD42NJ_TimerInterrupt
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Interrupt handler for the PPD42NJ timer interrupt
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
static void PPD42NJ_TimerInterrupt(void)
{
   unsigned char i;
   // Clear the timer interrupt.
   Timer_IF_InterruptClear(TIMERA0_BASE);

   // Bump the local second counter...
   ulLocalSecondCounter++;

   // Update the air quality measurements...
   tyLocalAirQualityMeasurements.ulSecondsElapsed = ulLocalSecondCounter;

   // Shift all measurements through the FIFO....
   for (i=1; i < MAXIMUM_HISTORY_IN_SECONDS; i++)
      {
      tyLocalAirQualityMeasurements.pulP1Times[i-1] = tyLocalAirQualityMeasurements.pulP1Times[i];
      tyLocalAirQualityMeasurements.pulP2Times[i-1] = tyLocalAirQualityMeasurements.pulP2Times[i];
      }

   // Add in the latest measurements at the end....
   tyLocalAirQualityMeasurements.pulP1Times[MAXIMUM_HISTORY_IN_SECONDS-1] = ulLocalP1Accumulated;
   tyLocalAirQualityMeasurements.pulP2Times[MAXIMUM_HISTORY_IN_SECONDS-1] = ulLocalP2Accumulated;

   // Reset the accumulated counts...
   ulLocalP1Accumulated = 0;
   ulLocalP2Accumulated = 0;

   // Invoke the callbacks if configured....
   if (tyLocalOneSecondCallback != NULL)
      tyLocalOneSecondCallback();
   if (tyLocalMaxHistoryCallback != NULL)
      {
      if ((ulLocalSecondCounter % MAXIMUM_HISTORY_IN_SECONDS) == 0)
         tyLocalMaxHistoryCallback();
      }
}


/****************************************************************************
     Function: PPD42NJ_PortLineInterrupt
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Interrupt handler for the P1 / P1 inputs.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
static void PPD42NJ_PortLineInterrupt(void)
{
   long lInterruptStatus;
   unsigned long ulCurrentTimer;
   double dDownTime;


   lInterruptStatus = MAP_GPIOIntStatus(P1_GPIO_BASE, true);

   if (lInterruptStatus & P1_GPIO_INTERRUPT)
   {
      MAP_GPIOIntClear(P1_GPIO_BASE, P1_GPIO_INTERRUPT);

      if (GPIOPinRead(P1_GPIO_BASE, P1_GPIO_INTERRUPT) == 0)
         {
         // Falling edge...
         ulLocalP1FallTime = MAP_TimerValueGet(TIMERA0_BASE, TIMER_A);
         }
      else
         {
         if (ulLocalP1FallTime != 0xFFFFFFFF)
            {
            // Rising edge...
            ulCurrentTimer = MAP_TimerValueGet(TIMERA0_BASE, TIMER_A);

            if (ulCurrentTimer < ulLocalP1FallTime)
               {
               dDownTime = MILLISECONDS_TO_TICKS(1000ul);
               dDownTime -= ulLocalP1FallTime;
               dDownTime += ulCurrentTimer;
               }
            else
               {
               dDownTime = ulCurrentTimer - ulLocalP1FallTime;
               }

           // dDownTime is in 12.5 ns units. Change to 1 us units...
           dDownTime /= 80;

           ulLocalP1Accumulated += (unsigned long)dDownTime;
           ulLocalP1FallTime = 0xFFFFFFFF;
         }
      }
   }


   lInterruptStatus = MAP_GPIOIntStatus(P2_GPIO_BASE, true);

   if (lInterruptStatus & P2_GPIO_INTERRUPT)
      {
      MAP_GPIOIntClear(P2_GPIO_BASE, P2_GPIO_INTERRUPT);

      if (GPIOPinRead(P2_GPIO_BASE, P2_GPIO_INTERRUPT) == 0)
      {
         // Falling edge...
         ulLocalP2FallTime = MAP_TimerValueGet(TIMERA0_BASE, TIMER_A);
      }
      else
      {
         if (ulLocalP2FallTime != 0xFFFFFFFF)
            {
            // Rising edge...
            ulCurrentTimer = MAP_TimerValueGet(TIMERA0_BASE, TIMER_A);

            if (ulCurrentTimer < ulLocalP2FallTime)
               {
               dDownTime = MILLISECONDS_TO_TICKS(1000ul);
               dDownTime -= ulLocalP2FallTime;
               dDownTime += ulCurrentTimer;
               }
            else
               {
               dDownTime = ulCurrentTimer - ulLocalP2FallTime;
               }

          // dDownTime is in 12.5 ns units. Change to 1 us units...
          dDownTime /= 80;

          ulLocalP2Accumulated += (unsigned long)dDownTime;
          ulLocalP2FallTime = 0xFFFFFFFF;
         }
      }
   }
}

/****************************************************************************
     Function: PPD42NJ_Initialise
     Engineer: Martin Hannon
        Input: N/A
       Output: TRUE: Success, FALSE: Failure.
  Description: Initialises the PPD42NJ sensor
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char PPD42NJ_Initialise(void)
{
   unsigned char i;

   // Initialise the local variables....
   ulLocalSecondCounter = 0;
   ulLocalP1FallTime = 0xFFFFFFFF;
   ulLocalP2FallTime = 0xFFFFFFFF;
   ulLocalP1Accumulated = 0;
   ulLocalP2Accumulated = 0;
   tyLocalOneSecondCallback = NULL;
   tyLocalMaxHistoryCallback = NULL;

   // Reset the air quality measurements...
   tyLocalAirQualityMeasurements.ulSecondsElapsed = 0;

   // Reset all the measurements through the FIFO....
   for (i=0; i < MAXIMUM_HISTORY_IN_SECONDS; i++)
      {
      tyLocalAirQualityMeasurements.pulP1Times[i] = 0;
      tyLocalAirQualityMeasurements.pulP2Times[i] = 0;
      }

   // Initial the TIMERA for a 1 second periodic timeout...
   Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC_UP, TIMER_A, 0);
   Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, PPD42NJ_TimerInterrupt);
   Timer_IF_Start(TIMERA0_BASE, TIMER_A, 1000ul);

   // Configure the port line interrupts....
   GPIO_IF_ConfigureNIntEnable(P1_GPIO_BASE, P1_GPIO_INTERRUPT, GPIO_BOTH_EDGES, PPD42NJ_PortLineInterrupt);
   GPIO_IF_ConfigureNIntEnable(P2_GPIO_BASE, P2_GPIO_INTERRUPT, GPIO_BOTH_EDGES, PPD42NJ_PortLineInterrupt);
    
   return TRUE;
}


/****************************************************************************
     Function: PPD42NJ_SetupNotifications
     Engineer: Martin Hannon
        Input: unsigned char ucNotificationType:
                  Notification type being configured.
               TyNotificationCallback tyNotificationCallback
                  Callback function pointer.
       Output: TRUE: Success, FALSE: Failure.
  Description: Configures the notification callback function pointers.
  
               NOTE:- These callbacks are invoked from an interrupt handler, 
               and their execution time therefore should be kept to a minimum.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char PPD42NJ_SetupNotifications(unsigned char ucNotificationType, TyNotificationCallback tyNotificationCallback)
{

   switch (ucNotificationType)
      {
      case NOTIFICATION_1_SECOND_UPDATE:
         tyLocalOneSecondCallback = tyNotificationCallback;
         return TRUE;
      case NOTIFICATION_MAX_HISTORY_UPDATE:
         tyLocalMaxHistoryCallback = tyNotificationCallback;
         return TRUE;
      default:
         return FALSE;
      }
}

/****************************************************************************
     Function: PPD42NJ_GetAirQualityMeasurements
     Engineer: Martin Hannon
        Input: TyAirQualityMeasurements *ptyAirQualityMeasurements: 
                  Storage for the air quality measurements.
       Output: TRUE: Success, FALSE: Failure.
  Description: Returns the air quality measurements.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
unsigned char PPD42NJ_GetAirQualityMeasurements(TyAirQualityMeasurements *ptyAirQualityMeasurements)
{
   unsigned long ulSecondCounter = 0;

   do
      {
         // Take a copy of the current second counter...
         ulSecondCounter = ulLocalSecondCounter;

         // Copy over the air quality measurements....
         *ptyAirQualityMeasurements = tyLocalAirQualityMeasurements;
      }
   while (ulSecondCounter != ulLocalSecondCounter); // If interrupt has occurred during the copy, retry.

   return TRUE;
}
