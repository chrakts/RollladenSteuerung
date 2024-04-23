/*
 * MyTimer.h
 *
 * Created: 11.02.2016 20:20:03
 *  Author: Christof
 */


#ifndef MYTIMERS_H_
#define MYTIMERS_H_

#include "timer.h"
#include "External.h"
#include "myconstants.h"

#define MYTIMER_NUM	2


enum{TIMER_SENSOREN,TIMER_REPORT,TIMER_SAVE_DELAY};

void nextReportStatus(uint8_t test);
void led1Blinken(uint8_t test);

extern volatile TIMER MyTimers[MYTIMER_NUM];

#endif /* MYTIMERS_H_ */
