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

config settings;

// Renders main menu 
void printMainMenu()
{
    system("cls"); 
    printf("--------------- Welcome To CMS ---------------\n\n");
    printf("\tSend Message\t\t(1)\n");
    printf("\tRecieve Message\t\t(2)\n");
    printf("\tSettings\t\t(3)\n");
    printf("\tExit at any time\t(CTRL + q)\n");
    printf("\n----------------------------------------------\n");
}
// Renders Send Menu
void printTxMenu()
{
    system("cls"); 
    printf("---------------- Send Message ----------------\n\n");
    printf("\tSelect Message Type:\n\n");
    printf("\tAudio\t\t(1)\n");
    printf("\tText\t\t(2)\n");
    printf("\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
// Open Transmit Menu Mode
int TxMode()
{
    int TxFlag = 0;
    queue msgQueue;

    while(!TxFlag)
    {
        printTxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
                TxAudio(&msgQueue);
                break;
            case '2':
                TxText(&msgQueue); 
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
    system("cls");
    printf("--------------- Recieve Message --------------\n\n");
    printf("\tSelect Message Type:\n\n");
    printf("\tAudio\t\t(1)\n");
    printf("\tText\t\t(2)\n");
    printf("\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
// Open Recieve Menu Mode
int RxMode()
{
    int RxFlag = 0;  
    char* tInBuf = NULL;                               // buffer used for storing recieved message - initialized to null so RxText can handle dynamic memory allocation
    short* aInBuf = NULL;		                       // buffer used for reading recorded sound from file - initialized to null so RxAudio can handle dynamic memory allocation

    while(!RxFlag)
    {
        printRxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
            {
                printf("Audio Mode:\n\n");
                
                // cout << "COM PORT: ";
                // wchar_t comport[6];                               // declare wchar_t* buffer for comport
                // wcin.getline(comport, sizeof(comport));         // wide character version of cin for getting user input
                // instantiate object
                // audio soundObj;                         // constructor initializes recording
                // BUFFERS
                if(!RxAudio())    // recieve audio from port and only play from buffer if there were no errors
                {   
                    // playback recording 
                    // printf("\nPlaying recording from buffer\n");
                    // soundObj.PlayBuffer(aInBuf, nBytes / sizeof(short));							// Play the recorded audio from the buffer. Since we have the number of bytes, we divide by sizeof(short) for number of samples

                    // soundObj.ClosePlayback();                                                   // End playback operation.
                }		
                getchar();
                break;
            }
            case '2':
                printf("Text Mode:\n\n");

                // cout << "COM PORT: ";
                // wchar_t comport[6];                                 // declare wchar_t* buffer for comport
                // wcin.getline(comport, sizeof(comport));
                
                if(!RxText())                 
                {
                    //printf("\n%s\n", tInBuf);
                }
                //free(tInBuf);
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
    printf("------------------- Settings -----------------\n\n");
    printf("\tHeader Settings:\n");
    printf("\t  Set SID\t\t\t(1)\n");
    printf("\t  Set RID\t\t\t(2)\n");
    printf("\t  Set Audio Compression Type\t(3)\n");
    printf("\t    0: None\n");
    printf("\t    1: RLE\n"); 
    printf("\t    2: HUFFMAN\n"); 
    printf("\t    3: BOTH\n");
    printf("\t  Set Text Compression Type\t(4)\n");
    printf("\t    0: None\n");
    printf("\t    1: RLE\n"); 
    printf("\t    2: HUFFMAN\n"); 
    printf("\t    3: BOTH\n");
    printf("\tComport Settings:\n");
    printf("\t  Set Bitrate\t\t\t(5)\n");
    printf("\t  Set Bit Depth\t\t\t(6)\n");
    printf("\t  Set Comport\t\t\t(7)\n");
    printf("\n\n\tBack\t\t(b)\n");
    printf("\n----------------------------------------------\n");
}
int settingsMode()
{
    int setFlag = 0;

    system("cls");
    printSettingsMenu();

    while(!setFlag)
    {

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
                cout << "SID >";
                cin >> settings.hdr.sid;
                break;
            case '2':
                cout << "RID >";
                cin >> settings.hdr.rid;
                break;
            case '3':
                cout << "Audio Compression Type >";
                cin >> settings.hdr.audioCompType;
                break;
            case '4':
                cout << "Text Compression Type >";
                cin >> settings.hdr.textCompType;
                break;
            case '5': 
                cout << "Bitrate >";
                cin >> settings.com.bitrate;
                break;
            case '6':
                cout << "Bit Depth >";
                cin >> settings.com.bitdepth;
                break;
            case '7':
                cout << "Comport >";
                wcin.sync();
                wcin.getline(settings.com.comport, sizeof(settings.com.comport));                      // wide version of cin for user input  
                break; 
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
    system("cls");
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