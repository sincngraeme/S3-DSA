/*
*   Menu.cpp
*   By: Nigel Sinclair, Rita Yevtushenko, Fergus Page
*   Desription: Menu implementation that contains function definitions for rendering menus
*/

#include "menu.h"
#include "TxMode.h"
#include "RxMode.h"
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
    char message[] = "this is my message string";

    while(!TxFlag)
    {
        printTxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
                /*TEMP*/printf("Audio Mode:");
                
                /*TEMP*/getchar();
                break;
            case '2':
                /*TEMP*/printf("Text Mode:");
                TxText(message, 26, L"COM6");
                /*TEMP*/getchar();
                break;
            case '3':
                /*TEMP*/printf("Image Mode:");
                /*TEMP*/getchar();
                break;
            case 'b':
                TxFlag = 1;                     // set exit flag high
                break;
                
        }
    }
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
    char message[26];

    while(!RxFlag)
    {
        printRxMenu();

        while(!kbhit());        // Wait for keypress
        switch(getch())         // load keypress and select fn
        {
            case '1':
                /*TEMP*/printf("Audio Mode:");
                /*TEMP*/getchar();
                break;
            case '2':
                /*TEMP*/printf("Text Mode:");
                RxText(message, 26);
                printf("\n%s\n", message);
                /*TEMP*/getchar();
                break;
            case '3':
                /*TEMP*/printf("Image Mode:");
                /*TEMP*/getchar();
                break;
            case 'b':
                RxFlag = 1;                     // set exit flag high
                break;
                
        }
    }
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
                
        }
    }
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
    Debug debug;
    debug.debugGeneral();



    //char arguments[DB_ARG_MAX_SZ];                          // function number (none specified by default)
    //printDebugMenu();
    //fgets(arguments, DB_ARG_MAX_SZ, stdin);         // store argument list
    // parse string
    // lookup from fn list
    // pass arguments and run fn
    ///*TEMP*/getchar();
}
// Renders quit menu
void printQuitMenu()
{
    printf("%s%sQuitting Program ...", clearfrom, setH);    // clear screen and print exit msg
}