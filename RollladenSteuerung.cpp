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
#pragma message "Rollladen 1 vorhanden"
ROLL1SETUP;
ROLL1_OFF;
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN > 1
#pragma message "Rollladen 2 vorhanden"
ROLL2SETUP;
ROLL2_OFF;
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN > 2
#pragma message "Rollladen 3 vorhanden"
ROLL3SETUP;
ROLL3_OFF;
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
    setPosition[i] = -100;
    oldPosition[i] = -100.0;
  }
  readEEData();

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
              setPosition[i] = 100;
              actPosition[i] = 0;
           }
            else                   // Zielposition ist in der unteren Hälfte -> ganz nach unten fahren
            {
              setPosition[i] = 0;
              actPosition[i] = 100;
            }
          }

          float diff = abs(setPosition[i]-actPosition[i])/100.0;
          if(diff > 0.99)
            diff = 1.1;
          startPosition[i] = actPosition[i];            // Startposition merken
          if(setPosition[i]>actPosition[i])
          {
            //up
            MyTimers[i].value = (uint16_t)(diff*(float)actualStatus[i].upTime);
            moveStatus[i] = 1;

          }
          else
          {
            //down
            MyTimers[i].value = (uint16_t)(diff*(float)actualStatus[i].downTime);
            moveStatus[i] = -1;
          }
          MyTimers[i].state = TM_START;
        }
      }
    }
#if NUM_ROLLLADEN>0
    switch(moveStatus[0])
    {
      case -1:
        ROLL1_DOWN;
        LEDGRUEN_ON;
        LEDROT_OFF;

      break;
      case 1:
        ROLL1_UP;
        LEDGRUEN_OFF;
        LEDROT_ON;
      break;
      default:
        ROLL1_OFF;
        LEDGRUEN_OFF;
        LEDROT_OFF;
    }
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN>1
    switch(moveStatus[1])
    {
      case -1:
        ROLL2_DOWN;
      break;
      case 1:
        ROLL2_UP;
      break;
      default:
        ROLL2_OFF;
    }
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN>2
    switch(moveStatus[2])
    {
      case -1:
        ROLL3_DOWN;
      break;
      case 1:
        ROLL3_UP;
      break;
      default:
        ROLL3_OFF;
    }
#endif // NUM_ROLLLADEN

    for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
    {
      if(actPosition[i] != oldPosition[i])
      {
        cnet.broadcastFloat(actPosition[i],'P','0'+i,'a');
        oldPosition[i] = actPosition[i];
      }
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
    }
    compareStatus();
    if(eepromWriteReady)
      writeEEData();
	}
}

void stopRollladen(uint8_t rollo)
{
  if(moveStatus[rollo]!=0)
  {
    MyTimers[rollo].state = TM_STOP;
    if(actPosition[rollo]>=0.0)           // nur wenn die Augangsposition bekannt war, wird die neue berechnet
    {
      actPosition[rollo] = startPosition[rollo] + (100.0*(float)(MyTimers[rollo].value - MyTimers[rollo].actual)/(float)actualStatus[rollo].upTime) * moveStatus[rollo];
      if(actPosition[rollo] > 100.0)
        actPosition[rollo] = 100.0;
      if(actPosition[rollo] < 0.0)
        actPosition[rollo] = 0.0;
      setPosition[rollo] = actPosition[rollo];
      moveStatus[rollo] = 0;
    }
    cnet.broadcastFloat(actPosition[rollo],'P','0'+rollo,'a');
    cnet.broadcastFloat(actPosition[rollo],'X','0'+rollo,'a');
  }
}

void readEEData()
{
  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    actualStatus[i].downTime = eeprom_read_word(&(saveStatus[i].downTime));
    actualStatus[i].upTime = eeprom_read_word(&(saveStatus[i].upTime));
    actualStatus[i].fixPos[0] = eeprom_read_byte(&(saveStatus[i].fixPos[0]));
    actualStatus[i].fixPos[1] = eeprom_read_byte(&(saveStatus[i].fixPos[1]));
    actualStatus[i].fixPos[2] = eeprom_read_byte(&(saveStatus[i].fixPos[2]));
  }
  setOldStatus();
}

void writeEEData()
{
  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    eeprom_update_word(&saveStatus[i].downTime,actualStatus[i].downTime);
    eeprom_update_word(&saveStatus[i].upTime,actualStatus[i].upTime);
    eeprom_update_byte(&saveStatus[i].fixPos[0],actualStatus[i].fixPos[0]);
    eeprom_update_byte(&saveStatus[i].fixPos[1],actualStatus[i].fixPos[1]);
    eeprom_update_byte(&saveStatus[i].fixPos[2],actualStatus[i].fixPos[2]);
  }
  eepromWriteReady = false;
  LEDROT_OFF;
}

void compareStatus()
{
  bool result = true;
  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    result = result && (actualStatus[i].upTime == oldStatus[i].upTime);
    result = result && (actualStatus[i].downTime == oldStatus[i].downTime);
    result = result && (actualStatus[i].fixPos[0] == oldStatus[i].fixPos[0]);
    result = result && (actualStatus[i].fixPos[1] == oldStatus[i].fixPos[1]);
    result = result && (actualStatus[i].fixPos[2] == oldStatus[i].fixPos[2]);
  }
  if(result == false)
  {
    cnet.broadcastUInt16(55555,'X','Y','Z');
    LEDROT_ON;
    MyTimers[TIMER_SAVE_DELAY].state = TM_START; // Speicherverzögerung läuft los
    setOldStatus();
  }
}

void setOldStatus()
{
  for(uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    oldStatus[i].upTime = actualStatus[i].upTime;
    oldStatus[i].downTime = actualStatus[i].downTime;
    oldStatus[i].fixPos[0] = actualStatus[i].fixPos[0];
    oldStatus[i].fixPos[1] = actualStatus[i].fixPos[1];
    oldStatus[i].fixPos[2] = actualStatus[i].fixPos[2];
  }
}
