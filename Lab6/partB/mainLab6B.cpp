/* main.cpp - Client for Hamming Codes test
 * Author: Michael Galle 
 *
 *
 */

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

 // Function to print the matrix multiplication (this function prints integers)
void showMult(int nRows, int mCols, int* H, int* x, int* y) {
	int row, col, r, c;			// row and col counter 
	for (row = 0; row < nRows; row++) {
		printf("  [ %d ] %c [ ", y[row], (row == 0) ? '=' : ' ');
		for (col = 0; col < mCols; col++) {
			printf("%d ", H[row * mCols + col]);
		}
		if (row < mCols) {
			printf("] [ %d ] \n", x[row]);
		}
		else {
			printf("]\n");
		}
	}
	// if mCols > nRows then x has more to display
	if (mCols > nRows) {
		for (r = nRows; r < mCols; r++) {
			//printf("                ");
			for (c = 0; c < mCols; c++) {
				printf("    ");
			}
			printf("[ %d ]\n", x[r]);
		}
	}

}

 // Testing mainline for Hamming encode/decode (This matrix is the same as the one in the presentation)
int main() {
	int	H_Encode[7][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1},{0,1,1,1},{1,0,1,1},{1,1,0,1} };
	int H_Decode[3][7] = { {0,1,1,1,1,0,0}, {1,0,1,1,0,1,0}, {1,1,0,1,0,0,1} };
	int nRowsEnc = 7, mColsEnc = 4, nRowsDec = 3, mColsDec = 7;

	int x[4] = { 1, 0, 1, 1 };		// Message to send 
	int r[7];						// Resulting codeword r = p with parity bits added 
	int s[3];						// Error syndrome - all zeros if no error 

	// No Error

	printf("\nMessage (r) sent to and received by receiver:"); 
	printf("\n***************************************\n");

	MultiplyHx((int*)H_Encode, nRowsEnc, mColsEnc, x, r);
	showMult(nRowsEnc, mColsEnc, (int*)H_Encode, x, r);


	printf("\nSyndrome computed at receiver (all 0's then no error):");
	printf("\n***************************************\n");

	MultiplyHx((int*)H_Decode, nRowsDec, mColsDec, r, s);	// No error
	showMult(nRowsDec, mColsDec, (int*)H_Decode, r, s);


	// Error introduced
	printf("\nMessage (r) sent to and received by receiver has error at r[1]:");
	printf("\n***************************************\n");

	MultiplyHx((int*)H_Encode, nRowsEnc, mColsEnc, x, r);
	r[1] = 1;		// Introduce an error to show effect on syndrome 
	showMult(nRowsEnc, mColsEnc, (int*)H_Encode, x, r);


	printf("\nSyndrome computed at receiver \n (error in r[1] indicated by pattern of syndrome matching col 1 in decode matrix):\n");
	printf("\n***************************************\n");

	MultiplyHx((int*)H_Decode, nRowsDec, mColsDec, r, s);	// Error r[1] = 1 (see presentation for what this means - it is in the example)
	showMult(nRowsDec, mColsDec, (int*)H_Decode, r, s);
}