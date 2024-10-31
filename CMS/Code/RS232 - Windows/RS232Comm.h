/* RS232Comm.h - Interface for the RS232 communications module
 * By: Michael A. Galle
 *
 */
#pragma once

// Prototype the functions to be used
void initPort(HANDLE* hCom, LPCSTR COMPORT, int nComRate, int nComBits, COMMTIMEOUTS timeout);        // initialize port settings
void purgePort(HANDLE* hCom);                                                                           // clear buffers of given port
void outputToPort(HANDLE* hCom, LPCVOID buf, DWORD szBuf);                                              // writes from LPVOID buf to port (HANDLE* hcom)
DWORD inputFromPort(HANDLE* hCom, LPVOID buf, DWORD szBuf);                                             // reads from port (HANDLE* hCom) to LPVOID buf

// Sub functions
void createPortFile(HANDLE* hCom, LPCSTR COMPORT);                                                       // creates device file for interacting with comport
static int SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout);                 // wrapper for setting DCB and timeout settings for the given port
//                                 ^ user can only set the BAUD rate and the number of bits