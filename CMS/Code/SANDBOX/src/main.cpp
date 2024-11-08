/*
*   Main.cpp
*   By: Nigel Sinclair, Rita Yevtushenko, Fergus Page
*   Desription: Menu Main file that tests all menu functions
*/

#include "menu.h"
#include "windows.h"

int main()
{
    int flag = 0;   // gets set low to exit program 
    int ret = 0;
    int c;

    Sleep(500);

    while(!flag)    // main program loop
    {
        printMainMenu();

        while(!kbhit());    // Wait for Keypress
        c = getch();        // load keypress 
        switch(c)           // pick function
        {
            case '1':         // Send Menu
                ret = TxMode();
                break;
            case '2':         // Recieve Menu
                ret = RxMode();
                break;
            case '3':         // Settings Menu
                ret = settingsMode();
                break;
            case CTRL_KEY('d'):             // Hidden Debug Menu
                ret = debugMode();
                break;
            case CTRL_KEY('q'):             // Asynchronous Quit
                flag = 1;                   // set exit flag high
                break;
        }
        flag = (ret == 2) ? 1: flag;        // if the quit flag is set by a sub menu, set flag high. else do not change
        c = 0;                              // ensure that we are not filling with garbage
    }

}