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

class RS232Comm {
    public:

        RS232Comm(wchar_t* portName, int baudRate, int numBits);   // Constructor of RS232Comm
        ~RS232Comm();                                   // Destructor of RS232Comm
        void hello();
        void hello2();
        // Tx/Rx functions are overloaded to handle multiple types
        void TxToPort(char* buf, DWORD szBuf);                      // Text
        void TxToPort(short* buf, DWORD szBuf);                     // Audio
        //void TxToPort(char* buf, DWORD szBuf);                    // Image
        void RxFromPort(char* buf, DWORD szBuf);                    // Text
        void RxFromPort(short* buf, DWORD szBuf);                   // Audio
        //void RxFromPort(LPVOID buf, DWORD szBuf);                 // Image

    private:

        // arguments to port functions
        HANDLE hCom;                    // cannot be set with cunstructor
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
        void createPortFile(HANDLE* hCom, wchar_t* COMPORT);                                                       // creates device file for interacting with comport
        int SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout);                 // wrapper for setting DCB and timeout settings for the given port
        //                                 ^ user can only set the BAUD rate and the number of bits
};