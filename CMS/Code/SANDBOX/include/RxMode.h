/*  RxMode.h
*   
*   By: Nigel Sinclair
*   Description: Header file for Data Reception
*/
#define UNICODE

#include "RS232Comm.h"
#include <string.h>

int RxAudio(short* buf, long szBuf);
int RxText(char* buf, int szBuf);
void RxImage();