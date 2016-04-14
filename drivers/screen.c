#include "screen.h"

/*
void print_char(char character, int col, int row, char attribute_byte)
{
   unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

   if (!attribute_byte)
      attribute_byte = GREEN_ON_BLACK;

   int offset;
   if (col >= 0 && row >= 0)
      offset = get_screen_offset(col, row);
   else
      offset = get_cursor();

   if (character == '\n')
   {
      int rows = offset / (2*MAX_COLS);
      offset = get_screen_offset(79, rows);
   }
   else
   {
      vidmem[offset] = character;
      vidmem[offset+1] = attribute_byte;
   }

   offset = handle_scrolling(offset);
   set_cursor(offset);
}
*/

void set_cursor()
{
   port_byte_out(REG_SCREEN_CTRL, 14);
   port_byte_out(REG_SCREEN_DATA, 0x00);
   port_byte_out(REG_SCREEN_CTRL, 15);
   port_byte_out(REG_SCREEN_DATA, 0x50);
}
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
void print_message(char* video_memory, char s[])
{
   int i;
   for (i=0; s[i] != 0; i++)
   {
      *video_memory++ = s[i];
      *video_memory++ = CHAR_COLOR;
   }
}

void clear_screen(char* video_memory)
{
   int i, j;
   for (i=0; i<25; i++)
   {
      for (j=0; j<80; j++)
      {
         *video_memory++ = ' ';
         *video_memory++ = CHAR_COLOR;
      }
   }
}
