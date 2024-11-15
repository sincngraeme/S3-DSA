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
int RxAudio(short* buf, long szBuf)
{
    cout << "COM PORT: ";
    wchar_t comport[6];                               // declare wchar_t* buffer for comport
    wcin.getline(comport, sizeof(comport));         // wide character version of cin for getting user input
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings

    if(portObj.RxFromPort(buf, szBuf) == 0 || portObj.RS232CommErr != RS232_NO_ERR) return 1;                     // recieve from port - if zero bytes are read, return 1 to indicate error
    
    return 0;                                                           // otherwise return 0 to indicate success 
}
// function for transmitting text
int RxText(char* buf, int szBuf)
{
    cout << "COM PORT: ";
    wchar_t comport[6];                               // declare wchar_t* buffer for comport
    wcin.getline(comport, sizeof(comport));
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings

    if(portObj.RxFromPort(buf, szBuf) == 0 || portObj.RS232CommErr != RS232_NO_ERR) return 1;                 // recieve from port
    
    return 0;
}
// function for transmitting images
void RxImage()
{

}
