/*	Filename: sound.h 
	Author: Michael Galle
	Date: Updated 2022
	Details: Interface - Contains prototypes for Windows sound API (sound recording and playback functions)
*/
#pragma once

#include <windows.h>					// Contains WAVEFORMATEX structure

// CONSTANTS - SET RECORDING TIME AND RATE
#define	DEFAULT_NSAMPLES	4000	////Default number of samples.
#define MIN_BUFSIZE			1000	////Minimum buffer size.
#define RECORD_TIME			6		// seconds to record from mic
#define SAMPLES_SEC			8000	// number of samples per second
#define	NFREQUENCIES		96		// number of frequencies used - leave this alone

// FUNCTION PROTOTYPES
/* ************************ */
short* recForTx();
short* playFromRx();
// Playback
int InitializePlayback(void);						////Sets up playback.
int PlayBuffer(short *piBuf, long lSamples);		////Plays recorded audio through a buffer/output device.
void ClosePlayback(void);							////Cleans out the buffers and closes the output device.

// Recording
int InitializeRecording(void);						////Sets up recording.
int	RecordBuffer(short *piBuf, long lBufSize);		////Records audio from input device to buffer.
void CloseRecording(void);							////Cleans out the buffers and closes the input device.

// Support functions for Playback functions (updated 2021)
void SetupFormat(WAVEFORMATEX* wf);			// Used by InitializePlayback()					
int WaitOnHeader(WAVEHDR* wh, char cDit);	// Used by Playbuffer()
