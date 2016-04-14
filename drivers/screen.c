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
