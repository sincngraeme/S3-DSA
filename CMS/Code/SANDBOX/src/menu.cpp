/*
*   Menu.cpp
*   By: Nigel Sinclair, Rita Yevtushenko, Fergus Page
*   Desription: Menu implementation that contains function definitions for rendering menus
*/

#include "menu.h"
#include "TxRx.h"
#include "sound.h"
#include "debug.h"

/************** Function for printing main menu *************/

// Renders main menu 
void printMainMenu()
{
    printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
    printf("--------------- Welcome To CMS ---------------\n\n");
    printf("\tSend Message\t\t(1)\n");
    printf("\tRecieve Message\t\t(2)\n");
    printf("\tSettings\t\t(3)\n");
    printf("\tDebug\t\t(4)\n");
    printf("\tExit at any time\t(CTRL + q)\n");
    printf("\n----------------------------------------------\n");
}
// Renders Send Menu
void printTxMenu()
{
    printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
    printf("---------------- Send Message ----------------\n\n");
    printf("\tSelect Message Type:\n\n");
    printf("\tAudio\t\t(1)\n");
    printf("\tText\t\t(2)\n");
    printf("\tImage\t\t(3)\n");
    printf("\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
// Open Transmit Menu Mode
int TxMode()
{
    int TxFlag = 0;
    char message[256];
    // // BUFFERS
    // extern short* iBigBuf;
    // extern long  lBigBufSize;	// total number of samples
    
    while(!TxFlag)
    {
        printTxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
            {
                soundbuf recording = record();													////End playback operation.
                cin.ignore();
                cout << "send? (y|n): ";
                if (getchar() == 'y')
                {
                    wcin.ignore();
                    cout << "COM PORT: ";
                    wchar_t comport[6];                                         // declare wchar_t* buffer for comport
                    wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input
                    TxAudio(recording.outBuf, recording.outBufSize * sizeof(short), comport);
                    system("pause");
                }
                break;
            }
            case '2':
                printf("Text Mode:\n\nMessage: ");
                cin.getline(message, sizeof(message));
                cout << "\nCOM PORT: ";
                wchar_t comport[6];                                         // declare wchar_t* buffer for comport
                //wcin.ignore();
                wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input
                TxText(message, strlen(message) + 1, comport);
                /*TEMP*/getchar();
                break;
            case '3':
                /*TEMP*/printf("Image Mode:\n");
                /*TEMP*/getchar();
                break;
            case 'b':
                TxFlag = 1;                     // set exit flag high
                break;
            case CTRL_KEY('q'): return 1;       // to break out of main program loop
        }
    }
    return 0;
}
// Renders recieve Menu
void printRxMenu()
{
    printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
    printf("--------------- Recieve Message --------------\n\n");
    printf("\tSelect Message Type:\n\n");
    printf("\tAudio\t\t(1)\n");
    printf("\tText\t\t(2)\n");
    printf("\tImage\t\t(3)\n");
    printf("\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
// Open Recieve Menu Mode
int RxMode()
{
    int RxFlag = 0;  
    char* tInBuf = NULL;                               // buffer used for storing recieved message - initialized to null so RxText can handle dynamic memory allocation
    short* aInBuf = NULL;		                       // buffer used for reading recorded sound from file - initialized to null so RxAudio can handle dynamic memory allocation
    long nBytes = 0;  

    while(!RxFlag)
    {
        printRxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
            {
                printf("Audio Mode:\n\n");
                
                cout << "COM PORT: ";
                wchar_t comport[6];                               // declare wchar_t* buffer for comport
                wcin.getline(comport, sizeof(comport));         // wide character version of cin for getting user input
                // instantiate object
                audio soundObj;                         // constructor initializes recording
                // BUFFERS
                if(!RxAudio(&aInBuf, &nBytes, comport))    // recieve audio from port and only play from buffer if there were no errors
                {   
                    // playback recording 
                    printf("\nPlaying recording from buffer\n");
                    soundObj.PlayBuffer(aInBuf, nBytes / sizeof(short));							// Play the recorded audio from the buffer. Since we have the number of bytes, we divide by sizeof(short) for number of samples

                    soundObj.ClosePlayback();                                                   // End playback operation.
                }		
                free(aInBuf);									            
                getchar();
                break;
            }
            case '2':
                /*TEMP*/printf("Text Mode:\n\n");

                cout << "COM PORT: ";
                wchar_t comport[6];                                 // declare wchar_t* buffer for comport
                wcin.getline(comport, sizeof(comport));
                
                if(!RxText(&tInBuf, &nBytes , comport))                 
                {
                    printf("\n%s\n", tInBuf);
                }
                free(tInBuf);
                getchar();
                break;
            case '3':
                /*TEMP*/printf("Image Mode:\n");
                /*TEMP*/getchar();
                break;
            case 'b':
                RxFlag = 1;                     // set exit flag high
                break;
            case CTRL_KEY('q'): return 1;       // to break out of main program loop    
        }
    }
    return 0;
}
// Renders Settings Menu
void printSettingsMenu()
{
    printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
    printf("------------------- Settings -----------------\n\n");
    printf("\tSet Bitrate\t\t(1)\n");
    // printf("\tText\t\t(2)\n");
    // printf("\tImage\t\t(3)\n");
    printf("\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
int settingsMode()
{
    int setFlag = 0;

    while(!setFlag)
    {
        printSettingsMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
                /*TEMP*/printf("Set Bitrate:");
                /*TEMP*/getchar();
                break;
            // case '2':
            //     /*TEMP*/printf("\n");
            //     /*TEMP*/getchar();
            //     break;
            // case '3':
            //     /*TEMP*/printf("\n");
            //     /*TEMP*/getchar();
            //     break;
            case 'b':
                setFlag = 1;                    // set exit flag high
                break;
            case CTRL_KEY('q'): return 1;       // to break out of main program loop
        }
    }
    return 0;
}
// Renders Debug Menu
void printDebugMenu()
{
    printf("%s%s", clearfrom, setH);        // clears screen then resets to home position
    // list all fn
    printf("Enter function name and arguments to test:\n");
}

int debugMode()
{
    //char arguments[DB_ARG_MAX_SZ];                          // function number (none specified by default)
    printDebugMenu();
    //fgets(arguments, DB_ARG_MAX_SZ, stdin);         // store argument list
    // parse string
    // lookup from fn list
    // pass arguments and run fn
    /*TEMP*/getchar();
    return 0;
}
// Renders quit menu
void printQuitMenu()
{
    printf("%s%sQuitting Program ...", clearfrom, setH);    // clear screen and print exit msg
}