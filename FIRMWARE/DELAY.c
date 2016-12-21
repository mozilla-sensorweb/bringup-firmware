/****************************************************************************
       Module: DELAY.c
     Engineer: Martin Hannon
  Description: Contains an accurate delay routine.
Date           Initials    Description
16-DEC-2016    MH          Initial
****************************************************************************/
#include "includes.h"

#define SYSTEM_CLOCK_SPEED 80 // Mhz

static volatile unsigned char bLocalDelayElapsed;

/****************************************************************************
     Function: DELAY_TimerInterrupt
     Engineer: Martin Hannon
        Input: N/A
       Output: N/A
  Description: Interrupt handler for the DELAY timer interrupt
Date           Initials    Description
16-DEC-2016    MH          Initial
****************************************************************************/
static void DELAY_TimerInterrupt(void)
{
   // Clear the timer interrupt...
   Timer_IF_InterruptClear(TIMERA1_BASE);

   // Stop the timer...
   Timer_IF_Stop(TIMERA1_BASE, TIMER_A);
   Timer_IF_DeInit(TIMERA1_BASE, TIMER_A);

   bLocalDelayElapsed = TRUE;
}

/****************************************************************************
     Function: TIMER_Delay
     Engineer: Martin Hannon
        Input: unsigned long ulDelay: Delay time in us.
       Output: N/A
  Description: Delays for the specified time.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/
void TIMER_Delay(unsigned long ulDelay)
{
   bLocalDelayElapsed = FALSE;

   // Timer clocks in 12.5ns ticks (or 1/80 of a microsecond)
   ulDelay *= 80;

   // Initial the TIMERA for the specified timeout...
   Timer_IF_Init(PRCM_TIMERA1, TIMERA1_BASE, TIMER_CFG_PERIODIC_UP, TIMER_A, 0);
   Timer_IF_IntSetup(TIMERA1_BASE, TIMER_A, DELAY_TimerInterrupt);

   MAP_TimerLoadSet(TIMERA1_BASE,TIMER_A, ulDelay);
   MAP_TimerEnable(TIMERA1_BASE,TIMER_A);

   while (bLocalDelayElapsed == FALSE)
      {
      ;;
      }
}
