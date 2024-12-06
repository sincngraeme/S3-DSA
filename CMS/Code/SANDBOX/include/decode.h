/*
*   Decode.h
*   
*   By: Nigel Sinclair
*   Description:    header for wrapper functions for data operations:
*                       - Decodes header and performes the following opperations based on flags
*                           * Compression
*                           * Encryption
*                           * Error Detection
*/

#include <windows.h>
#include "Huffman.h"
#include <iostream>

using namespace std;

int compress(void* buf, DWORD inSz, DWORD* outSz, int fCompress);            // takes in buffer to be compressed, the buffers uncompressed size, and the compression flag
int decompress(void* buf, DWORD inSz, DWORD outSz, int fCompress);