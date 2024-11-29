#define UNICODE

#include "TxRx.h"
#include "RLE.h"
#include "RS232Comm.h"
#include "header.h"
//#include "Huffman.h"
#include <iostream>

// Logic in pseudo code or the bitwise cFlag (settings) for the header:

    // run the compression (temp: set variable with compression type)
    // set the cFlag from port1 object to include this compression
    // current value: cFlag = 0b 00 00 00 00;
    // set the value: port1.header.cFlags |= 0b 00 10 00 00;
    // run the type of compression specified
    // set headers 
    // set up header


// Different options for bitwise compression
char compress(void* payload, char cFlags, DWORD szBuf)
{
    if(cFlags & RLE & HUFFMAN)       // check the bits
    {
        printf("Both Compressions"); // print the compression type
    }
    else if(cFlags & RLE)
    {
        char* outbuf = (char*)calloc(szBuf, sizeof(char*));             // initialize output buffer
        long long outlength = RLEcompress(payload, szBuf, outbuf, szBuf);   // compress the buffer
        
        //Display the compressed message
        printf("Compressed message of length %llu", outlength);
        return outlength;
    }
    else if(cFlags & HUFFMAN)
    {
        printf("Huffman");

        //int Huff:: HuffmanCompress(_______);
    }
    else 
    {
        printf("no compression used");
    }
 return(cFlags);
}

void encryption(void* buf, char cFlags)
{
	if(cFlags & VIGENERE & XOR)
	{
        printf("Both encryptions");
	}
    else if (cFlags & VIGENERE)
    {
        printf("vigenere");
    }
    else if (cFlags & XOR)
    {
        printf("xor");
    }
    else {
        printf("no encryption used");
    }
}

char dataCorrect(void* buf, char cFlags){
    if(cFlags & VOTEON)
    {
        printf("Voteon");
    }
    else
    {
        printf("No data correction used");
    }
    return(cFlags);
}
