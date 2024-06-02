#pragma once

#include "RollladenSteuerung.h"

extern COMMAND cnetCommands[];
extern INFORMATION information[];

#define NUM_COMMANDS 12+CMULTI_STANDARD_NUM
#define NUM_INFORMATION 1

void gotStatusNachtabsenkung();

void jobStop(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetToFixPos0(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetToFixPos1(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetToFixPos2(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetToFixPosTop(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetToFixPosBottom(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetPosition(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetFixPositionA(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetFixPositionB(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetFixPositionC(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetUpTime(ComReceiver *comRec, char function,char address,char job, void * pMem);
void jobSetDownTime(ComReceiver *comRec, char function,char address,char job, void * pMem);



