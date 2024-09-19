#include "myTimers.h"
#include "ledHardware.h"

// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

//2: 16.2ms
//10: 81ms
//20: 162ms
//100: 810ms
// 12.346 tics/100ms

volatile TIMER2 MyTimers[MYTIMER_NUM]=
{
  {TM_STOP,RESTART_NO,100,0,rollTimer,0},
#if NUM_ROLLLADEN>1
  {TM_STOP,RESTART_NO,100,0,rollTimer,1},
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN>2
  {TM_STOP,RESTART_NO,100,0,rollTimer,2},
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN>3
  {TM_STOP,RESTART_NO,100,0,rollTimer,3},
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN>4
  {TM_STOP,RESTART_NO,100,0,rollTimer,4},
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN>5
  {TM_STOP,RESTART_NO,100,0,rollTimer,5},
#endif // NUM_ROLLLADEN
  {TM_START,RESTART_YES,actReportBetweenSensors,0,nextReportStatus,0},
  {TM_START,RESTART_YES,30,0,actPositionTimer,0},
  {TM_STOP,RESTART_NO,5000,0,nowSaveEEProm,0},
  {TM_START,RESTART_YES,10,0,ledBlinken,0}
};

void rollTimer(uint16_t parameter)
{
  //LEDROT_OFF;
  LEDGRUEN_OFF;
  actPosition[parameter] = setPosition[parameter];
  moveStatus[parameter]  = 0;
}

void actPositionTimer(uint16_t parameter)
{
	for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    switch(moveStatus[i])
    {
      case 1:
        actPosition[i] = startPosition[i] + (100/TicsPer10ms*(float)(MyTimers[i].value - MyTimers[i].actual)/(float)actualStatus[i].upTime)*float(moveStatus[i]);
      break;
      case -1:
        actPosition[i] = startPosition[i] + (100/TicsPer10ms*(float)(MyTimers[i].value - MyTimers[i].actual)/(float)actualStatus[i].downTime)*float(moveStatus[i]);
      break;
    }
  }
}

void nextReportStatus(uint16_t parameter)
{
	sendStatusReport = true;
  if(indexReport >= NUM_ROLLLADEN)
  {
    indexReport = 0;
    statusReport++;
  }

	if( statusReport > LASTREPORT )
  {
    statusReport = FIRSTREPORT;
    indexReport = 0;
  }
}

void nowSaveEEProm(uint16_t parameter)
{
  eepromWriteReady = true;
}

void ledBlinken(uint16_t parameter)
{
  LEDROT_TOGGLE;
}



