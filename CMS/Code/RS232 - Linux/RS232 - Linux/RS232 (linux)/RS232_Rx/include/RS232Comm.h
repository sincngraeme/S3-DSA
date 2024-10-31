/*	RS232Comm.h : Interface for RS232 based communications 
 *  Copyright 2019 Michael Galle 
 *  
 *  Source 1: https://www.cmrr.umn.edu/~strupp/serial.html
 * 	Source 2: http://www.tldp.org/HOWTO/Serial-Programming-HOWTO/index.html
 *  Source 3: http://man7.org/linux/man-pages/man3/termios.3.html 
 *  Source 4: https://man7.org/linux/manpages/man2/fcntl.2.html
 * 
 */

#define BIT_RATE B9600								// See Table 4 in Source 1 for options

const char PORT1[] = "/dev/ttyS1";  //COM6          //"/dev/ttyUSB0";				// determine the USB port names from terminal using $ dmesg | grep tty 
const char PORT2[] = "/dev/ttyS2";  //COM7          //"/dev/ttyUSB1";

// Function prototypes  
int openPort(const char* port);                     // Opens port and returns file descriptor 
void configPort(int fd);                            // Configures port settings
