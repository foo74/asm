#include <stdint.h>
#include "low_level.h"
/*****************************************************************************
 * A C wrapper function that reads a byte from the specified port
 * "=a" (result) means: put AL register in variable RESULT when finished
 * "d" (port) means: load EDX with port.
 *****************************************************************************/
unsigned char port_byte_in(unsigned short port)
{
   unsigned char result;
   __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
   return result;
}

void port_byte_out(unsigned short port, unsigned char data)
{
   __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port)
{
   unsigned short result;
   __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
   return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
   __asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}

/* https://littleosbook.github.io/#moving-the-cursor provide info how */
void set_cursor(int row, int col)
{
   /* we are only dealing with positive so used unsigned. inlcude stdint.h */
   uint16_t mem_loc = 0;
   uint8_t lower_eight_bits = 0;
   uint8_t upper_eight_bits = 0;

   /* calculate the memory location */
   mem_loc = ((row * 80) + col);

   /* grab the upper and lower byte */
   lower_eight_bits = mem_loc & 0b0000000011111111;
   upper_eight_bits = (mem_loc & 0b1111111100000000) >> 8;

   /* send the data to the IO ports on the bus */
   port_byte_out(REG_SCREEN_CTRL, 14);
   port_byte_out(REG_SCREEN_DATA, upper_eight_bits);
   port_byte_out(REG_SCREEN_CTRL, 15);
   port_byte_out(REG_SCREEN_DATA, lower_eight_bits);
}
