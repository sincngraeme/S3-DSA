/* RS232Comm.h - Interface for the RS232 communications module
 * By: Michael A. Galle
 *
 */
#pragma once

#define UNICODE 		// CreateFile() defenition needs to expand to LPCWSTR is a 32-bit pointer to a constant null-terminated string of 8-bit characters

#include <Windows.h>    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RS232_NO_ERR    0
#define RS232_WRITE_ERR 1
#define RS232_READ_ERR  2
#define RS232_CREATE_ERR  4
#define RS232_INVALID_PARAMETER 8

class RS232Comm {
    public:
        int RS232CommErr = 0;                   // error flags
        /*
        *   RS232_NO_ERR = 0
        *   RS232_WRITE_ERR = 1
        *   RS232_READ_ERR = 2
        *   RS232_CREATE_ERR = 4
        *   RS232_INVALID_PARAMETER = 8
        */

        RS232Comm(wchar_t* portName, int baudRate, int numBits);   // Constructor of RS232Comm
        ~RS232Comm();                                   // Destructor of RS232Comm
        // Tx/Rx functions are overloaded to handle multiple types
        void TxToPort(char* buf, DWORD szBuf);                      // Text
        void TxToPort(short* buf, DWORD szBuf);                     // Audio
        //void TxToPort(char* buf, DWORD szBuf);                    // Image
        DWORD RxFromPort(char* buf, DWORD szBuf);                    // Text
        DWORD RxFromPort(short* buf, DWORD szBuf);                   // Audio
        //void RxFromPort(LPVOID buf, DWORD szBuf);                 // Image

    private:

        // arguments to port functions
        HANDLE hCom;                    // cannot be set with constructor
        wchar_t* COMPORT;
        int nComRate;
        int nComBits;
        COMMTIMEOUTS timeout;           // cannot be set with constructor

        // Prototype the functions to be used
        void initPort(HANDLE* hCom, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS timeout);        // initialize port settings
        void purgePort(HANDLE* hCom);                                                                           // clear buffers of given port
        void outputToPort(HANDLE* hCom, LPCVOID buf, DWORD szBuf);                                              // writes from LPVOID buf to port (HANDLE* hcom)
        DWORD inputFromPort(HANDLE* hCom, LPVOID buf, DWORD szBuf);                                             // reads from port (HANDLE* hCom) to LPVOID buf
        // Sub functions
        int createPortFile(HANDLE* hCom, wchar_t* COMPORT);                                                       // creates device file for interacting with comport
        int SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout);                 // wrapper for setting DCB and timeout settings for the given port
        //                                 ^ user can only set the BAUD rate and the number of bits
};