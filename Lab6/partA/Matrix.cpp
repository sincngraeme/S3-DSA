void MultiplyAx(float* A, int n , int m, float* x1, float* y1 )
{
    for (int i = 0; i < n; i++)      // loop through and A rows
    {
        int sum = 0;                 // set sum to 0 for every row, in an example it could also be written as y[row]

        for (int j = 0; j < m; j++)                      // loop through A cols, and x1 rows
        {
            // multiply A element with x1 element
            sum += (*(A + i * m + j)) * (*(x1 + j));     // *(A + row * m + col) this handles the pointer offset 
        }                                                // y[row] += A[row *m + col] * x[col]

      *(y1 + i) = sum;          // set each element of y1 to sum for each row
    }
}

