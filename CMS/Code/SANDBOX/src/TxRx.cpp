/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxRx.h"


/******************************************** Transmitting *******************************************/


// function for transmitting audio
void TxAudio(short* buf, long szBuf, wchar_t* comport)
{
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings
    
    // set up header
    port1.header.payloadSize = szBuf;                            

    port1.TxToPort(&port1.header, buf);             // output
}
// function for transmitting text
void TxText(char* buf, int szBuf, wchar_t* comport)
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

    if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR) // recieve from port - if zero bytes are read, return 1 to indicate error and print flags
    {
        cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";
        //printf("ERROR reading from port: 0x%x, %ld bytes read.\n", portObj.RS232CommErr, *nbytes);
        return 1;                     
    } 
    else if(*nbytes != portObj.header.payloadSize)
    {
        cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
        return 1;
    }
    return 0;                                                           // otherwise return 0 to indicate success 
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
