/****************************************************************************
       Module: PPD42NJ.h
     Engineer: Martin Hannon
  Description: Contains function prototypes for accessing the PPD42NJ
               particle sensor.
Date           Initials    Description
05-DEC-2016    MH          Initial
****************************************************************************/

#define MAXIMUM_HISTORY_IN_SECONDS 30

typedef struct
{

   // pulP1Times contains the accumulated P1 pulse times per second for the 
   // last MAXIMUM_HISTORY_IN_SECONDS seconds. pulP1Times[0] contains the 
   // oldest data. pulP1Times[MAXIMUM_HISTORY_IN_SECONDS -1] contains the 
   // newest data.
   unsigned long pulP1Times[MAXIMUM_HISTORY_IN_SECONDS]; // In 1 us units
   // pulP2Times contains the accumulated P2 pulse times per second for the 
   // last MAXIMUM_HISTORY_IN_SECONDS seconds. pulP2Times[0] contains the 
   // oldest data. pulP2Times[MAXIMUM_HISTORY_IN_SECONDS -1] contains the 
   // newest data.
   unsigned long pulP2Times[MAXIMUM_HISTORY_IN_SECONDS]; // In 1 us units
   // ulSecondsElapsed contains the number of seconds since monitoring started.
   // Wraps every 136 years.
   unsigned long ulSecondsElapsed;
} TyAirQualityMeasurements;


typedef void (*TyNotificationCallback)(void);


// The following defines can be passed as the ucNotificationType parameter to the 
// PPD42NJ_SetupNotifications function. 
#define NOTIFICATION_1_SECOND_UPDATE   0  // Specified callback is invoked every second after new sensor data has been added.
#define NOTIFICATION_MAX_HISTORY_UPDATE 1 // Specified callback is invoked every MAXIMUM_HISTORY_IN_SECONDS after new sensor data has been added.


// Function prototypes from the PPD42NJ module...
unsigned char PPD42NJ_Initialise(void);
unsigned char PPD42NJ_SetupNotifications(unsigned char ucNotificationType, TyNotificationCallback tyNotificationCallback);
unsigned char PPD42NJ_GetAirQualityMeasurements(TyAirQualityMeasurements *ptyAirQualityMeasurements);

