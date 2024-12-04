/* RS232Comm.cpp - Implementation for the RS232 communications module
 * 	By: Michael A. Galle
 *	Adapted By: Nigel Sinclair, Fergus Page
 */

#pragma once

#define UNICODE 		// CreateFile() defenition needs to expand to LPCWSTR is a 32-bit pointer to a constant null-terminated string of 8-bit characters

#include <Windows.h>    // Includes the functions for serial communication via RS232
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232Comm.h"

#define EX_FATAL 1

/**************************************************** WRAPPERS *********************************************/

// Constructor
RS232Comm::RS232Comm(wchar_t* portName, int baudRate, int numBits)
{
	// set members
	COMPORT = portName;
	nComRate = baudRate;
	nComBits = numBits;

	initPort(&hCom, COMPORT, nComRate, nComBits, timeout);			// if initPort fails set the objects error flag to initPorts error Value
}
// Destructor
RS232Comm::~RS232Comm()
{
	purgePort(&hCom);
	CloseHandle(hCom);
}
// Transmit
void RS232Comm::TxToPort(pcomhdr header, char* buf)	// text
{
	outputToPort(&hCom, (LPCVOID)header, sizeof(comhdr));					// send header
	outputToPort(&hCom, (LPCVOID)buf, header->payloadSize);					// send text
}
void RS232Comm::TxToPort(pcomhdr header, short* buf) // Audio
{
	outputToPort(&hCom, (LPCVOID)header, sizeof(comhdr));					// send header	
	outputToPort(&hCom, (LPCVOID)buf, header->payloadSize);					// send Audio
}
// Recieve
DWORD RS232Comm::RxFromPort(pcomhdr header, char** buf)
{
	if(!inputFromPort(&hCom, (LPVOID)header, sizeof(comhdr))) return MAXDWORD;

	*buf = (char*)malloc(header->payloadSize);					// allocate space according to payload size in buffer
	if(*buf == NULL)		// malloc failed
	{
		printf("ERROR recieving from port: not enough space\n");
		return 0;
	}
	msgStatus = 1;		// message has been recieved
	return inputFromPort(&hCom, (LPVOID)(*buf), header->payloadSize);			// return number of bytes read from inputFromPort unless memory could not be allocated			
}
DWORD RS232Comm::RxFromPort(pcomhdr header, short** buf)
{
	if(!inputFromPort(&hCom, (LPVOID)header, sizeof(comhdr))) return MAXDWORD;

	*buf = (short*)malloc(header->payloadSize);					// allocate space according to payload size in buffer
	if(*buf == NULL)		// malloc failed
	{
		printf("ERROR recieving from port: not enough space\n");
		return 0;
	}
	msgStatus = 1;		// message has been recieved
	return inputFromPort(&hCom, (LPVOID)(*buf), header->payloadSize);			// return number of bytes read from inputFromPort unless memory could not be allocated			

}
/**************************************************************** PRIVATE ***************************************************************/

// Initializes the port and sets the communication parameters
void RS232Comm::initPort(HANDLE* hCom, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS timeout) 
{
	RS232CommErr |= createPortFile(hCom, COMPORT);						// Initializes hCom to point to PORT# and sets error flags
	purgePort(hCom);												// Purges the COM port
	RS232CommErr |= SetComParms(hCom, nComRate, nComBits, timeout);		// Uses the DCB structure to set up the COM port
	purgePort(hCom);
}

// Purge any outstanding requests on the serial port (initialize)
void RS232Comm::purgePort(HANDLE* hCom) 
{
	PurgeComm(*hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);		// perormes logical or with Macros from Windows.h in order tom set bits
}

