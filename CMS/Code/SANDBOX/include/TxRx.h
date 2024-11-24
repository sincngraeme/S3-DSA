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
#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std;

void TxAudio(short* buf, long szBuf, wchar_t* comport);
void TxText(char* buf, int szBuf, wchar_t* comport);
void TxImage();

int RxAudio(short** buf, long* nbytes, wchar_t* comport);
int RxText(char** buf, long* nbytes, wchar_t* comport);
void RxImage();