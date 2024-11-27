/*	Filename: sound.h 
	Author: Michael Galle
	Date: Updated 2022
	Details: Interface - Contains prototypes for Windows sound API (sound recording and playback functions)
	Changes:	
				- Changed from static function definitions to audio class.
				-  
*/
#pragma once

#include <windows.h>					// Contains WAVEFORMATEX structure
#include <conio.h>

// CONSTANTS - SET RECORDING TIME AND RATE
#define	DEFAULT_NSAMPLES	4000	////Default number of samples.
#define MIN_BUFSIZE			1000	////Minimum buffer size.
#define RECORD_TIME			6		// seconds to record from mic
#define SAMPLES_SEC			8000	// number of samples per second
#define	NFREQUENCIES		96		// number of frequencies used - leave this alone

struct soundbuf {
	short* outBuf;			
	DWORD outBufSize;
};

soundbuf record();

// FUNCTION PROTOTYPES
/* ************************ */
class audio {

	public: 
	// Constructor
	audio();						// initializes playback and recording upon instantiation

	// BUFFERS
	short iBigBuf[SAMPLES_SEC * RECORD_TIME];
	DWORD  lBigBufSize = SAMPLES_SEC * RECORD_TIME;	// total number of samples


	// Playback
	int InitializePlayback(void);						// Sets up playback.
	int PlayBuffer(short *piBuf, DWORD lSamples);		// Plays recorded audio through a buffer/output device.
	void ClosePlayback(void);							// Cleans out the buffers and closes the output device.

	// Recording
	int InitializeRecording(void);						// Sets up recording.
	int	RecordBuffer(short *piBuf, DWORD lBufSize);		// Records audio from input device to buffer.
	void CloseRecording(void);							// Cleans out the buffers and closes the input device.

	private:

	// output and input channel parameters 
	int					g_nSamplesPerSec = SAMPLES_SEC;		////Audio sample rate in Hz (SAMPLES_SEC == 8kHz)
	int					g_nBitsPerSample = 16;				////Bit depth of samples (16bit)
	HWAVEOUT			HWaveOut;				/* Handle of opened WAVE Out and In device */
	HWAVEIN				HWaveIn;				
	WAVEFORMATEX 		WaveFormat;			/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
	WAVEHDR				WaveHeader[NFREQUENCIES];	/* WAVEHDR structures - 1 per buffer */
	WAVEHDR				WaveHeaderSilence;			// Not used in main yet.
	WAVEHDR 			WaveHeaderIn;				

	// Support functions for Playback functions (updated 2021)
	void SetupFormat(WAVEFORMATEX* wf);			// Used by InitializePlayback()					
	int WaitOnHeader(WAVEHDR* wh, char cDit);	// Used by Playbuffer()

};


void PrintHexDump(const void* buffer, size_t size);
