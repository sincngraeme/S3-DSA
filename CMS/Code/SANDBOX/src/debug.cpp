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
    RS232Flags::dFlag = 1;     // set the debug flag high
    int debugFlag = 0;

    while(!debugFlag)
    {
        printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
        printf("-------------------- Debug ------------------\n\n");
        printf("Please select the function you want to test:\n\n");
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
    char* timestamp[26];                                                //variable to handle timestamp read back from debugLog.
    
    int numQuotes = fnumQuotes();									    //number of quotes in FortuneCookies.txt (Quotes file).
    long int* quoteIndices = fquoteIndices(numQuotes);					//index locations of the quotes.
    int* quoteLengths = fquoteLength(numQuotes, quoteIndices);          //gets the lengths of all the quotes in the file.
    char messageIn[MAX_QUOTE_LENGTH];                                   //buffer to hold outgoing transmit message.
    char messageOut[strlen(messageIn) +26];                             //buffer to hold timestamped message read back from file.
    char messageTx[strlen(messageOut)];

    GetMessageFromFile(messageIn, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);   //get a test message from the Quotes file.

    wchar_t* debugPort = L"DebugLog.txt";

    time_t timeNow = time(NULL);                                        //get current number of seconds since January 1, 1970.
    struct tm *dateTime = localtime(&timeNow);                          //parses timeNow into clock and calendar units (hours, seconds, days, etc.).
    *timestamp = asctime(dateTime);                                      //Write timestamp as a 26 char string.

    memcpy(messageTx, *timestamp, 26);
    strcat(messageTx, "\n");
    strcat(messageTx, messageIn);

    TxText(messageTx, 26 + strlen(messageIn), debugPort);  
    CloseHandle(debugPort); 

    // FILE* fp = fopen((const char*)debugPort, "r"); 

    // if (fp == NULL)                            // error checking
    // {
    //     perror("ERROR opening file");
    //     return;
    // }

    // fgets(messageOut, sizeof(messageOut), fp);

    // fclose(fp);
    // free(fp);             

    // if (strcmp(messageIn, messageOut) == 0)                                //compare the string sent to the file to the one retrieved from the file to see if they match.
    // {
    //     printf("The test transmission was successful.\n");              //confirm match.
    //     printf("Transmitted message: %s\n", messageOut);                  //print retrieved string.

    //     return;
    // }

    // else
    // {
    //     printf("The test transmission failed.\n");                      //deny match.

    //     return;
    // }
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