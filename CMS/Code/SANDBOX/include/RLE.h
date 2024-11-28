
#include <stdio.h>
#include <string.h>
#pragma once

// Function for compression and decompression
long long RLEcompress(void* in, long long iInLen, void* out, long long iOutMax);

long long RLEdecompress(void* in, long long iInLen, void* out, long long iOutMax, unsigned char cEsc);
