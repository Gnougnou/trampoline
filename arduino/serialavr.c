// cf http://www.appelsiini.net/2011/simple-usart-with-avr-libc

//#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


#define BAUDRATE	103 // UBRR value for 9600

void init_serial(void)
{
  /* ACHTUNG : we suppose UBRR value < 0xff */
  /* Not true in all case */
  uint8_t baudrate = BAUDRATE;
  /* Set baud rate */
  UBRR0H = 0;
  UBRR0L = baudrate;

  /* Enable transmitter */
  UCSR0B = (1<<TXEN0)|(1<<RXEN0);


  /* Set frame format */
  UCSR0C = 0x06;
}


void send_serial(unsigned char c)
{
  UDR0 = c;
  loop_until_bit_is_set(UCSR0A, TXC0);
}

//Blocking serial
char serial_getchar(void) {

  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
  
  return UDR0;
}

//Non blocking serial 
int serial_get_char2(char* one){
  if (bit_is_set(UCSR0A, RXC0))
    {
      *one = UDR0;
      return 1;
    }
  else return 0;
}

void task_get_serial_and_blink(void){
  char c = serial_getchar();
  send_serial(c);
  if (c=='b')
    PORTC ^= _BV(1); // blink yellow led
}

int main(void){

 DDRC |= _BV(1); // yellow led analog 1
 init_serial();

 while(1){
    task_get_serial_and_blink();
   _delay_ms(100);
 }
   
 return 0;
}


