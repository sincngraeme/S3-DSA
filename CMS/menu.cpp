/*
*   Menu.cpp
*   Description: Renders user interface and calls programs
*   By: Nigel Sinclair, Rita Yevtushenko
*/

#include "menu.h"

// function to handle dynamic buffer for printing menu
/*char* append(char* str)
{
    int len = strlen(str);
    char*
}*/
void renderMainMenu()
{
    printf("\033[0J");      // ANSI escape code to erase screen starting from cursor

    printf("----------------\tWelcome To CMS\t----------------\n\n");
    printf("Send Message\t(1)\n");
    printf("Recieve Message\t(2)\n);
    printf("Exit\t\t(q)\n");

}
void recordMenu()
{
    printf("\033[0J");      // ANSI escape code to erase screen starting from cursor
    printf("Record:\n\n");
    printf("");
}
// Handles all exit processes before exiting the program
void prexit() 
{

}