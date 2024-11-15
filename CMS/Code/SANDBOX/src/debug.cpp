#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "debug.h"
#include "message.h"
#include "RS232Comm.h"
#include "TxMode.h"
#include "RxMode.h" 

#define CTRL_KEY(k) ((k) & 0x1f)		// allows for processing ctrl inputs

void Debug::debugGeneral()
{   
    int debugFlag = 0;

    while(!debugFlag)
    {
        printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
        printf("-------------------- Debug ------------------\n\n");
        printf("Please select the function that you want to test:\n\n");
        printf("\tTxAudio\t\t(1)\n");
        printf("\tTxText\t\t(2)\n");
        printf("\tTxImage\t\t(3)\n");
        printf("\tRxAudio\t\t(4)\n");
        printf("\tRxText\t\t(5)\n");
        printf("\tRxImage\t\t(6)\n");
        printf("\tSetParameters\t(7)\n");
        printf("\n\tBack\t\t(b)\n");
        printf("\n----------------------------------------------\n");

        while(!kbhit());                                                // Wait for keypress
        switch(getch())                                                 // load keypress and select fn
        {
            case '1':       /*dTxAudio();*/         break;
            case '2':       dTxText();          break;                  
            case '3':       /*dTxImage();*/         break;
            case '4':       /*dRxAudio();*/         break;
            case '5':       /*dRxText();*/          break;
            case '6':       /*dRxImage();*/         break;
            case '7':       /*dSetParameters();*/   break;
            case 'b':       return;                  // set exit flag high
        }
    }

    return;
}

    // void dTxAudio()
    // {
    //     TxAudio();
    // }

void Debug::dTxText()
{    
    srand(time(NULL));
    printf("Testing text transmission.\n\n");              
    char* timestamp;                                                    //variable to handle timestamp read back from debugLog.
    int numQuotes = fnumQuotes();									    //number of quotes in FortuneCookies.txt (Quotes file).
    long int* quoteIndices = fquoteIndices(numQuotes);					//index locations of the quotes.
    int* quoteLengths = fquoteLength(numQuotes, quoteIndices);          //gets the lengths of all the quotes in the file.
    char messageA[MAX_QUOTE_LENGTH];                                    //buffer to hold outgoing transmit message.
    char messageB[MAX_QUOTE_LENGTH];                                    //buffer to hold message read back from file.
  
    printf("print1\n");

    GetMessageFromFile(messageA, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);   //get a test message from the Quotes file.
    printf("%s\n", messageA);

    printf("print2\n");

    wchar_t* debugPort = L"DebugLog.txt";

    // Call the CreateFile() function to create comport file (hardware is accessed through files) 
    HANDLE hCom = CreateFileW(
        (LPCWSTR)debugPort,							// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
        GENERIC_READ | GENERIC_WRITE,				// Open for read and write
        NULL,                           			// No sharing allowed
        NULL,										// No security
        CREATE_ALWAYS,								// Opens the existing com port
        FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
        NULL										// No template
    );
	
    printf("print3\n");

    printf("hCom == %d\n", hCom);

	if (hCom == INVALID_HANDLE_VALUE)
    {
		printf("\nFatal Error 0x%lx: Unable to open\n", GetLastError());
	}

	else
    {
		printf("\nCOM is now open\n");
	}

    printf("print4\n");

    RS232Comm debug(debugPort, 9600, 8);

     printf("print5\n");

	// Call the CreateFile() function to create DebugLog.txt file (hardware is accessed through files)   

    time_t timeNow = time(NULL);                                        //get current number of seconds since January 1, 1970.
    struct tm *dateTime = localtime(&timeNow);                          //parses timeNow into clock and calendar units (hours, seconds, days, etc.).
    TxText(asctime(dateTime), 26, debugPort);                  //converts dateTime into a 26 character string to make it readable. Transmit stamp to debugLog file.
    TxText(messageA, MAX_QUOTE_LENGTH, debugPort);             //transmit messageA to debugLog file.
   
    FILE* debugLog = fopen("DebugLog.txt", "r");                              //open debugLog in read mode.

    if (debugLog == NULL)                                           //error checking.
    {
        perror("Error opening file\n");
        return;
    }

    fgets(timestamp, 26, debugLog);                                     //retrieve the timestamp from debugLog.
    fgets(messageB, MAX_QUOTE_LENGTH, debugLog);                        //retrieve the message from debugLog.
    fclose(debugLog);                                                   //close debugLog.
    free(debugLog);                                                     //free the file pointer.
    printf("Timestamp: %s\n", timestamp);                               //print the timestamp.

    if (strcmp(messageA, messageB) == 0)                                //compare the string sent to the file to the one retrieved from the file to see if they match.
    {
        printf("The test transmission was successful.\n");              //confirm match.
        printf("Transmitted message: %s\n", messageB);                  //print retrieved string.

        return;
    }

    else
    {
        printf("The test transmission failed.\n");                      //deny match.

        return;
    }
    CloseHandle(hCom);
}   

    // int Debug::dTxImage()
    // {
    //     //TxImage();
    // }

    // int Debug::dRxAudio()
    // {
    //     //RxAudio();
    // }

    // int Debug::dRxText()
    // {
    //     //RxText();
    // }

    // int Debug::dRxImage()
    // {
    //     //RxImage();
    // }

    // int Debug::dSetParameters()
    // {
    //     //SetParameters();
    // }