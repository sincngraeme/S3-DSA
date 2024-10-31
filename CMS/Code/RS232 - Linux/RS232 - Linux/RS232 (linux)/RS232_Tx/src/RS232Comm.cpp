/*	RS232 Communication : Function implementations 
 *  Copyright 2019 Michael Galle 
 *  
 *  Source 1: https://www.cmrr.umn.edu/~strupp/serial.html
 * 	Source 2: http://www.tldp.org/HOWTO/Serial-Programming-HOWTO/index.html
 *  Source 3: http://man7.org/linux/man-pages/man3/termios.3.html 
 *  Source 4: https://man7.org/linux/manpages/man2/fcntl.2.html
 * 
 */

#include <stdio.h>		
#include <string.h>
#include <unistd.h>		// Unix standard functions
#include <fcntl.h>		// File control funcitons
#include <errno.h>		// Error number definitions
#include <termios.h>	// POSIX terminal control definitions
#include "RS232Comm.h"


// Open a port 
int openPort(const char* port) {
	int fd;											// file descriptor for the port
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);	// Open for reading and writing, not as controlling terminal, no delay (no sleep - keep awake) (see Source 1)
	if (fd == -1) {
		perror("\nError: could not open specified port\n"); 
	} else {
		fcntl(fd, F_SETFL, 0);						// Manipulates the file descriptor ands sets status FLAGS to 0 (see Source 4)
													// Block (wait) until characters come in or interval timer expires
	}
	return(fd);
}

void configPort(int fd) {
	struct termios options;
	tcgetattr(fd, &options);						// Fills the termios structure with the current serial port configuration 

	// Change the current settings to new values

	// Set baud rate
	cfsetispeed(&options, BIT_RATE);				// Input speed (rate)  -- Most systems don't support different input and output speeds so keep these the same for portability
	cfsetospeed(&options, BIT_RATE);				// Output speed (rate)

	// Enable the receiver and set as local mode - CLOCAL & CREAD should always be enabled. 
	// CLOCAL so that program does not become owner of the port
	// CREAD so that the serial interface will read incoming data
	options.c_cflag |= (CLOCAL | CREAD);

	// Set other options to match settings on Windows side of comm (No parity, 1 stop bit) - See Source 1 
	options.c_cflag &= ~PARENB;						// PARITY NOT ENABLED
	options.c_cflag &= ~CSTOPB;						// CSTOPB = 2 stop bits (1 otherwise). Therefore ~CSTOPB means 1 stop bit
	options.c_cflag &= ~CSIZE;						// Mask the character size to be in bits
	options.c_cflag |= CS8;							// Use 8 bit data (per character)
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Set the port for RAW input with no echo or other input signals
	options.c_oflag &= ~OPOST;						// Use RAW output mode
	options.c_cc[VMIN] = 0;							// Min # of chars to read. When 0 VTIME specifies the wait time for every character
	options.c_cc[VTIME] = 240;						// Time in 1/10ths of a second to wait for every character before timing out. 
													// If VTIME is set to 0 then reads will block forever (port will only read)
	// Apply the new options to the port
	tcsetattr(fd, TCSANOW, &options); 				// TCSANOW makes changes without waiting for data to complete
}