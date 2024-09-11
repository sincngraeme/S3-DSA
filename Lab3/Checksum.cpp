// contains definition for Checksum() function
#include <stdio.h>
#include "Checksum.h"

unsigned int Checksum(void* buf, int iBufLen, CHECKSUM iType)
{
    int i;
    unsigned char* buf8bit;             // for 8 bit
    unsigned short* buf16bit;   // for 16 bit
    unsigned int sum = 0, checksum = 0;


    switch(iType)
    {
        case CHK_16BIT:
            buf16bit = (unsigned short*)buf;            // cast the value to the 16bit width we want

            for (i = 0; i < iBufLen; i++)
            {
                sum += *buf16bit;                       // add the current 16bit chunk to the running total
                buf16bit++;                             // move to the next 16bit chunk in memory
            }

            checksum = sum % 0x10000;                // we only want 16 bits
            return(checksum);
            break;

        case CHK_8BIT:
            buf8bit = (unsigned char*)buf;                      // cast the value to the 8bit width we want

            for (i = 0; i < iBufLen; i++)
            {
                sum += *buf8bit;                        // add the current 8bit chunk to the running total
                buf8bit++;                              // move to the next 8bit chunk
            }

            checksum = sum % 0x100;                   // we only want 8 bits
            return(checksum);
            break;

        default:
            printf("you must use either a 16bit or 8bit number\n");
            return(0x10000);
    }

}

