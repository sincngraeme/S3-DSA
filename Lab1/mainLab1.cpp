/* main.cpp : Testing mainline for Lab #1 
*            By: Michael Galle & Jack Cole 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Parity.h"  // Header file includes Prototypes defined in Parity.cpp

int main(int argc, char *argv[])
{
	int	i, rc;

	// Ensure there is at least one argument supplied by user
	if (argc < 2) {
		fprintf(stderr, "Usage: Parity <string1> <string2> ..., where strings must be a series of 1's and 0's.\n");
		return(0);
	}

	// Test the byte-oriented (ASCII) version - 'ParityOnBytes'
	for (i = 1; i < argc; ++i) {
		rc = ParityOnBytes(argv[i], strlen(argv[i]));
		printf("For %s, ParityOnBytes() is %s.\n", argv[i], (rc == PAR_EVEN) ? "even" : ((rc == PAR_ODD) ? "odd" : "ERROR"));
	}
	
	printf("Press any key to end program ..."); 
	getchar();  // Keep console open until user presses enter 
	return(0); 
}


