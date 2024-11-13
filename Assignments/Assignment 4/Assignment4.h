
#include <stdio.h>
#include <string.h>
#pragma once

// Function for compression and decompression
long long RLEcompress(unsigned char* in, long long iInLen, unsigned char* out, long long iOutMax);

long long RLEdecompress(unsigned char* in, long long iInLen, unsigned char* out, long long iOutMax, unsigned char cEsc);
