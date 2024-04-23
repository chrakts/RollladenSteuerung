/*
* RollladenSteuerung.cpp
*/

#include "RollladenSteuerung.h"

void setup()
{
  init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);
	PORTA_DIRSET = PIN2_bm | PIN3_bm | PIN4_bm;
	PORTA_OUTSET = 0xff;
	PORTB_DIRSET = 0xff;
	PORTC_DIRSET = PIN1_bm;
	PORTD_DIRSET = 0xff;
	PORTE_DIRSET = PIN0_bm | PIN1_bm | PIN3_bm;

  uint8_t i;
	for(i=0;i<20;i++)
	{
		LEDGRUEN_TOGGLE;
		_delay_ms(50);
	}

  PMIC_CTRL = PMIC_LOLVLEX_bm | PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm;
	sei();
	cnet.open(Serial::BAUD_57600,F_CPU);
}

int main(void)
{
	setup();
	cnet.broadcastUInt8((uint8_t) RST.STATUS,'S','0','R');
	init_mytimer();

	while (1)
	{
		cnetRec.comStateMachine();
		cnetRec.doJob();

		if( sendStatusReport )
    {
        sendStatusReport = false;
        MyTimers[TIMER_REPORT].value = actReportBetweenSensors;
        MyTimers[TIMER_REPORT].state = TM_START;
        switch(statusReport)
        {
          case FIRSTREPORT:
          break;

          case LASTREPORT:
              MyTimers[TIMER_REPORT].value = actReportBetweenBlocks;
              MyTimers[TIMER_REPORT].state = TM_START;
          break;
      }
      LEDGRUEN_OFF;
    }
	}
}


