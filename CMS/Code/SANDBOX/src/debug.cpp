#include <stdio.h>
#include "debug.h"
#include "message.h"
#include "RS232Comm.h"
#include "TxRx.h"
    void Debug::debugGeneral(int select)
    {
        int debugFlag = 0;

        while(!debugFlag)
        {

            printf("Please select the function that you want to test:\n");
            printf("1. TxAudio\n2. TxText\n3. TxImage\n4. RxAudio\n5. RxText\n6. RxImage\n7. SetParameters\n");
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
                case 'b':       /*debugFlag = 1;*/      break;                  // set exit flag high
                    
                    
            }
        }
    }

        // void dTxAudio()
        // {
        //     TxAudio();
        // }

    int Debug::dTxText()
    {
        int numQuotes = fnumQuotes();									    // Number of quotes
        long int* quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
        int* quoteLengths = fquoteLength(numQuotes, quoteIndices);
        char* messageA;
        char* messageB;

        GetMessageFromFile(messageA, MAX_QUOTE_LENGTH, frandNum(0,numQuotes), numQuotes, quoteIndices, quoteLengths);

        FILE* debugLog = fopen("DebugLog.txt", "w");

        if (debugLog == NULL)
            {
                perror("Error opening file");
                return 1;
            }

        TxText(messageA, MAX_QUOTE_LENGTH, (wchar_t*)debugLog);
        fclose(debugLog);

        fopen((const char*)debugLog, "r");

            if (debugLog == NULL)
            {
                perror("Error opening file");
                return 1;
            }

        fgets(messageB, MAX_QUOTE_LENGTH, debugLog);
        fclose(debugLog);
        free(debugLog);

        

        if (strcmp(messageA, messageB) == 0)
        {
            printf("The test transmission was successful.\n");
            printf("Transmitted message: %s\n", messageB);
        }

        else
        {
            printf("The test transmission failed.\n");
        }
        
        return 0;
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