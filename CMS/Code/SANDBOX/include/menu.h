/*
*   Menu.h
*   By: Nigel Sinclair, Rita Yevtushenko, Fergus Page
*   Desription: Menu header that contains functions declarations for rendering menus and enums for return values
*/

#pragma once

#include <stdio.h>
#include <conio.h>

#define CTRL_KEY(k) ((k) & 0x1f)		// allows for processing ctrl inputs
#define DB_ARG_MAX_SZ 256               // max buffer size for total argument input string to debug mode

// ANSI escape sequences (not compatible with older versions of windows)
const char setH[] = "\033[H";           // set to home position (0,0)
const char clearto[] = "\033[0J";       // Clear Screen starting from cursor to end of screen
const char clearfrom[] = "\033[1J";     // Clear Screen starting from home to cursor
const char clear[] = "\033[2J";
const char setBlnk[] = "\033[5m";      // set mode to blinking
const char resetGraph[] = "\033[0m";    // reset colours/graphics mode
<<<<<<< Updated upstream
const char curUp[] = "\033M";          // move up one line
=======
>>>>>>> Stashed changes

/********** Function Declarations **********/

// printing Functions
void printMainMenu();   
// Transmit
void printTxMenu();     
int TxMode();
// Recieve
void printRxMenu();     
int RxMode();
// Settings
void printSettingsMenu();
int settingsMode();
// Debug
void printDebugMenu();
int debugMode();        // calls printDebugMenu(); then runs a test fn based on user input (only accessible via ctrl + d)

void printQuitMenu();   // Quit