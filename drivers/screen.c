#include "screen.h"
#include "low_level.h"

void print_char(char character, int row, int col, char attribute_byte)
{
   unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;
   int offset;

   if (!attribute_byte)
      attribute_byte = GREEN_ON_BLACK;

   set_cursor(row, col);

   offset = get_cursor();

   if (character == '\n')
   {
      int rows = offset / (2*MAX_COLS);
      /*offset = get_screen_offset(79, rows);*/
   }
   else
   {
      vidmem[offset] = character;
      vidmem[offset+1] = attribute_byte;
   }

   /*offset = handle_scrolling(offset);*/
   set_cursor(row, col + 1);
}

int handle_scrolling(int cursor_offset)
{
   int i;
   unsigned char *video_memory = (unsigned char *)VIDEO_MEMORY;

   /* if cursor is in the start buffer size then don't scroll */
   if (cursor_offset < (MAX_ROWS*MAX_COLS*2))
      return cursor_offset;

   for (i=1; i<MAX_ROWS; i++)
      memory_copy(video_memory, video_memory+(MAX_COLS*2), MAX_COLS*2);
   
   cursor_offset -= 2*MAX_COLS;

   return cursor_offset;
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

int get_cursor()
{
   /* we are only dealing with positive so used unsigned. inlcude stdint.h */
   int cursor_loc = 0;

   /* receive the data from the IO ports on the bus */
   port_byte_out(REG_SCREEN_CTRL, 14);
   cursor_loc = port_byte_in(REG_SCREEN_DATA) << 8;
   port_byte_out(REG_SCREEN_CTRL, 15);
   cursor_loc += port_byte_in(REG_SCREEN_DATA);

   return cursor_loc * 2;
}
