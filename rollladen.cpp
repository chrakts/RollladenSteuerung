#include "Rollladen.h"
#include "External.h"


void getStatusFromPGM(uint8_t i)
{
  if(i<NUM_ROLLLADEN)
  {
    for( uint8_t j=0;j<3;j++)
    {
      actualStatus[i].fixPos[j] = pgm_read_byte(&(backupStatus[i].fixPos[j]));
    }
    actualStatus[i].upTime = pgm_read_word(&(backupStatus[i].upTime));
    actualStatus[i].downTime = pgm_read_word(&(backupStatus[i].downTime));
  }
}

void getStatusFromEE()
{
  for( uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    ROLL_STATUS tempStatus;
    for( uint8_t j=0;j<3;j++)
    {
      tempStatus.fixPos[j] = eeprom_read_byte(&(saveStatus[i].fixPos[j]));
    }
    tempStatus.upTime = eeprom_read_word(&(saveStatus[i].upTime));
    tempStatus.downTime = eeprom_read_word(&(saveStatus[i].downTime));
    if( calculateChecksum(tempStatus) != eeprom_read_byte(&(checksumEE[i])) )
    {
      getStatusFromPGM(i);
    }
    else
    {
      for( uint8_t j=0;j<3;j++)
      {
        actualStatus[i].fixPos[j] = tempStatus.fixPos[j];
      }
      actualStatus[i].upTime = tempStatus.upTime;
      actualStatus[i].downTime = tempStatus.downTime;
    }
  }
}

uint8_t calculateChecksum(const ROLL_STATUS& data)
{
  uint8_t checksum = 0;
  // Calculate checksum using XOR instead of addition
  const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&data);
  for (size_t i = 0; i < sizeof(ROLL_STATUS); ++i)
    checksum ^= *(ptr + i);
  if (checksum == 0)      // If the checksum is 0, change it to a non-zero value
    checksum = 0xFF;

  return checksum;
}

void writeStatusToEE()
{
  for( uint8_t i=0;i<NUM_ROLLLADEN;i++)
  {
    for( uint8_t j=0;j<3;j++)
    {
      eeprom_update_byte(&(saveStatus[i].fixPos[j]),actualStatus[i].fixPos[j] );
    }
    eeprom_update_word(&(saveStatus[i].upTime),actualStatus[i].upTime );
    eeprom_update_word(&(saveStatus[i].downTime),actualStatus[i].downTime );
    eeprom_update_byte(&checksumEE[i], calculateChecksum(actualStatus[i]));
  }
}

