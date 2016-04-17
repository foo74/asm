#include "../drivers/screen.h"
#include "../drivers/low_level.h"
#include "util.h"

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory =  (char *)VIDEO_MEMORY;
   char hello[] = "HELLO";
   int cursor;
   int i;

   clear_screen(video_memory);

   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 2, i, 0);

   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 20, i, 0);

/*
   memory_copy(video_memory, video_memory + 100, 10);
   set_cursor(5, 0);
   cursor = get_cursor();
   print_message(cursor+video_memory, hello);
*/
}
