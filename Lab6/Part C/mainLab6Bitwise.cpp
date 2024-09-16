/* main.cpp - Client for Hamming Codes test IN BITWISE FORM
 * Authors: Michael Galle & Jack Cole
 *
 *
 */

#include "MatrixBitwise.h"
#include <stdio.h>
#include <stdlib.h>

// Function to show bitwise matrix multiplication
void showMult(int nRows, int mCols, unsigned int H, unsigned char x, unsigned char y) {
	int rows, col, r, c;										// row and col counter 
	unsigned int Hbit = 0x80000000;								// position (bit) in the A 'array'
	unsigned char coly = 0x80;									// column (bit) in output vector y 
	unsigned char colx = 0x80;									// column (bit) in input vector x
	unsigned char output;										// Character to output 

	// Go through y, H and x and output '1' or '0' by polling the bits
	for (rows = 0; rows < nRows; rows++) {
		output = (y & coly) ? '1' : '0';						// Poll the bit indicated by coly in y and print a '1' if the '&' operation is non-zero else print '0'
		printf("  [ %c ] %c [ ", output, (rows == 0) ? '=' : ' ');
		for (col = 0; col < mCols; col++) {
			output = (H & Hbit) ? '1' : '0';					// Poll the bit indicated by Hbit in H and print a '1' if the '&' operation is non-zero else print '0'
			printf("%c ", output);
			Hbit >>= 1;											// Go to next bit in H
		}
		if (rows < mCols) {
			output = (x & colx) ? '1' : '0';					// Poll the bit indicated by colx in x and print a '1' if the '&' operation is non-zero else print '0' 
			printf("] [ %c ] \n", output);
			colx >>= 1;											// Go to next bit in x
		}
		else {
			printf("]\n");
		}
		coly >>= 1;												// Go to next bit in y
	}
	// if mCols > nRows then x has more to display
	if (mCols > nRows) {
		for (r = nRows; r < mCols; r++) {
			output = (x & colx) ? '1' : '0';					// Poll and output additional bits in x
			for (c = 0; c < mCols; c++) {
				printf("    ");									// Formatting
			}
			printf("[ %c ]\n", output);
			colx >>= 1;											// Go to next bit in x
		}
	}

}

// Function to indicate which bit is in error based on the syndrome
unsigned char errorBit(unsigned char s) {
	/* First 3 bits in s are the syndrome. The column number in H_Decode that these three bits matches is the index of the bit in error. 
	 * if s = 0b01100000 = 0x60 errorBit returns index 0   (the first 3 bits match column 0 in H_Decode) - See PowerPoint slides for explanation and illustration
	 *    s = 0b10100000 = 0xA0 errorBit returns index 1
	 *	  s = 0b11000000 = 0xC0 errorBit returns index 2
	 *	  s = 0b11100000 = 0xD0 rerrorBit returns index 3
	 */

	switch (s) {
	case 0x60:
		return(0);
		break;
	case 0xA0:
		return(1);
		break;
	case 0xC0:
		return(2);
		break;
	case 0xD0:
		return(3);
		break;
	}
}
 

// Testing mainline for Hamming encode/decode (This matrix is the same as the one in the presentation)
int main() {
	//int H_Encode[7][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{0,1,1,1},{1,0,1,1},{1,1,0,1} }; - THIS IS THE CODE FROM LAB 6 PART B
	//int H_Decode[3][7] = { {0,1,1,1,1,0,0}, {1,0,1,1,0,1,0}, {1,1,0,1,0,0,1} };					  - THIS IS THE CODE FROM LAB 6 PART B
	unsigned int HENC = 0b00001000010000100001011110111101 << 4;		// 32 bit (since unsigned integers are 4 bytes) encode matrix in bitwise form with bits shifted left by 4 so first bit is set correctly (see H_Encode above)  - REVISED FOR BITWISE OPERATION
	unsigned int HDEC = 0b00000000000011110010110101101001 << 11;		// 32 bit (since unsigned integers are 4 bytes) decode matrix in bitwise form with bits shifted left by 11 so first bit is set correctly (see H_Decode above) - REVISED FOR BITWISE OPERATION
	int nRowsEnc = 7, mColsEnc = 4;							// Dimensions of Hamming Encode matrix
	int nRowsDec = 3, mColsDec = 7;							// Dimensions of Hamming Decode matrix
	
	// Set message
	//int x[4] = { 1, 0, 1, 1 };							// Message to send - THIS IS THE CODE FROM LAB 6 PART B
	//char x = 0b10110000;									// This is the message in binary  - REVISED FOR BITWISE OPERATION
	unsigned char x = 0xB0;									// This is the message in Hex     - REVISED FOR BITWISE OPERATION (alternate using Hex)

	//int r[7];												// Received message at receiver (r) - THIS IS THE CODE FROM LAB 6 PART B
	unsigned char r = 0;									// Reserve one byte, only using first 7 bits for r - REVISED FOR BITWISE OPERATION

	//int s[3];												// Error syndrome - all zeros if no error			- THIS IS THE CODE FROM LAB 6 PART B
	unsigned char s = 0;									// Reserve one byte only using first 3 bits			- REVISED FOR BITWISE OPERATION


	/**************************DEMO FUNCTIONALITY ********************************************/

	// No Error
	printf("\nMessage received (r) by receiver:"); 
	printf("\n***************************************\n");

	MultiplyHx_bitwise(HENC, nRowsEnc, mColsEnc, x, &r);
	showMult(nRowsEnc, mColsEnc, HENC, x, r);

	
	printf("\nSyndrome computed at receiver (all 0's then no error):");
	printf("\n***************************************\n");

	MultiplyHx_bitwise(HDEC, nRowsDec, mColsDec, r, &s);	// No error
	showMult(nRowsDec, mColsDec, HDEC, r, s);


	// Error introduced
	printf("\nMessage (r) sent to and received by receiver has error at r[1]:");
	printf("\n***************************************\n");

	MultiplyHx_bitwise(HENC, nRowsEnc, mColsEnc, x, &r);
	// Introduce an error to show effect on syndrome  - Flip the second bit in the message that includes the parity bits from 0 to 1
	r |= 0b01000000;

	showMult(nRowsEnc, mColsEnc, HENC, x, r);


	printf("\nSyndrome computed at receiver \n (error in r[1] indicated by pattern of syndrome matching col 1 in decode matrix):\n");
	printf("\n***************************************\n");

	MultiplyHx_bitwise(HDEC, nRowsDec, mColsDec, r, &s);	// Error r[1] = 1 (see presentation for what this means - it is in the example)
	showMult(nRowsDec, mColsDec, HDEC, r, s);

	printf("\nThe bit in error is: %d \n", errorBit(s));

	return(0);
}