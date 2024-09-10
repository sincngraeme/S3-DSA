#include "Parity.h"

PARITY ParityOnBytes(char* buf, int iBufLen)
{
    int i = 0;  // counter variable to count 1s

    for(int j = 0; j < iBufLen; j++)        // iterate until the last character in argument
    {
        if(buf[j] == '1')                   // since we are counting ones
        {
            i++;  
        }
        else if(buf[j] != '0')              // since we are not counting 0s and if it is neither 0 nor 1 it must be WRONG!
        {
            return PAR_ERROR;
        } 
    }

    if(i % 2 == 0)
    {
        return PAR_EVEN;         // check if even or odd number                          
    }
    return PAR_ODD;              // mod can only produce 1 or 0: if not 0, must be 1
}