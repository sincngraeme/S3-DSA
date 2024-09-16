/* Matrix.h - Implementation for matrix multiplication
 * Author: MG
 *
 */

#include "MatrixBitwise.h"
#include <stdio.h>

// Bitwise multiplication
void MultiplyHx_bitwise(unsigned int H, int nRows, int mCols, unsigned char x, unsigned char* y) {
	*y = 0;														// initialize bits in y to zero
	unsigned int Hbit = 0x80000000;								// position (bit) in the 32 bit H 'array' (equivalent to 0b10000000000000000000000000000000)
	unsigned char rowy = 0x80;									// bit (row) in output vector y (equivalent to 0b10000000 )
	unsigned char rowx = 0x80;									// bit (row) in input vector x (equivalent to 0b10000000 )
	unsigned int y_rowsum;										// sum in given row in output vector y

	for (rowy = 0x80;  rowy > (0x80>>nRows); rowy >>= 1) {		// For each bit in y (i.e. rowy) compute the sum (see PowerPoint slides for description)
		y_rowsum = 0;
		for (rowx = 0x80; rowx > (0x80>>mCols) ; rowx>>=1, Hbit>>=1) {   // bit shift rowx until it reaches the end of a column (i.e. 0b10000000>>mCols)
			if ((H & Hbit) != 0 && (x & rowx) != 0) {			// If both H and x bits are '1' (1 * 1 = 1) 
				y_rowsum++;										// then increment sum for that row 
			}
		}
		if ((y_rowsum % 2) == 1) {								// Convert the sum for each row to binary - '1' if sum is odd, leave '0' if even valued
			*y |= rowy;											// Set the coresponding bit in output vector y to '1' (originally initialized to 0) if odd	
		}														// Binary matrix mulitiplication is described in the PowerPoint slides for this lab
	}
	return;
}


