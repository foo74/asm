#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "../kernel/util.h"
/* #include <stdint.h> so we can cast int to pointer type on line 19.
 * #include <stddef.h> so we can use the size_t to pass the size of input. 
 */

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

/* Attribute byte for our default color scheme. */
#define GREEN_ON_BLACK 0x02
#define CHAR_COLOR 0x02
#define VIDEO_MEMORY 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25


void print_char(char, int, int, char);
void clear_screen(char *);
void print_message(char* , char []);
void set_cursor(int, int);
int get_cursor_offset();
int handle_scrolling(int);
void scroll_up();
void print_string(char [], size_t, char);
void set_colors();
