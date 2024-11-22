/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxRx.h"
#include "menu.h"

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
    port1.TxToPort(&port1.header, buf);             // output
    port1.TxToPort(&port1.header, buf);             // output
    port1.header.payloadSize = MAXDWORD;
    port1.TxToPort(&port1.header, (char*)NULL);             // output


}
// function for transmitting images
void TxImage()
{

}
/******************************************** Recieving *******************************************/

// function for recieving audio
int RxAudio(short** buf, long* nbytes, wchar_t* comport)
{
    int timeout;

    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings

    while(timeout > 10)         // user can kill process with ctrl + k, otherwise terminates if there are zero bytes read for 10 loops
    {
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
        else if(*nbytes == MAXDWORD)        // if the header was not recived we are just waiting for the payload so increase the manual timeout
        {
            timeout++;
        }
        if(portObj.header.payloadSize == MAXDWORD) return 0;     // if this is the footer we have reached the end of the message
    }
    return 0;                                     // otherwise return 0 to indicate success 
}
// function for recieving text
int RxText(char** buf, long* nbytes, wchar_t* comport)
{
    int timeout;

    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings

    while(!kbhit() && timeout > 10)         // user can kill process with therwise terminates if there are zero bytes read for 10 loops
    {
        if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR) // recieve from port - if zero bytes are read, return 1 to indicate error and print flags
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";
            cout << *buf;
            //printf("ERROR reading from port: 0x%x, %ld bytes read.\n", portObj.RS232CommErr, *nbytes);
            return 1;                     
        }
        else if(*nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
            cout << *buf;
            return 1;
        }
        else if(*nbytes == MAXDWORD)        // if the header was not recived we are just waiting for the payload so increase the manual timeout
        {
            cout << *buf;
            timeout++;
        }
        if(portObj.header.payloadSize == MAXDWORD) return 0;     // if this is the footer we have reached the end of the message
        cout << *buf;
    }
    return 0;                                     // otherwise return 0 to indicate success 
}
// function for transmitting images
void RxImage()
{

}
