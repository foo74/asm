#include "screen.h"
#include "low_level.h"

void print_string(char input[], size_t string_length, char row)
{
   unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;
   int i;
   int j;

   if (row > MAX_ROWS)
      vidmem += ((MAX_ROWS-1)*MAX_COLS*2);
   else
      vidmem += row*160;

   if (row > MAX_ROWS)
   {
      for (int i=row-MAX_ROWS-1; i >= 0; i--)
      {
         scroll_up();
      }
      set_colors();
      set_cursor(MAX_ROWS-1, string_length-1);
   }
   else
      set_cursor(row, string_length-1);

   for (i=0, j=0; input[i] != 0; i++)
   {
      vidmem[j++] = input[i]; 
      vidmem[j++] = CHAR_COLOR; 
   }
}

void set_colors()
{
   unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;
   int i;
   for (i=1; i < MAX_ROWS*MAX_COLS*2; i+= 2)
      vidmem[i] = CHAR_COLOR;
}

void print_char(char character, int row, int col, char attribute_byte)
{
   unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;
   int offset;

   if (!attribute_byte)
      attribute_byte = GREEN_ON_BLACK;

/*
   set_cursor(row, col);
*/

   offset = get_cursor_offset();

   if (offset > MAX_COLS*MAX_ROWS)
   {
      scroll_up();
      offset = offset - 80;
   }

   offset = offset*2;

   /*
   if (character == '\n')
   {
      int rows = offset / (2*MAX_COLS);
      offset = get_screen_offset(79, rows);
   }
   else
   */
   {
      vidmem[offset] = character;
      vidmem[offset+1] = attribute_byte;
   }

   /* offset = handle_scrolling(offset); */
   /* set_cursor(row, col + 1); */
}

void scroll_up()
{
   int i;
   unsigned char *video_memory = (unsigned char *)VIDEO_MEMORY;

   for (i=0; i<=MAX_ROWS; i++)
   {
      memory_copy((video_memory+160), video_memory, 160);
      video_memory += 160;
   }
}

int handle_scrolling(int cursor_offset)
{
   int i;
   unsigned char *video_memory = (unsigned char *)VIDEO_MEMORY;

   /* if cursor is in the start buffer size then don't scroll */
   /*
   if (cursor_offset < (MAX_ROWS*MAX_COLS))
      return cursor_offset;
   else
   */
      for (i=0; i<MAX_ROWS; i++)
      {
         memory_copy((video_memory+160), video_memory, 160);
         video_memory += 160;
      }
/*
      memory_copy(video_memory+(MAX_COLS*2), video_memory, MAX_COLS*2);
      video_memory += (MAX_COLS*2);
      memory_copy(video_memory+(MAX_COLS*2), video_memory, MAX_COLS*2);
*/
   
   cursor_offset -= MAX_COLS;

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
   set_cursor(0, 1);
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

int get_cursor_offset()
{
   /* we are only dealing with positive so used unsigned. inlcude stdint.h */
   int cursor_loc = 0;

   /* receive the data from the IO ports on the bus */
   port_byte_out(REG_SCREEN_CTRL, 14);
   cursor_loc = port_byte_in(REG_SCREEN_DATA) << 8;
   port_byte_out(REG_SCREEN_CTRL, 15);
   cursor_loc += port_byte_in(REG_SCREEN_DATA);

   return cursor_loc;
}
