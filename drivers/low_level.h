/*****************************************************************************
 * A C wrapper function that reads a byte from the specified port
 * "=a" (result) means: put AL register in variable RESULT when finished
 * "d" (port) means: load EDX with port.
 *****************************************************************************/


/* Screen device I/O ports. */
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void set_cursor();
