/* main() : Testing for matrix multiplication function - LAB 6 
 *				Michael Galle & Jack Cole, 2023
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "Matrix.h"

// Function to print the matrix multiplication (this function prints floats)
void showMult(int nRows, int mCols, float* A, float* x, float* y) {
	int row, col, r, c;			// row and col counter 
	for (row = 0; row < nRows; row++) {
		printf("  [ % 6.3f ] %c [ ", y[row], (row == 0) ? '=' : ' ');
		for (col = 0; col < mCols; col++) {
			printf("% 6.3f ", A[row * mCols + col]);
		}
		if (row < mCols) {
			printf("] [ % 6.3f ] \n", x[row]);
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
				printf("            ");
			}
			printf("[ % 6.3f ]\n", x[r]);
		}
	}

}

// a testing mainline 
int main( int argc, char *argv[] ) 
{
	int		r, c, n = 3, m = 4;
	float	A[3][4] = { { 1.0, 2.0, 3.0, 4.0 }, { 2.0, 1.0, 1.0, 2.0 }, { 3.0, -3.0, 2.0, -2.0 } };
	// The nested braces indicating the intended row, above are optional. The line above is equivalent to: 
	//	float A[3][4] = {1.0, 2.0, 3.0, 4.0, 2.0, 1.0, 1.0, 2.0, 3.0, -3.0, 2.0, -2.0 };

	float	x1[4] = { -1.0, 2.0, -1.0, 2.0 };
	float	y1[3];			
	
	// multiply A times x1
	MultiplyAx( (float *)A, n, m, x1, y1);		// A is a one dimensional array that is n x m long!!!

	// show the results as y = Ax.
	showMult(n, m, (float*)A, x1, y1);

	printf("Press enter to continue ...");
	getchar();

	return(1);
}

