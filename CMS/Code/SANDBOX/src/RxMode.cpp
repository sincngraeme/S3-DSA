/*  RxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "RxMode.h"
#include "RS232Comm.h"

// function for transmitting audio
void RxAudio(short* buf, long szBuf)
{
    wchar_t* comport = L"COM6";

    RS232Comm port1(comport, 9600, 8);

    port1.RxFromPort(buf, szBuf);
}
// function for transmitting text
void RxText(char* buf, int szBuf)
{
    wchar_t* comport = L"COM6";

    RS232Comm port1(comport, 9600, 8);

    port1.RxFromPort(buf, szBuf);
}
// function for transmitting images
void RxImage()
{

}
