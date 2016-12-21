/****************************************************************************
       Module: pinmux.c
     Engineer: Martin Hannon
  Description: Contains PinMuxConfig routine for configuring the processor.
Date           Initials    Description
07-DEC-2016    MH          Initial
****************************************************************************/
#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"
#include "prcm.h"

void PinMuxConfig(void)
{
    //
    // Set unused pins to PIN_MODE_0 with the exception of JTAG pins 16,17,19,20
    //
    PinModeSet(PIN_05, PIN_MODE_0);
    PinModeSet(PIN_06, PIN_MODE_0);
    PinModeSet(PIN_08, PIN_MODE_0);
    PinModeSet(PIN_15, PIN_MODE_0);
    PinModeSet(PIN_18, PIN_MODE_0);
    PinModeSet(PIN_21, PIN_MODE_0);
    PinModeSet(PIN_53, PIN_MODE_0);
    PinModeSet(PIN_50, PIN_MODE_0);
    
    //
    // Enable Peripheral Clocks 
    //
    PRCMPeripheralClkEnable(PRCM_TIMERA0, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_TIMERA1, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_UARTA0, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_UARTA1, PRCM_RUN_MODE_CLK);
    PRCMPeripheralClkEnable(PRCM_I2CA0, PRCM_RUN_MODE_CLK);

    //
    // Configure PIN_03 for GPIO input
    //
    PinTypeGPIO(PIN_03, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, 0x10, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_04 for GPIO input
    //
    PinTypeGPIO(PIN_04, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, 0x20, GPIO_DIR_MODE_IN);


    //
    // Configure PIN_60 for GPIO Input
    //
    PinTypeGPIO(PIN_60, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA0_BASE, 0x20, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_61 for GPIO Input
    //
    PinTypeGPIO(PIN_61, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA0_BASE, 0x40, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_62 for GPIO Input
    //
    PinTypeGPIO(PIN_62, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA0_BASE, 0x80, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_63 for GPIO Input
    //
    PinTypeGPIO(PIN_63, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, 0x1, GPIO_DIR_MODE_IN);

    //
    // Configure PIN_64 for GPIO Output
    //
    PinTypeGPIO(PIN_64, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA1_BASE, 0x2, GPIO_DIR_MODE_OUT);

    //
    // Configure PIN_07 for GPIO Output
    //
    PinTypeGPIO(PIN_07, PIN_MODE_0, false);
    GPIODirModeSet(GPIOA2_BASE, 0x1, GPIO_DIR_MODE_OUT);
    GPIOPinWrite(GPIOA2_BASE, 0x1, 1);

    //
    // Configure PIN_55 for UART0 UART0_TX
    //
    PinTypeUART(PIN_55, PIN_MODE_3);

    //
    // Configure PIN_57 for UART0 UART0_RX
    //
    PinTypeUART(PIN_57, PIN_MODE_3);

    //
    // Configure PIN_58 for UART1 UART1_TX
    //
    PinTypeUART(PIN_58, PIN_MODE_6);

    //
    // Configure PIN_59 for UART1 UART1_RX
    //
    PinTypeUART(PIN_59, PIN_MODE_6);

    //
    // Configure PIN_01 for I2C0 I2C_SCL
    //
    PinTypeI2C(PIN_01, PIN_MODE_1);

    //
    // Configure PIN_02 for I2C0 I2C_SDA
    //
    PinTypeI2C(PIN_02, PIN_MODE_1);
}

