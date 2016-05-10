/* Faire sonner le HP du PC */
/* doit etre execute avec les droits super-utilisateur */
// Credit Eric Würbel. (LSIS, Marseille)


#include <sys/io.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

/* registres du PIT (programmable interval timer) */
#define TIMER_COMMAND_REGISTER      0x43
#define TIMER_CHANNEL2_DATA_PORT    0x42 
/* port du HP */
#define SPKR_PORT          0x61

#ifndef LOBYTE
#define LOBYTE(w) ((unsigned char) (w))
#endif

#ifndef HIBYTE
#define HIBYTE(w) ((unsigned char) (((unsigned short) (w) >> 8) & 0xFF))
#endif


void hw_sound(unsigned int freq)
{
  unsigned short counter = 1193280 / freq; /* cycle counter */

  /* prepare timer : 10110110 */
  /* bit 0 : 16 bit binary */
  /* bits 1-3 : square wave generator ;o) */
  /* bits 4-5 : access mode : low byte/high byte */
  /* bits 6-7 : select channel : channel 2 */
  outb(0xB6, TIMER_COMMAND_REGISTER);
  outb(LOBYTE(counter), TIMER_CHANNEL2_DATA_PORT); /* send low byte */
  outb(HIBYTE(counter), TIMER_CHANNEL2_DATA_PORT); /* send high byte */
  outb(inb(SPKR_PORT) | 0x03, SPKR_PORT);          /* turn speaker ON */
  return;
}

void hw_nosound(void)
{
  outb(inb(SPKR_PORT) & 0xFC, SPKR_PORT); /* turn speaker OFF */
  return;
}

void zong(unsigned int freq, unsigned int time)
{
  hw_sound(freq);
  usleep(time*1000);// to be tuned.
  hw_nosound();
  return;
}

int main(int argc, char **argv) {

  // Steve Reich : piano phase, motif principal ;o)
  int tune[12] = { 329, 370, 494, 554, 587, 370, 329, 554, 494, 370, 587, 554 };
  int i;

  if (ioperm(SPKR_PORT, 3, 1)) {perror("ioperm"); exit(1);}
  if (ioperm(TIMER_COMMAND_REGISTER, 8, 1)) {perror("ioperm"); exit(1);}
  if (ioperm(TIMER_CHANNEL2_DATA_PORT, 8, 1)) {perror("ioperm"); exit(1);}

  for (i = 0 ; i < 12 ; i++) {
    zong(tune[i], 150);
  }

  return 0;
}
