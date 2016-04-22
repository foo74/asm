#include "../drivers/screen.h"
#include "../drivers/low_level.h"
#include "util.h"

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory =  (char *)VIDEO_MEMORY;
   char hello[] = "HELLO";
   char bye[] = "BYE BYE";
   char starting[] = "Foo OS booting...";
   int cursor;
   int i;
   int a;
   size_t size;
   size_t size2;
   size_t size3;
   i = a = 0;

   size = sizeof(hello) / sizeof(hello[0]);
   size2 = sizeof(bye) / sizeof(bye[0]);
   size3 = sizeof(starting) / sizeof(starting[0]);
   

   clear_screen(video_memory);
   print_string(starting, size3, 0);
   for (i=0; i<0xaffffff;i++)
      a += 10;
   print_string(hello, size, 20);
   for (i=0; i<0xaffffff;i++)
      a += 10;
   print_string(bye, size2, 30);

/*

   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 2, i, 0);

   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 3, i, 0);

   while ( a < 0xfffffff )
      a = a + 1;

   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 25, i, 0);
   for (i=0; hello[i] != 0; i++)
      print_char(hello[i], 26, i, 0);
*/

/*
   scroll_up();
   scroll_up();
*/

/*
   handle_scrolling(0);

   memory_copy(video_memory, video_memory + 100, 10);
   set_cursor(5, 0);
   cursor = get_cursor();
   print_message(cursor+video_memory, hello);
*/
}
