#include "../drivers/screen.h"
#include "../drivers/low_level.h"
#include "util.h"

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory =  (char *)VIDEO_MEMORY;

   char welcome[] = "Welcome to the Foo Operating System!\nIt is my pleasure you ran me.";
   char luke[] = "Luke \nI \nam \nyour \nfather.";
   char bye[] = "That's all folks! \nBye \nBye";
   int cursor;
   size_t size;

   clear_screen(video_memory);

   size = sizeof(welcome) / sizeof(welcome[0]);
   print_string(welcome, size, 1);

   size = sizeof(luke) / sizeof(luke[0]);
   print_string(luke, size, 10);

   size = sizeof(bye) / sizeof(bye[0]);
   print_string(bye, size, 18);
}
