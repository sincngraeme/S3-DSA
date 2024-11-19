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
    cout << "COM PORT: ";
    wchar_t comport[6];                                         // declare wchar_t* buffer for comport
    wcin.ignore();
    wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings

    port1.TxToPort(buf, szBuf);             // output
}
// function for transmitting text
void TxText(char* buf, int szBuf)
{
    cout << "\nCOM PORT: ";
    wchar_t comport[6];                                         // declare wchar_t* buffer for comport
    //wcin.ignore();
    wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings

    port1.TxToPort(buf, szBuf);             // output
}
// function for transmitting images
void TxImage()
{

}
