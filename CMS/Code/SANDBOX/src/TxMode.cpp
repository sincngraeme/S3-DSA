/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxMode.h"
#include "RS232Comm.h"
#include <iostream>

using namespace std;

// function for transmitting audio
void TxAudio(short* buf, long szBuf)
{
    wchar_t* comport = NULL;                       // declare wchar_t* buffer for comport
    wcin >> comport;                        // wide version of cin for user input

    RS232Comm port1(comport, 9600, 8);      // Instantiate port object and initialize settings

    port1.TxToPort(buf, szBuf);             // output
}
// function for transmitting text
void TxText(char* buf, int szBuf)
{
    wchar_t* comport = NULL;                       // declare wchar_t* buffer for comport
    wcin >> comport;                        // wide version of cin for user input

    RS232Comm port1(comport, 9600, 8);      // Instantiate port object and initialize settings

    port1.TxToPort(buf, szBuf);             // output
}
// function for transmitting images
void TxImage()
{

}
