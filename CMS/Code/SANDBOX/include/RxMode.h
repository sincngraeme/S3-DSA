/*  RxMode.h
*   
*   By: Nigel Sinclair
*   Description: Header file for Data Reception
*/
#define UNICODE

#include "RS232Comm.h"

void RxAudio();
void RxText(char* buf, int szBuf);
void RxImage();