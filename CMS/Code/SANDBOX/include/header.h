#define UNICODE

#include "TxRx.h"
#include "RLE.h"
#include "RS232Comm.h"
//#include "Huffman.h"
#include <iostream>

void AudioCompress(short* buf, DWORD szBuf, char cFlags);

void TextCompress(short* buf, DWORD szBuf, char cFlags);


