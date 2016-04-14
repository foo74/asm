#include <stdio.h>
/* #include <stdint.h> so we can cast int to pointer type on line 19. */

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
#define VIDEO_ADDRESS 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25
/* Screen device I/O ports. */
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5


void set_cursor();
void print_char(char character, int col, int row, char attribute_byte);
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void clear_screen(char *);
void print_message(char* video_memory, char s[]);
