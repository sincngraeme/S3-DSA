/*  TxAudio.cpp
*   
*   By: Nigel Sinclair
*   Description: Header file for Data transmission
*/
#define UNICODE

#include "RS232Comm.h"

void TxAudio();
void TxText(char* buf, int szBuf, wchar_t* comport);
void TxImage();