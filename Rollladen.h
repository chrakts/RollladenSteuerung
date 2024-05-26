#ifndef ROLLLADEN_H_INCLUDED
#define ROLLLADEN_H_INCLUDED

#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


struct rolladenStatus
{
  uint8_t fixPos[3];      // Programmierbare Positionen in % als Ganzzahlwert
  uint16_t upTime;        // Zeit in 1/100s zum Hochfahren
  uint16_t downTime;      // Zeit in 1/100s zum runterfahren
};

typedef struct rolladenStatus ROLL_STATUS;

void getStatusFromPGM(uint8_t i);
void getStatusFromEE();
uint8_t calculateChecksum(const ROLL_STATUS& data);
void writeStatusToEE();


#endif // ROLLLADEN_H_INCLUDED
