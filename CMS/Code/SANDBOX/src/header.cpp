#define UNICODE

#include "TxRx.h"
#include "RLE.h"
#include "RS232Comm.h"
#include "header.h"
//#include "Huffman.h"
#include <iostream>

void AudioCompressRLE(short* buf, DWORD szBuf, char cFlags)
{
    cFlags = (AUDIOBIT | RLE); // set the header to include compression type
    ///////////////////////
    char* outbuf = (char*)calloc(szBuf, sizeof(char*));             // initialize output buffer
    unsigned char cEsc = 0x1b;                                      // escape character
    long long outlength = RLEcompress(buf, szBuf, outbuf, szBuf);   // compress the buffer
    
    //Display the compressed message
	printf("Compressed message of length %llu", outlength);

}


void TextCompressRLE(char* buf, DWORD szBuf, char cFlags)
{
    cFlags = (AUDIOBIT | RLE); // set the header to include compression type
    ///////////////////////
    char* outbuf = (char*)calloc(szBuf, sizeof(char*));             // initialize output buffer
    unsigned char cEsc = 0x1b;                                      // escape character
    long long outlength = RLEcompress(buf, szBuf, outbuf, szBuf);   // compress the buffer
    
    //Display the compressed message
	printf("Compressed message of length %llu", outlength);

}

    // run the compression (temp: set variable with compression type)
    // set the cFlag from port1 object to include this compression
    // current value: cFlag = 0b 00 00 00 00;
    // set the value: port1.header.cFlags |= 0b 00 10 00 00;
    // run the type of compression specified
    // set headers 
    // set up header
void AudioCompressHuff(char* buf, DWORD szBuf, char cFlags)
{
    cFlags = (AUDIOBIT | HUFFMAN); // set the header to include compression type
    ///////////////////////
    char* outbuf = (char*)calloc(szBuf, sizeof(char*));             // initialize output buffer
    unsigned char cEsc = 0x1b;                                      // escape character
    long long outlength = RLEcompress(buf, szBuf, outbuf, szBuf);   // compress the buffer
    
    //Display the compressed message
	printf("Compressed message of length %llu", outlength);

}
void TextCompressHuff(char* buf, DWORD szBuf, char cFlags)
{
    cFlags = (TEXTBIT | HUFFMAN); // set the header to include compression type
    ///////////////////////
    char* outbuf = (char*)calloc(szBuf, sizeof(char*));             // initialize output buffer
    unsigned char cEsc = 0x1b;                                      // escape character
    long long outlength = RLEcompress(buf, szBuf, outbuf, szBuf);   // compress the buffer
    
    //Display the compressed message
	printf("Compressed message of length %llu", outlength);

}



// Different options for bitwise
char compress(void* payload, char settings, char cFlag)
{
    if(settings & RLE & HUFFMAN)
    {
        printf("Both Compressions"); // Huffman is missing
    }

    else if(settings & RLE)
    {
        printf("rle");
        AudioCompressRLE((short*)payload, settings, cFlag);
    }
        // else if(settings & HUFFMAN)
        // {
        //     printf("huffman");
    
        //     //int Huff:: HuffmanCompress(_______);
        // }
 return(cFlag);
}

void encryption(void* buf, char settings)
{
	if(settings & VIGENERE & XOR)
	{
printf("Both encryptions");
	}

	else if(settings & RLE)
	{
printf("XOR");
		// run rle on buffer
	}
    else if (settings & VIGENERE)
    {
        printf("vigenere");
    }
    else if (settings & XOR)
    {
        printf("xor");
    }
    else () {
        printf("no encryption");
    }

// 	else if(settings & HUFFMAN)
// 	{

// // printf("huffman");

// // 		//int Huff:: HuffmanCompress(_______);
// // 	}

}