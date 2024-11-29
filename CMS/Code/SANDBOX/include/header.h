#define UNICODE

#include "TxRx.h"
#include "RLE.h"
#include "RS232Comm.h"
//#include "Huffman.h"
#include <iostream>

char compress(void* buf, char cFlags);

char encrypt(void* buf, char cFlags);

char dataCorrect(void* buf, char cFlags);




