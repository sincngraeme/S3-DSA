/*
*   Menu.h
*   Description: Renders user interface and calls programs
*   By: Nigel Sinclair, Rita Yevtushenko
*/

#pragma once

#include <stdio.h>
#include <string.h>

enum options {
    record = 1,
    exit = 'q'
};

//char* append(char* str);
void renderMainMenu();      // prints main menu
void prexit();          // prints any relevant info and runs any atexit processes, then exits program