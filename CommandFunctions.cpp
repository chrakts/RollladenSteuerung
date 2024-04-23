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
		{'N','a',CUSTOMER,NOPARAMETER,0,jobGetNachtabsenkung},
	};

void gotStatusNachtabsenkung()
{
	if(strStatusNachtabsenkung[1]=='n')
	  statusNachtabsenkung = true;
  else
	  statusNachtabsenkung = false;
}


void jobGetNachtabsenkung(ComReceiver *comRec, char function,char address,char job, void * pMem)
{
  if(statusNachtabsenkung)
    comRec->sendAnswer("on",'V',address,'a',true);
  else
    comRec->sendAnswer("off",'V',address,'a',true);
}

