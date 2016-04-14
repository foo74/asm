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

void set_cursor()
{
   port_byte_out(REG_SCREEN_CTRL, 14);
   port_byte_out(REG_SCREEN_DATA, 0x00);
   port_byte_out(REG_SCREEN_CTRL, 15);
   port_byte_out(REG_SCREEN_DATA, 0x50);
}
