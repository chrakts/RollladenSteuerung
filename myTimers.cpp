#include "myTimers.h"
#include "ledHardware.h"

// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,actReportBetweenSensors,0,nextReportStatus},
                                        {TM_START,RESTART_YES,5000,0,led1Blinken}
};

void led1Blinken(uint8_t test)
{
	LEDROT_TOGGLE;
}

void nextReportStatus(uint8_t test)
{
  LEDGRUEN_ON;
	sendStatusReport = true;
	statusReport+=1;
	if( statusReport > LASTREPORT )
        statusReport = FIRSTREPORT;
}



