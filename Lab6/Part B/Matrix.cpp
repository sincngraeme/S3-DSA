void MultiplyAx(float* A, int n , int m, float* x1, float* y1 )
{
    for (int i = 0; i < n; i++)      // loop through and A rows
    {
        int sum = 0;                 // set sum to 0 for every row

        for (int j = 0; j < m; j++)                      // loop through A cols, and x1 rows
        {
            // multiply A element with x1 element
            sum += (*(A + i * m + j)) * (*(x1 + j));     // *(A + row * m + col) this handles the pointer offset 
        }

      *(y1 + i) = sum;          // set each element of y1 to sum for each row
    }
}

void MultiplyHx(int* A, int n , int m, int* x1, int* y1 )
{
    for (int i = 0; i < n; i++)      // loop through and A rows
    {
        int sum = 0;                 // set sum to 0 for every row

        for (int j = 0; j < m; j++)                      // loop through A cols, and x1 rows
        {
            // multiply A element with x1 element
            sum += (*(A + i * m + j)) * (*(x1 + j));     // *(A + row * m + col) this handles the pointer offset 
        }

      *(y1 + i) = sum % 2;          // set each element of y1 to modulus of sum for each row since
}


