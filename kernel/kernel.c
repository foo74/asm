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

#define CHAR_COLOR 0x04

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory = 0xb8000;
   char hello[] = "HELLO";
   int i;

   /* At the address pointed to by video_memory, store the character 'X'
    * (i.e. display 'X' in the top-left of the screen). */
   for (i=0; hello[i] != 0; i++)
   {
      *video_memory++ = hello[i];
      *video_memory++ = CHAR_COLOR;
     
      /* 
      *video_memory++ = 'X';
      *video_memory++ = CHAR_COLOR;
      video_memory = video_memory + 0x100;
      *video_memory++ = 'Y';
      *video_memory++ = CHAR_COLOR;
      */
   }
   
}
