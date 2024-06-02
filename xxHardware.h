#pragma once

#define RELAISX1_PORT PORTA
#define RELAISX1_PIN  PIN6_bm
#define RELAISY1_PORT PORTA
#define RELAISY1_PIN  PIN3_bm

#define RELAISX1SETUP RELAISX1_PORT.DIRSET=RELAISX1_PIN
#define RELAISX1_ON   RELAISX1_PORT.OUTCLR=RELAISX1_PIN
#define RELAISX1_OFF  RELAISX1_PORT.OUTSET=RELAISX1_PIN
#define RELAISX1_TOGGLE  RELAISX1_PORT.OUTTGL=RELAISX1_PIN

#define RELAISY1SETUP RELAISY1_PORT.DIRSET=RELAISY1_PIN
#define RELAISY1_ON   RELAISY1_PORT.OUTCLR=RELAISY1_PIN
#define RELAISY1_OFF  RELAISY1_PORT.OUTSET=RELAISY1_PIN
#define RELAISY1_TOGGLE  RELAISY1_PORT.OUTTGL=RELAISY1_PIN

#define ROLLADEN_1_UP RELAISX1_ON; RELAISY1_OFF;
#define ROLLADEN_1_DW RELAISX1_OFF; RELAISY1_ON;
#define ROLLADEN_1_ST RELAISX1_OFF; RELAISY1_OFF;

// -----------------------------------------------------

#define RELAISX2_PORT PORTA
#define RELAISX2_PIN  PIN6_bm
#define RELAISY2_PORT PORTA
#define RELAISY2_PIN  PIN3_bm

#define RELAISX2SETUP RELAISX2_PORT.DIRSET=RELAISX2_PIN
#define RELAISX2_ON   RELAISX2_PORT.OUTCLR=RELAISX2_PIN
#define RELAISX2_OFF  RELAISX2_PORT.OUTSET=RELAISX2_PIN
#define RELAISX2_TOGGLE  RELAISX2_PORT.OUTTGL=RELAISX2_PIN

#define RELAISY2SETUP RELAISY2_PORT.DIRSET=RELAISY2_PIN
#define RELAISY2_ON   RELAISY2_PORT.OUTCLR=RELAISY2_PIN
#define RELAISY2_OFF  RELAISY2_PORT.OUTSET=RELAISY2_PIN
#define RELAISY2_TOGGLE  RELAISY2_PORT.OUTTGL=RELAISY2_PIN

#define ROLLADEN_2_UP RELAISX2_ON; RELAISY2_OFF;
#define ROLLADEN_2_DW RELAISX2_OFF; RELAISY2_ON;
#define ROLLADEN_2_ST RELAISX2_OFF; RELAISY2_OFF;

// -----------------------------------------------------

#define RELAISX3_PORT PORTA
#define RELAISX3_PIN  PIN6_bm
#define RELAISY3_PORT PORTA
#define RELAISY3_PIN  PIN3_bm

#define RELAISX3SETUP RELAISX3_PORT.DIRSET=RELAISX3_PIN
#define RELAISX3_ON   RELAISX3_PORT.OUTCLR=RELAISX3_PIN
#define RELAISX3_OFF  RELAISX3_PORT.OUTSET=RELAISX3_PIN
#define RELAISX3_TOGGLE  RELAISX3_PORT.OUTTGL=RELAISX3_PIN

#define RELAISY3SETUP RELAISY3_PORT.DIRSET=RELAISY3_PIN
#define RELAISY3_ON   RELAISY3_PORT.OUTCLR=RELAISY3_PIN
#define RELAISY3_OFF  RELAISY3_PORT.OUTSET=RELAISY3_PIN
#define RELAISY3_TOGGLE  RELAISY3_PORT.OUTTGL=RELAISY3_PIN

#define ROLLADEN_3_UP RELAISX3_ON; RELAISY3_OFF;
#define ROLLADEN_3_DW RELAISX3_OFF; RELAISY3_ON;
#define ROLLADEN_3_ST RELAISX3_OFF; RELAISY3_OFF;

#if NUM_ROLLLADEN > 0
  #define ROLL_PORT PORTA
  #ifdef ROLL1_INV
    #define ROLL1_UP_PIN   PIN3_bm
    #define ROLL1_DOWN_PIN PIN6_bm
    #pragma message "Rolladen 1 läuft invers"
  #else
    #define ROLL1_UP_PIN   PIN6
    #define ROLL1_DOWN_PIN PIN3_bm
  #endif // ROLL1_INV
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN > 1
  #ifdef ROLL2_INV
    #define ROLL2_UP_PIN PIN2_bm
    #define ROLL2_DOWN_PIN PIN4_bm
    #pragma message "Rolladen 2 läuft invers"
  #else
    #define ROLL2_UP_PIN PIN4
    #define ROLL2_DOWN_PIN PIN2_bm
  #endif // ROLL2_INV
#endif // NUM_ROLLLADEN
#if NUM_ROLLLADEN > 2
  #ifdef ROLL3_INV
    #define ROLL3_UP_PIN PIN1_bm
    #define ROLL3_DOWN_PIN PIN5_bm
    #pragma message "Rolladen 3 läuft invers"
  #else
    #define ROLL3_UP_PIN PIN5
    #define ROLL3_DOWN_PIN PIN1_bm
  #endif // ROLL3_INV
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN > 0
  #define ROLL1SETUP  ROLL_PORT.DIRSET=ROLL1_DOWN_PIN | ROLL1_UP_PIN
  #define ROLL1_DOWN  ROLL_PORT.OUTCLR=ROLL1_UP_PIN   ; ROLL_PORT.OUTSET=ROLL1_DOWN_PIN
  #define ROLL1_UP    ROLL_PORT.OUTCLR=ROLL1_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL1_UP_PIN
  #define ROLL1_OFF   ROLL_PORT.OUTSET=ROLL1_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL1_UP_PIN
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN > 1
  #define ROLL2SETUP  ROLL_PORT.DIRSET=ROLL2_DOWN_PIN | ROLL2_UP_PIN
  #define ROLL2_DOWN  ROLL_PORT.OUTCLR=ROLL2_UP_PIN   ; ROLL_PORT.OUTSET=ROLL2_DOWN_PIN
  #define ROLL2_UP    ROLL_PORT.OUTCLR=ROLL2_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL2_UP_PIN
  #define ROLL2_OFF   ROLL_PORT.OUTSET=ROLL2_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL2_UP_PIN
#endif // NUM_ROLLLADEN

#if NUM_ROLLLADEN > 2
  #define ROLL3SETUP  ROLL_PORT.DIRSET=ROLL3_DOWN_PIN | ROLL3_UP_PIN
  #define ROLL3_DOWN  ROLL_PORT.OUTCLR=ROLL3_UP_PIN   ; ROLL_PORT.OUTSET=ROLL3_DOWN_PIN
  #define ROLL3_UP    ROLL_PORT.OUTCLR=ROLL3_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL3_UP_PIN
  #define ROLL3_OFF   ROLL_PORT.OUTSET=ROLL3_DOWN_PIN ; ROLL_PORT.OUTSET=ROLL3_UP_PIN
#endif // NUM_ROLLLADEN




