/*
 * Globals.cpp
 */

#define EXTERNALS_H_

#include "RollladenSteuerung.h"
#include "CmultiAddresses.h"

const char *Node = NODE_STRING;

volatile char strStatusNachtabsenkung[5];
volatile bool statusNachtabsenkung;

uint16_t actReportBetweenBlocks  = REPORT_BETWEEN_BLOCKS;
uint16_t actReportBetweenSensors = REPORT_BETWEEN_SENSORS;
uint16_t actWaitAfterLastSensor  = WAIT_AFTER_LAST_SENSOR;

volatile uint8_t statusReport = FIRSTREPORT;
volatile bool    sendStatusReport = true;

Communication cnet(0,Node,5,true);
ComReceiver cnetRec(&cnet,Node,cnetCommands,NUM_COMMANDS,information,NUM_INFORMATION,NULL,NULL);