// Output/Input messages to/from ports - template function to accept any datatype  
void RS232Comm::outputToPort(HANDLE* hCom, LPCVOID buf, DWORD szBuf)
{
	int i = 0;
	DWORD NumberofBytesTransmitted;
	LPDWORD lpErrors=0;
	LPCOMSTAT lpStat=0; 

	i = WriteFile(
		*hCom,										// Write handle pointing to COM port
		buf,										// Buffer size
		szBuf,										// Size of buffer
		&NumberofBytesTransmitted,					// Written number of bytes
		NULL										// unused
	);
	// Handle the timeout error (no device detected)
	if (i == 0) {
		printf("\nWrite Error: 0x%lx\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.	
		RS232CommErr |= RS232_WRITE_ERR; 			// set write error flag high
	} else {
		printf("\nSuccessful transmission, there were %ld bytes transmitted\n", NumberofBytesTransmitted);
	}
}

// input function template for recieving data of any type
DWORD RS232Comm::inputFromPort(HANDLE* hCom, LPVOID buf, DWORD szBuf) 
{
	int i = 0;
	DWORD NumberofBytesRead;						// stores the number of bytes read from the port
	LPDWORD lpErrors = 0;							// ptr to variable to recieve error mask
	LPCOMSTAT lpStat = 0;							// ptr to a COMSTAT struct where device status information is returned. If  NULL, no return.

	i = ReadFile(
		*hCom,										// Read handle pointing to COM port
		buf,										// Buffer size
		szBuf,  									// Size of buffer - Maximum number of bytes to read
		&NumberofBytesRead,
		NULL
	);
	// Handle the timeout error
	if (i == 0) {
		printf("\nRead Error: 0x%lx\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.
		RS232CommErr |= RS232_READ_ERR;			// set error flags high
	}
	else if (NumberofBytesRead == 0)
	{
		printf("\nReception Failed, There were %ld bytes read\n", NumberofBytesRead);
	} else {
		printf("\nSuccessful reception!, There were %ld bytes read\n", NumberofBytesRead);
	}

	return(NumberofBytesRead);
}

// Sub functions called by above functions
/**************************************************************************************/
// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
int RS232Comm::createPortFile(HANDLE* hCom, wchar_t* COMPORT) 	// Changed from Wchar_t* (LPCSTR is a 32-bit pointer to a constant null-terminated string of 8-bit characters)
{
	// Call the CreateFile() function to create comport file (hardware is accessed through files) 
	*hCom = CreateFile(
		COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
		GENERIC_READ | GENERIC_WRITE,				// Open for read and write
		NULL,										// No sharing allowed
		NULL,										// No security
		OPEN_EXISTING,								// Opens the existing com port
		FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
		NULL										// No template
	);
	
	if (*hCom == INVALID_HANDLE_VALUE) {
		printf("\nFatal Error 0x%lx: Unable to open\n", GetLastError());
		return RS232_CREATE_ERR;
	}
	else {
		printf("\nCOM is now open\n");
		return RS232_NO_ERR;
	}
}

int RS232Comm::SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout) 
{
	DCB dcb;										// Windows device control block (struct that defines ctrl settings for serial coms device)
	// Clear DCB to start out clean, then get current settings
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(*hCom, &dcb))
		return(RS232_INVALID_PARAMETER);

	// Set our own parameters from Globals
	dcb.BaudRate = nComRate;						// Baud (bit) rate
	dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
	dcb.Parity = 0;									// No parity	
	dcb.StopBits = ONESTOPBIT;						// One stop bit
	if (!SetCommState(*hCom, &dcb))
		return(RS232_INVALID_PARAMETER);

	// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
	memset((void *)&timeout, 0, sizeof(timeout));
	timeout.ReadIntervalTimeout = 50; 
	//500;					// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
	timeout.ReadTotalTimeoutMultiplier = 1; 
	//1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
	timeout.ReadTotalTimeoutConstant = 0; 
	// timeout.WriteTotalTimeoutMultiplier = 0;
	// timeout.WriteTotalTimeoutConstant = 0;
	//5000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
	SetCommTimeouts(*hCom, &timeout);
	return RS232_NO_ERR;
}

 