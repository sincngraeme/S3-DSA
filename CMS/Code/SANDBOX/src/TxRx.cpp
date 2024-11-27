/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxRx.h"


/******************************************** Transmitting *******************************************/


// function for transmitting audio
void TxAudio(short* buf, DWORD szBuf, wchar_t* comport)
{
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings
    
    // set up header
    port1.header.payloadSize = szBuf;                            

    port1.TxToPort(&port1.header, buf);             // output
}
// function for transmitting text
void TxText(char* buf, DWORD szBuf, wchar_t* comport)
{
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings

    // set up header
    port1.header.payloadSize = szBuf;

    port1.TxToPort(&port1.header, buf);             // output
}
// function for transmitting images
void TxImage()
{

}
/******************************************** Recieving *******************************************/

// function for recieving audio
int RxAudio(short** buf, DWORD* nbytes, wchar_t* comport)
{
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings 
    DWORD prevnBytes;                                   // temp variable for storing previous nummber of bytes to prevent the wrong value beign assigned.
    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k')
    {
        if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR) 
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";
            return 1;                 // recieve from port
        }
        else if(*nbytes == MAXDWORD)
        {
            *nbytes = prevnBytes;
            if(portObj.msgStatus) return 0;     // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(*nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
            return 1;
        }
        prevnBytes = *nbytes;           // store so it can be accessed after next read operation
    }
    return 1;                           // If we reached here the user terminated the loop and the transmission was incomplete
}
// function for recieving text
int RxText(char** buf, DWORD* nbytes, wchar_t* comport)
{
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings 

    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k')
    {
        if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR) 
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";
            return 1;                 // recieve from port
        }
        else if(*nbytes == MAXDWORD)
        {
            if(portObj.msgStatus) return 0;     // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(*nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
            return 1;
        }
    }
}
// function for transmitting images
void RxImage()
{

}
