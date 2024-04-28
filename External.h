/*
 * External.h
 *
 * Created: 03.04.2017 21:04:41
 *  Author: Christof
 */



#ifndef EXTERNAL_H_
#define EXTERNAL_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "timer2.h"
#include "Communication.h"
#include "myTimers.h"
#include "myconstants.h"
#include "secrets.h"
#include "Rollladen.h"

#if NUM_ROLLLADEN > 0
  #pragma message "Rollläden sind vorgesehen"
  extern float actPosition[NUM_ROLLLADEN];
  extern float setPosition[NUM_ROLLLADEN];
  extern float oldPosition[NUM_ROLLLADEN];
  extern int8_t moveStatus[NUM_ROLLLADEN];
  extern ROLL_STATUS actualStatus[NUM_ROLLLADEN];
  extern ROLL_STATUS oldStatus[NUM_ROLLLADEN];
  extern const  ROLL_STATUS backupStatus[NUM_ROLLLADEN] PROGMEM;
  extern ROLL_STATUS saveStatus[NUM_ROLLLADEN] EEMEM;
  extern uint8_t checksumEE[NUM_ROLLLADEN] EEMEM;
  extern uint8_t checksum[NUM_ROLLLADEN];
#endif


extern uint16_t actReportBetweenBlocks;
extern uint16_t actReportBetweenSensors;
extern uint16_t actWaitAfterLastSensor;

extern volatile uint8_t statusReport;
extern volatile uint8_t indexReport;
extern volatile bool sendStatusReport;

extern volatile char strStatusNachtabsenkung[5];
extern volatile bool statusNachtabsenkung;

class Communication;   // Forward declaration
class ComReceiver;
extern Serial debug;
extern Communication cnet;
extern ComReceiver cnetRec;
extern CRC_Calc crcGlobal;

#endif /* EXTERNAL_H_ */
