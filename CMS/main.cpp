/*
*   Main.cpp
*   Description: Renders user interface and calls programs
*   By: Nigel Sinclair, Rita Yevtushenko
*/

#include <stdio.h>
#include <conio.h>
#include "menu.h"

int main()
{
    int flag = 0;
    
    while (!flag)
    {
        renderMainMenu();

        while (!kbhit());

        switch (getch())
        {
            case send:                // record function
            case exit: prexit();        // exit program
        }
    }
}