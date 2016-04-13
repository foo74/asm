/**************************************************************************
 * Attribute byte code. first 4 bits are background, next 4 are foreground.
 * 0 = BLACK            8 = DARK GREY
 * 1 = BLUE             9 = LIGHT BLUE
 * 2 = GREEN           10 = LIGHT GREEN
 * 3 = CYAN            11 = LIGHT CYAN
 * 4 = RED             12 = LIGHT RED
 * 5 = MAGENTA         13 = LIGHT MAGENTA
 * 6 = BROWN           14 = LIGHT BROWN
 * 7 = LIGHT GREY      15 = WHITE
 **************************************************************************/

#define CHAR_COLOR 0x02
#define VIDEO_MEMORY 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25

void clear_screen(char *);

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory = VIDEO_MEMORY;
   char hello[] = "HELLO";
   int i;

   /* At the address pointed to by video_memory, store the character 'X'
    * (i.e. display 'X' in the top-left of the screen). */

   /*
   for (i=0; hello[i] != 0; i++)
   {
      *video_memory++ = hello[i];
      *video_memory++ = CHAR_COLOR;
     
      *video_memory++ = 'X';
      *video_memory++ = CHAR_COLOR;
      video_memory = video_memory + 0x100;
      *video_memory++ = 'Y';
      *video_memory++ = CHAR_COLOR;
   }
      */

   clear_screen(video_memory);

   /* last char of line is 0x9E in hex 
   video_memory += (80 * 2);
   *video_memory++ = 'X';
   *video_memory++ = CHAR_COLOR;
*/
   
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

/*
get_cursor()
{
}

set_cursor()
{
}

get_screen_offset()
{
}

handle_scrolling()
{
}
*/
