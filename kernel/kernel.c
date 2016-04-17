#include "../drivers/screen.h"
#include "../drivers/low_level.h"

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory =  (char *)VIDEO_MEMORY;
   char hello[] = "HELLO";
   int cursor;

   clear_screen(video_memory);

   print_char('a', 5, 0, 0);
/*
   set_cursor(5, 0);
   cursor = get_cursor();
   print_message(cursor+video_memory, hello);
*/
}
