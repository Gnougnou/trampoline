// Sound with arduino.

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FREQ 8192
#define DELAYMS (100000/FREQ)

//bizarre, ya une puissance de 10 qui ne va pas.


void init_sound(void){
  DDRB |= _BV(0); // buzzer on digital 8

}

int main(void){
 
 init_sound();

 while(1){
   PORTB ^= _BV(0); 
   _delay_ms(DELAYMS); 
 }
   
 return 0;
}


