// see blink.oil head of file for information about the compilation process.
// This is an example for the trampoline distribution, modified by LG May 2016

#include "tpl_os.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void setup()
{
  // initialize analog0 as an output
  DDRC |= _BV(0); // 
}

//The TASK is activated by the alarm "periodicAl":
//* The alarm "periodicAl" is configured in the .oil file to activate task 
//"periodicTask" each 1000 pulses of counter SystemCounter.
//* The SystemCounter is the same as the systick used in Arduino, a tick each 1024us on a 16MHz arduino.
//* This task is periodic, with a period of 1024ms.
TASK(periodicTask)
{
  PORTC ^= _BV(0); 
}

