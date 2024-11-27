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

void TxAudio(short* buf, DWORD szBuf, wchar_t* comport);
void TxText(char* buf, DWORD szBuf, wchar_t* comport);
void TxImage();

int RxAudio(short** buf, DWORD* nbytes, wchar_t* comport);
int RxText(char** buf, DWORD* nbytes, wchar_t* comport);
void RxImage();