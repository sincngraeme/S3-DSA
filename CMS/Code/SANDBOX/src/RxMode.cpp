/*  RxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data reception
*/
#define UNICODE

#include "RxMode.h"
#include "RS232Comm.h"
#include <iostream>

using namespace std;

// function for transmitting audio
void RxAudio(short* buf, long szBuf)
{
    wchar_t comport[6];                               // declare wchar_t* buffer for comport
    wcin.getline(comport, sizeof(comport));         // wide character version of cin for getting user input
    RS232Comm port1(comport, 9600, 8);              // instantiate port object and initialize port settings

    port1.RxFromPort(buf, szBuf);                   // recieve from port
}
// function for transmitting text
void RxText(char* buf, int szBuf)
{
    wchar_t comport[6];                               // declare wchar_t* buffer for comport
    wcin.getline(comport, sizeof(comport));
    RS232Comm port1(comport, 9600, 8);              // instantiate port object and initialize port settings

    port1.RxFromPort(buf, szBuf);                   // recieve from port
}
// function for transmitting images
void RxImage()
{

}
