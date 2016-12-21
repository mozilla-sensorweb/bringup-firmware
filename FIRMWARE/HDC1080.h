/****************************************************************************
       Module: HDC1080.h
     Engineer: Martin Hannon
  Description: Contains function prototypes for accessing the HDC1080 
               temperature / humidity sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/

unsigned char HDC1080_Initialise(void);
unsigned char HDC1080_HeaterControl(unsigned char bEnable);
unsigned char HDC1080_ReadTemperature(double *pdTemperature);
unsigned char HDC1080_ReadHumidity(double *pdHumidity);

