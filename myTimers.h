/*
 * MyTimer.h
 *
 * Created: 11.02.2016 20:20:03
 *  Author: Christof
 */


#ifndef MYTIMERS_H_
#define MYTIMERS_H_

#include "timer2.h"
#include "External.h"
#include "myconstants.h"

#define MYTIMER_NUM	3+NUM_ROLLLADEN


enum{TIMER_REPORT=NUM_ROLLLADEN,TIMER_ACTUAL_POSITION,TIMER_SAVE_DELAY};


void rollTimer(uint16_t parameter);
void nextReportStatus(uint16_t parameter);
void actPositionTimer(uint16_t parameter);
void nowSaveEEProm(uint16_t parameter);

extern volatile TIMER2 MyTimers[MYTIMER_NUM];

#endif /* MYTIMERS_H_ */
