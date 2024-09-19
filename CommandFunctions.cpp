/*
 * CommandFunctions.cpp
 */

#include "CommandFunctions.h"
#include "External.h"
#include "secrets.h"

INFORMATION information[NUM_INFORMATION]=
{
  {"DT",'t','1','N',STRING,3,(void*)strStatusNachtabsenkung,gotStatusNachtabsenkung},
};

COMMAND cnetCommands[NUM_COMMANDS] =
	{
    cmultiStandardCommands,
		{'a','S',CUSTOMER,UINT_8,1,jobSetFixPositionA},
		{'b','S',CUSTOMER,UINT_8,1,jobSetFixPositionB},
		{'c','S',CUSTOMER,UINT_8,1,jobSetFixPositionC},
		{'U','S',CUSTOMER,UINT_16,1,jobSetUpTime},
		{'D','S',CUSTOMER,UINT_16,1,jobSetDownTime},
		{'X','S',CUSTOMER,FLOAT,1,jobSetPosition},
		{'F','a',CUSTOMER,NOPARAMETER,0,jobSetToFixPos0},
		{'F','b',CUSTOMER,NOPARAMETER,0,jobSetToFixPos1},
		{'F','c',CUSTOMER,NOPARAMETER,0,jobSetToFixPos2},
		{'F','T',CUSTOMER,NOPARAMETER,0,jobSetToFixPosTop},
		{'F','B',CUSTOMER,NOPARAMETER,0,jobSetToFixPosBottom},
		{'R','S',CUSTOMER,NOPARAMETER,0,jobStop},

	};

void jobStop(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    stopRollladen(adr);
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}


void jobSetToFixPos0(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = actualStatus[adr].fixPos[0];
      comRec->Getoutput()->broadcastFloat(setPosition[adr],'X',address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetToFixPos1(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = actualStatus[adr].fixPos[1];
      comRec->Getoutput()->broadcastFloat(setPosition[adr],'X',address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetToFixPos2(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = actualStatus[adr].fixPos[2];
      comRec->Getoutput()->broadcastFloat(setPosition[adr],'X',address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetToFixPosTop(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = 100;
      comRec->Getoutput()->broadcastFloat(setPosition[adr],'X',address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetToFixPosBottom(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = 0;
      comRec->Getoutput()->broadcastFloat(setPosition[adr],'X',address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetPosition(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    if(moveStatus[adr]==0)
    {
      setPosition[adr] = ( (double*) pMem )[0];
      comRec->Getoutput()->broadcastFloat(setPosition[adr],function,address,'a');
    }
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetFixPositionA(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    actualStatus[adr].fixPos[0] = ( (uint8_t*) pMem )[0];
    comRec->Getoutput()->broadcastUInt8(actualStatus[adr].fixPos[0],function,address,'a');
    //writeEEData();
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetFixPositionB(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    actualStatus[adr].fixPos[1] = ( (uint8_t*) pMem )[0];
    comRec->Getoutput()->broadcastUInt8(actualStatus[adr].fixPos[1],function,address,'a');
    //writeEEData();
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetFixPositionC(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    actualStatus[adr].fixPos[2] = ( (uint8_t*) pMem )[0];
    comRec->Getoutput()->broadcastUInt8(actualStatus[adr].fixPos[2],function,address,'a');
    //writeEEData();
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetUpTime(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    actualStatus[adr].upTime = ( (uint16_t*) pMem )[0];
    comRec->Getoutput()->broadcastUInt16(actualStatus[adr].upTime,function,address,'a');
    //writeEEData();
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}

void jobSetDownTime(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  uint8_t adr = (uint8_t)address-48;
  if(adr<NUM_ROLLLADEN)
  {
    actualStatus[adr].downTime = ( (uint16_t*) pMem )[0];
    comRec->Getoutput()->broadcastUInt16(actualStatus[adr].downTime,function,address,'a');
    //writeEEData();
  }
  else
    comRec->sendPureAnswer(function,address,job,false);
}


void gotStatusNachtabsenkung()
{
	if(strStatusNachtabsenkung[1]=='n')
	  statusNachtabsenkung = true;
  else
	  statusNachtabsenkung = false;
}

