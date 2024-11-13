#include "Assignment4.h"


long long RLEcompress(unsigned char* in, long long iInLen, unsigned char* out, long long iOutMax) {

long long i = 0; 
long long outPos = 0; 
unsigned char cEsc = 0x1b; 
char count; 
unsigned char repeatedChar;

    while (i < iInLen) {
    count = 0;

    // Count the number of repeats until repeats stop (or until 255 characters reached)
    do { 
    memcpy(&repeatedChar, &in[i], 1); // Store the repeated character using memcpy()
    count++;// Increment the repeat counter
    } 

    while ((memcmp(&in[i], &in[i++], 1) == 0) && (count <= 255) && (i < iInLen)); // memcmp() == 0 when same
    // RLE encode (compress only if there are 3 or more repeats)
    if (count >= 3) {

    memcpy(&out[outPos++], &cEsc, 1); // 3 or more repeats
    memcpy(&out[outPos++], &count, 1);// Here, integers (HEX values not strings) are used rather than strings
    memcpy(&out[outPos++], &repeatedChar, 1); }

    // Process 2 characters without compression
    else if (count == 2){

    memcpy(&out[outPos++], &repeatedChar, 1);
    memcpy(&out[outPos++], &repeatedChar, 1);

    }

    // Process data without compression of count < 2
    else {
    memcpy(&out[outPos++], &repeatedChar, 1); }
    
    }

    return(outPos); // Stores the length of the output buffer – make sure it is less than iOutMax
}

long long RLEdecompress(unsigned char* in, long long iInLen, unsigned char* out, long long iOutMax, unsigned char cEsc){

long long i = 0; 
long long outPos = 0; 
char count; 
unsigned char repeatedChar; 
int j;

while (i < iInLen) {

    if ((memcmp(&in[i], &cEsc, 1) == 0) && (memcmp(&in[i], &in[i + 1], 1) != 0)){ // No repeats of ESE char, only one
    memcpy(&count, &in[i+1], 1); // Next byte stores repeat count
    memcpy(&repeatedChar, &in[i+2], 1); // Next byte stores repeated character
    i += 3; // Increment i by 3 (the RLE encoding length)
        
        for (j = 0; j < count; j++) {

            memcpy(&out[outPos++], &repeatedChar, 1);// Output repeated character to output buffer one character at a time
        }

        } else { // Single character - no repeats
            repeatedChar = in[i++];
            memcpy(&out[outPos++], &repeatedChar, 1);
        }
    }
    if (outPos <= iOutMax) { // Output buffer is less than max buffer size
    
    return(outPos);

    } else { // Output buffer exceeds max

        printf("Buffer overflow: Cannot decompress");
        return(0);

    }
}