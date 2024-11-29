/*  TxAudio.cpp
*   
*   By: Nigel Sinclair
*   Description: Header file for Data transmission
*/
#pragma once

#define UNICODE

#include "RS232Comm.h"
#include "RS232Comm.h"
#include "sound.h"
#include "queue.h"
#include "menu.h"
#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

// these take a pointer to a queue object so they are both sending messages on the same queue
void TxAudio(queue* msgQueue);
void TxText(queue* msgQueue);
void TxImage();

int RxAudio(short** buf, DWORD* nbytes, wchar_t* comport);
int RxText(char** buf, DWORD* nbytes, wchar_t* comport);
void RxImage();