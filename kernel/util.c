#include "util.h"

/* Copy a length of memory from one location to another. */
void memory_copy(char* source, char* dest, uint32_t no_bytes)
{
   uint16_t i;
   for (i=0; i<no_bytes; i++)
      *(dest + i) = *(source + i);
}
