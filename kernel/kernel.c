#include "../drivers/screen.h"
#include "../drivers/low_level.h"

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory =  (char *)VIDEO_MEMORY;
   char hello[] = "HELLO";
   int i;

   clear_screen(video_memory);

   print_message(video_memory, hello);
   set_cursor(5, 79);
}
