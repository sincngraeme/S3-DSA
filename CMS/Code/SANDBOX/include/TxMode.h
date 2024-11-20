/*  TxAudio.cpp
*   
*   By: Nigel Sinclair
*   Description: Header file for Data transmission
*/
#define UNICODE

#include "RS232Comm.h"

void TxAudio(short* buf, long szBuf);
void TxText(char* buf, int szBuf);
void TxImage();