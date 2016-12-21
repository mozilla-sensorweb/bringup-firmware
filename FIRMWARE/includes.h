/****************************************************************************
       Module: includes.h
     Engineer: Martin Hannon
  Description: Contains the various include files used by the project.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/

#include <stdlib.h>

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "hw_memmap.h"
#include "timer.h"
#include "utils.h"
#include "gpio.h"


//Common interface includes
#include "timer_if.h"
#include "gpio_if.h"
#include "i2c_if.h"
#include "uart_if.h"

#include "common.h"
#include "pinmux.h"

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

#include "DELAY.h"
#include "HDC1080.h"
#include "PPD42NJ.h"
#include "TLC59116.h"
