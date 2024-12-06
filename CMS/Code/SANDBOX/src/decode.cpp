/*
*   Decode.cpp
*   
*   By: Nigel Sinclair
*   Description:    implementation for wrapper functions for data operations:
*                       - Decodes header and performes the following opperations based on flags
*                           * Compression
*                           * Encryption
*                           * Error Detection
*/

#include "decode.h"


// Checking for compression on transmitting side and compressing if specified
int compress(void* buf, DWORD inSz, DWORD* outSz, int fCompress)
{
    unsigned char* out;
    Huff huff;                          // instantiate huffman object

    if(fCompress == 0) return 0;                // No compression
    else if(fCompress == 2)                     // flag for Huffman                          this is a message that is hopefully long enough to be compressed c
    {
        // Calculate worst-case buffer size for output
        *outSz = inSz * (104 + 50) / (100 + 384);
        out = (unsigned char*)calloc(*outSz, sizeof(unsigned char*));

        if (!out)
        {
            printf("Not enough memory\n");
            return 0;
        }

        // Compress
        *outSz = huff.Huffman_Compress((unsigned char*)buf, out, inSz);
        // if compression would result in larger message
        if(*outSz > inSz) 
        {
            printf("Message cannot be further compressed\n"); 
            return 0;
        }
        // Output file statistics message                    
        printf("\nOutput: %d bytes (%.1f%%)\n", *outSz, 100.0f * (float)*outSz / (float)inSz);

        memcpy(buf, out, *outSz);            // copy the compressed message in               
        free(out);

        return 1; 
    }
}
// Decompressing on recieving side if specified in header
int decompress(void* buf, DWORD inSz, DWORD outSz, int fCompress)
{
   // Allocate memory for output (example size, adjust as needed)
    unsigned char* out;
    Huff huff;                          // instantiate huffman object               
    
    if(fCompress == 0) return 0;                // No compression
    else if(fCompress == 2)                     // flag for Huffman                 
    {

        out = (unsigned char*)calloc(outSz, sizeof(unsigned char*));
        // out = (unsigned char*)malloc(outSz);

        cout << "Uncompressed size is: " << outSz << endl;

        if (!out)
        {
            printf("Not enough memory\n");
            return 0;
        }

        // Decompress
        huff.Huffman_Uncompress((unsigned char*)buf, out, (unsigned int)inSz, (unsigned int)outSz);
        printf("Decompression complete.\n");

        memcpy(buf, out, outSz);
        free(out);
        return 1;
    }
}