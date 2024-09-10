/* main.cpp : Testing mainline for Lab #2 
*            By: Michael Galle & Jack Cole 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "Parity.h"  // Header file includes Prototypes defined in Parity.cpp


/* PackToBits() : Utility function to convert the ASCII form to packed binary 
 * 
 *		NOTE: malloc()'s the buffer to hold the packed binary, and
 *		returns the pointer. CALLER SHOULD FREE THE BUFFER WHEN DONE.
 *		Returns NULL if malloc() fails, or if string contains bad characters.
 *		Returns the output length (rounded up) via pOutLen;
 *		
 *		buf is a pointer to a char buffer (array)
 *		iBufLen is the number of bytes in buf array
 *		*pOutlen contains the number of bytes in the output buffer  
 *		PackToBits returns a pointer to the output buffer
 */
static unsigned char* PackToBits( char* buf, int iBufLen, int *pOutLen )    
{
	unsigned char*	p;														// Pointer to START of output buffer (smaller than input buf)
	unsigned char*  pCur;													// Pointer that is moved to SELECT individual bytes in the output buffer						
	unsigned char	iMask;													// Mask used to select INDIVIDUAL BITS in the output buffer
	int				i;														// 'for' loop counter
	
	// The packed form will be 1/8th as long as the ASCII form (one bit per char vs one byte), taken to the next largest integer					  
	*pOutLen = (iBufLen + 7) / 8; 											// *pOutLen is the number of bytes to be allocated in the output buffer (smaller than buf since 1/8th the size)
	p = (unsigned char *)calloc( *pOutLen, sizeof(unsigned char));         	// Allocate the space for the output buffer and SET ALL BITS TO ZERO
																		  
	// Walk through the input string setting the bitset
	pCur = p; 
	for( i=0, iMask = 0x80; i < iBufLen; ++i, ++buf ) {						// iMask = 0x10000000					
		// Check for a '1' or a '0' or something illegal in buffer
		if (*buf == '1') { *pCur |= iMask; }							  	// *pCur dereferences pCur so indicates/sets the value it points to in memory
																		  	//  a |= b   is the same as  a = a | b  (a OR b)  (if either is a 1 then the result is 1)
		else if( *buf != '0' )  {    									  	// If user input anything other than '1' or '0' we have an error (return NULL to signal error) 
			// ERROR: Must free p or we have a memory leak
			free(p);
			return(NULL);
		}
		
		// Prepare mask for next time, and chack for start of new byte
		iMask >>= 1;													  	// Shift all bits by one position to the right to select next bit  (e.g., 0x10000000  --> 0x01000000)
		if (iMask == 0) {												  	// The '1' bit was shifted all the way right and now need to go to next byte in the output buffer (p)
			// Mask must be reset, and new data processed
			iMask = 0x80; 
			++pCur; 
		}
	}

	return(p);																// Return pointer to the output buffer
}


int main(int argc, char *argv[])
{
	int					i, rc, iPackedLen;
	unsigned char		*bPackedString;
	
	// Ensure there is at least one argument supplied by user
	if (argc < 2) {
		fprintf(stderr, "Usage: Parity <string1> <string2> ..., where strings must be a series of 1's and 0's.\n");
		return(0);
	}

	// Test the byte-oriented (ASCII) version - 'ParityOnBytes' (LAB 1)
	printf("Byte Oriented ASCII version - Lab 1 results: \n");
	for (i = 1; i < argc; ++i) {
		rc = ParityOnBytes(argv[i], strlen(argv[i]));
		printf("For %s, ParityOnBytes() is %s.\n", argv[i], (rc == PAR_EVEN) ? "even" : ((rc == PAR_ODD) ? "odd" : "ERROR"));
	}
	printf("\n\n");
	
	// Test the bit-oriented version - 'Parity' (LAB 2)
	// To do this we first need to convert the ASCII characters to bits - Not trivial since the length could be ANYTHING ( need to use PackToBits() )
	printf("Bit-oriented version - Lab 2 results: \n");
	for( i=1; i < argc; ++i ) {
		// Convert from string to packed bits
		bPackedString = PackToBits( argv[i], strlen( argv[i] ), &iPackedLen );   // argv[i] is the ith char string input by user (i.e. 1100 ), i elements are separated by spaces
																				 // &iPackedLen is the memory location of the int iPackedLen which is passed to PackToBits() and stores the value iOutLen (length of buf in bits)
		if( bPackedString ) {  // i.e. if not NULL
			rc = 	Parity( bPackedString, iPackedLen );
			printf("For %s, Parity() is %s. \n", argv[i], ( rc == PAR_EVEN ) ? "even" : ( ( rc == PAR_ODD ) ? "odd" : "ERROR"));
			free( bPackedString); 
		} else {
			fprintf(stderr, "Bad test string, or unable to allocate space for %s. \n", argv[i] );
		}
	}
	
	printf("Press any key to end program ..."); 
	getchar();  // Keep console open until user presses enter 
	return(0); 
}


