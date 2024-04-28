/*
 * Globals.cpp
 */

#define EXTERNALS_H_

#include "RollladenSteuerung.h"
#include "CmultiAddresses.h"
#include "Rollladen.h"

const char *Node = NODE_STRING;

#if NUM_ROLLLADEN > 0
  #pragma message "Rollläden sind vorgesehen"
  float actPosition[NUM_ROLLLADEN];      // aktuelle Position in % als float-Wert
  float setPosition[NUM_ROLLLADEN];      // Zielposition in % als float-Wert
  float oldPosition[NUM_ROLLLADEN];
  int8_t moveStatus[NUM_ROLLLADEN];
  ROLL_STATUS actualStatus[NUM_ROLLLADEN];
  ROLL_STATUS oldStatus[NUM_ROLLLADEN];
  const  ROLL_STATUS backupStatus[NUM_ROLLLADEN] PROGMEM = { {{30,50,75},230,190}, {{30,50,75},230,190} };
  ROLL_STATUS saveStatus[NUM_ROLLLADEN] EEMEM= { {{30,50,75},230,190}, {{30,50,75},230,190}  };
  uint8_t checksumEE[NUM_ROLLLADEN] EEMEM;
  uint8_t checksum[NUM_ROLLLADEN];
#endif

volatile char strStatusNachtabsenkung[5];
volatile bool statusNachtabsenkung;

uint16_t actReportBetweenBlocks  = REPORT_BETWEEN_BLOCKS;
uint16_t actReportBetweenSensors = REPORT_BETWEEN_SENSORS;
//uint16_t actWaitAfterLastSensor  = WAIT_AFTER_LAST_SENSOR;

volatile uint8_t statusReport = FIRSTREPORT;
volatile uint8_t indexReport = 0;     // iteriert über die Rollläden
volatile bool    sendStatusReport = true;

Communication cnet(0,Node,5,true);
ComReceiver cnetRec(&cnet,Node,cnetCommands,NUM_COMMANDS,information,NUM_INFORMATION,NULL,NULL);

