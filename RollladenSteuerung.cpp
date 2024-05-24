/*
* RollladenSteuerung.cpp
*/

#include "RollladenSteuerung.h"

void setup()
{
  init_clock(SYSCLK,PLL,true,CLOCK_CALIBRATION);
	PORTA_DIRSET = 0xff; // Relais
	PORTA_OUTSET = 0xff;
	PORTB_DIRCLR = 0xff; // Tastatur-LEDs
	PORTC_DIRCLR = 0xff; // Tastatur
	PORTD_DIRSET = 0xff; // LED
	PORTE_DIRSET = PIN0_bm | PIN1_bm | PIN3_bm;

  LEDGRUENSETUP;
  LEDROTSETUP;
#ifdef TASTATUR
#pragma message "Tastatur vorhanden"
  LEDGRUEN_TASTSETUP;
  LEDROT_TASTSETUP;
#endif // TASTATUR

#if NUM_ROLLLADEN > 0
#pragma message "Relais vorhanden"
  RELAISX1SETUP;
  RELAISY1SETUP;
  RELAISX2SETUP;
  RELAISY2SETUP;
  RELAISX3SETUP;
  RELAISY3SETUP;
  ROLLADEN_1_ST;
  ROLLADEN_2_ST;
  ROLLADEN_3_ST;
#endif // NUM_ROLLLADEN


  uint8_t i;
  LEDROT_OFF;
	for(i=0;i<20;i++)
	{
		LEDGRUEN_TOGGLE;
		_delay_ms(50);
	}
	LEDGRUEN_OFF;
	for(i=0;i<20;i++)
	{
		LEDROT_TOGGLE;
		_delay_ms(50);
	}

  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    moveStatus[i] = 0;          // Stillstand
    actPosition[i] = -100.0;   // unbekannte Position
    setPosition[i] = -100.0;
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
  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
    moveStatus[i] = 0;

	while (1)
	{
		cnetRec.comStateMachine();
		cnetRec.doJob();

		for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
    {
      if(actPosition[i] != setPosition[i])
      {
        if(moveStatus[i] == 0)   // falls bereits in Bewegung - nichts veranlassen
        {
          if(actPosition[i] < 0.0)  // unbekannte Ausgangsposition
          {
            if(setPosition[i] > 50.0)    // Zielposition ist in der oberen Hälfte -> ganz nach oben fahren
            {
              MyTimers[i].value = actualStatus[i].upTime*1.2;
              moveStatus[i] = 1;
            }
            else                   // Zielposition ist in der unteren Hälfte -> ganz nach unten fahren
            {
              MyTimers[i].value = actualStatus[i].downTime*1.2;
              moveStatus[i] = -1;
            }
          }
          else                   // bekannte Ausgangsposition
          {
            float diff = abs(setPosition[i]-actPosition[i]);
            if(setPosition>actPosition)
            {
              //up
              MyTimers[i].value = diff*actualStatus[i].upTime;
              moveStatus[i] = 1;

            }
            else
            {
              //down
              MyTimers[i].value = diff*actualStatus[i].downTime;
              moveStatus[i] = -1;
            }

          }
          MyTimers[i].state = TM_START;
        }
      }
    }
    switch(moveStatus[0])
    {
      case 1:
        LEDGRUEN_ON;
        LEDROT_OFF;
      break;
      case -1:
        LEDGRUEN_OFF;
        LEDROT_ON;
      break;
      default:
        LEDGRUEN_OFF;
        LEDROT_OFF;

    }
		if( sendStatusReport )
    {
        sendStatusReport = false;
        MyTimers[TIMER_REPORT].value = actReportBetweenSensors;
        MyTimers[TIMER_REPORT].state = TM_START;
        switch(statusReport)
        {
          case FIRSTREPORT:
            indexReport = NUM_ROLLLADEN;
          break;
          case ACT_POSITION:
            cnet.broadcastFloat(actPosition[indexReport],'P','0'+indexReport,'a');
            indexReport++;
          break;
          case SET_POSITION:
            cnet.broadcastFloat(setPosition[indexReport],'X','0'+indexReport,'a');
            indexReport++;
          break;
          case FIXPOS_A:
            cnet.broadcastUInt8(actualStatus[indexReport].fixPos[0],'a','0'+indexReport,'a');
            indexReport++;
          break;
          case FIXPOS_B:
            cnet.broadcastUInt8(actualStatus[indexReport].fixPos[1],'b','0'+indexReport,'a');
            indexReport++;
          break;
          case FIXPOS_C:
            cnet.broadcastUInt8(actualStatus[indexReport].fixPos[2],'c','0'+indexReport,'a');
            indexReport++;
          break;
          case UPTIME:
            cnet.broadcastUInt16(actualStatus[indexReport].upTime,'U','0'+indexReport,'a');
            indexReport++;
          break;
          case DOWNTIME:
            cnet.broadcastUInt16(actualStatus[indexReport].downTime,'D','0'+indexReport,'a');
            indexReport++;
          break;
          case LASTREPORT:
              indexReport = NUM_ROLLLADEN;
              MyTimers[TIMER_REPORT].value = actReportBetweenBlocks;
              MyTimers[TIMER_REPORT].state = TM_RESET;
              MyTimers[TIMER_REPORT].state = TM_START;
          break;
      }
      //LEDGRUEN_OFF;
    }
	}
}

void stopRollladen(uint8_t rollo)
{
  if(moveStatus[rollo]!=0)
  {
    MyTimers[rollo].state = TM_STOP;
    if(actPosition[rollo]>=0.0)           // nur wenn die Augangsposition bekannt war, wird die neue berechnet
    {
      if(moveStatus[rollo]==1)
      {
        actPosition[rollo] += (MyTimers[rollo].value - MyTimers[rollo].actual)/actualStatus[rollo].upTime;
        if(actPosition[rollo] > 100.0)
          actPosition[rollo] = 100.0;
      }
      else
      {
        actPosition[rollo] -= (MyTimers[rollo].value - MyTimers[rollo].actual)/actualStatus[rollo].downTime;
        if(actPosition[rollo] < 0.0)
          actPosition[rollo] = 0.0;
      }
    }
  }
}
