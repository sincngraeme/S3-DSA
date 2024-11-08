/*  TxAudio.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxMode.h"
#include "RS232Comm.h"

// function for transmitting audio
void TxAudio()
{

}
// function for transmitting text
void TxText(char* buf, int szBuf)
{
    RS232Comm port1(L"COM5",9600,8);

    port1.TxToPort(buf, szBuf);
}
// function for transmitting images
void TxImage()
{

}
