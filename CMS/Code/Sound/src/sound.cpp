/*	Filename: sound.cpp
Author: Michael Galle
Date: Updated 2022
Details: Implementation - Contains functions for Windows sound API (sound recording & playback) 
*/

// #pragma comment(lib, "Ws2_32.lib")	   // Make sure we are linking against the Ws2_32.lib library
// #pragma comment(lib, "Winmm.lib")      // Make sure we are linking against the Winmm.lib library - some functions/symbols from this library (Windows sound API) are used
#include <stdio.h> 
#include <windows.h>					// Contains WAVEFORMATEX structure
#include <mmsystem.h>					////Header for Windows multimedia interfaces. Includes mmeapi.h and others.
#include <math.h>						////Header for math functions.
#include "sound.h"						////Header for the supplied Audio wrapper functions.


// BUFFERS
short iBigBuf[SAMPLES_SEC * RECORD_TIME];
long  lBigBufSize = SAMPLES_SEC * RECORD_TIME;	// total number of samples

// output and input channel parameters 
static	int			g_nSamplesPerSec = SAMPLES_SEC;		////Audio sample rate in Hz (SAMPLES_SEC == 8kHz)
static	int			g_nBitsPerSample = 16;				////Bit depth of samples (16bit)
static	HWAVEOUT	HWaveOut;				/* Handle of opened WAVE Out and In device */
static  HWAVEIN		HWaveIn;				
static	WAVEFORMATEX WaveFormat;			/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
static  WAVEHDR	WaveHeader[NFREQUENCIES];	/* WAVEHDR structures - 1 per buffer */
static  WAVEHDR	WaveHeaderSilence;			// Not used in main yet.
static  WAVEHDR WaveHeaderIn;				

/* PLAYBACK FUNCTIONS */
/* ********************************************************************************************* */

int	InitializePlayback(void)												////Initialize Playback
{
	int		rc;																////Flag for error checking.
	// set up the format structure, needed for playback (and recording)
	SetupFormat(&WaveFormat);
	// open the playback device
	rc = waveOutOpen(&HWaveOut, WAVE_MAPPER, &WaveFormat, (DWORD)NULL, 0, CALLBACK_NULL);
	if (rc) {
		printf("Unable to open Output sound Device! Error %x.", rc);
		return(0);
	}
	return(1);
}

int PlayBuffer(short *piBuf, long lSamples)					////Function to play back a recorded message.
{
	static	WAVEFORMATEX WaveFormat;	/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
	static  WAVEHDR	WaveHeader;			/* WAVEHDR structure for this buffer */
	MMRESULT	mmErr;					
	int		rc;							////Flag for error checking.

	// stop previous note (just in case)
	waveOutReset(HWaveOut);   // is this good?	////Yes. This stops any current playback and returns the current position to 0.
												////This prevents the program from reading unaligned data and partial samples.

	// get the header ready for playback
	WaveHeader.lpData = (char *)piBuf;									////Sets the waveheader struct data pointer to the buffer input to function.
	WaveHeader.dwBufferLength = lSamples * sizeof(short);				////Sets the waveheader struct buffer length to the number of samples times
																		////the size of short to make enough room for all the bits.
	rc = waveOutPrepareHeader(HWaveOut, &WaveHeader, sizeof(WAVEHDR));	////This prepares a waveform block for playback - loads it up.
	if (rc) {															////Error checking the result.
		printf("Failed preparing WAVEHDR, error 0x%x.", rc);
		return(0);
	}
	WaveHeader.dwFlags &= ~(WHDR_BEGINLOOP | WHDR_ENDLOOP);				////Sets the flag in the waveheader struct to indicate the status of the buffer
																		////with respect to queueing, etc.

	// play the buffer. This is NON-blocking.
	mmErr = waveOutWrite(HWaveOut, &WaveHeader, sizeof(WAVEHDR));		////Sends the loaded wave data block to the output device. Records error/non-error code.
	// wait for completion
	rc = WaitOnHeader(&WaveHeader, 0);									////Playback timer - delays program so that playback of that block can finish before moving on.
	// give back resources
	waveOutUnprepareHeader(HWaveOut, &WaveHeader, sizeof(WAVEHDR));		////Cleans out the wavebuffer and undoes what waveoutprepareheader() does.
	return(rc);															////Return error code.
}

void ClosePlayback(void)														////Closes the waveform output device.
{
	int		i;																	////Counter to go through the frequencies.
	for (i = 0; i < NFREQUENCIES; ++i) {										////For loop to traverse the frequencies.
		waveOutUnprepareHeader(HWaveOut, &WaveHeader[i], sizeof(WAVEHDR));		////Unprepares each individual header for the different frequencies.
	}
	// close the playback device
	waveOutClose(HWaveOut);														////Close out the playback buffer.
	return;
}

/* RECORDING FUNCTIONS */
/* ********************************************************************************************* */
int InitializeRecording(void)													////Initialize Recording
{
	MMRESULT rc;																////Initialize error code.

	// set up the format structure, needed for recording.
	SetupFormat(&WaveFormat);													////Sets up the file type for recording so that the samples can be reinterpreted at playback.

	// open the recording device
	rc = waveInOpen(&HWaveIn, WAVE_MAPPER, &WaveFormat, (DWORD)NULL, 0, CALLBACK_NULL);		////Opens the given audio input device for recording.
	if (rc) {																				////Error checking.
		printf("Unable to open Input sound Device! Error %x.", rc);
		return(0);
	}

	// prepare the buffer header for use later on
	WaveHeaderIn.lpData = (char *)iBigBuf;									////Sets the waveheader struct data pointer to the buffer input to function.
	WaveHeaderIn.dwBufferLength = lBigBufSize * sizeof(short);				////Sets the waveheader struct buffer length to the number of samples times
																			////the size of short to make enough room for all the bits.
	rc = waveInPrepareHeader(HWaveIn, &WaveHeaderIn, sizeof(WAVEHDR));		////This prepares a waveform block for playback - loads it up.
	if (rc) {																////Error checking the result.
		printf("Failed preparing input WAVEHDR, error 0x%x.", rc);
		return(0);
	}

	return(1);

}

int	RecordBuffer(short *piBuf, long lBufSize)								////Function to record a message.
{
	static	WAVEFORMATEX WaveFormat;	/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
	static  WAVEHDR	WaveHeader;			/* WAVEHDR structure for this buffer */
	MMRESULT	mmErr;					////Initialize error flag
	int		rc;							////initialize error flag

	printf("Recording now.....");

	// stop previous recording (just in case)
	waveInReset(HWaveIn);   // is this good?							////This stops any current playback and returns the current position to 0.

	// get the header ready for recording.  This should not be needed here AND in init.
	WaveHeader.lpData = (char *)piBuf;									////Sets the waveheader struct data pointer to the buffer input to function.
	WaveHeader.dwBufferLength = lBufSize * sizeof(short);				////Sets the waveheader struct buffer length to the number of samples times
																		////the size of short to make enough room for all the bits.
	rc = waveInPrepareHeader(HWaveIn, &WaveHeader, sizeof(WAVEHDR));	////This prepares a waveform block for recording - loads it up.
	if (rc) {															////Return error code.
		printf("Failed preparing WAVEHDR, error 0x%x.", rc);
		return(0);
	}
	WaveHeader.dwFlags &= ~(WHDR_BEGINLOOP | WHDR_ENDLOOP);				////Sets the flag in the waveheader struct to indicate the status of the buffer
																		////with respect to queueing, etc.

	// Give the buffer to the recording device to fill.
	mmErr = waveInAddBuffer(HWaveIn, &WaveHeader, sizeof(WAVEHDR));
	// Record the buffer. This is NON-blocking.
	mmErr = waveInStart(HWaveIn);
	// wait for completion
	rc = WaitOnHeader(&WaveHeader, '.');
	// stop input
	waveInStop(HWaveIn);
	return(rc);
}

void CloseRecording(void)												////Closes the waveform input device.
{
	waveInUnprepareHeader(HWaveIn, &WaveHeaderIn, sizeof(WAVEHDR));		////Clean out the buffer and header and prepare for closing.
	// close the playback device	
	waveInClose(HWaveIn);												////Close out the input device.
	return;
}


/* SUPPORT FUNCTIONS USED BY PLAYBACK FUNCTIONS - Updated 2021 */
/* ********************************************************************************************* */
// Function needed by InitializePlayback() - SetupFormat() initializes a WAVEFORMATEX structure to the required parameters (sample rate, bits per sample, etc) 
static void SetupFormat(WAVEFORMATEX* wf)
{
	wf->wFormatTag = WAVE_FORMAT_PCM;									////A standard data format used in Windows.
	wf->nChannels = 1;													////Number of channels recorded in one block. Mono/Stereo/Dual Mono.
	wf->nSamplesPerSec = g_nSamplesPerSec;								////Sample rate.
	wf->wBitsPerSample = g_nBitsPerSample;								////Bit depth.
	wf->nBlockAlign = wf->nChannels * (wf->wBitsPerSample / 8);			////Block alignment - how big is a block of data? step through files accordingly.
	wf->nAvgBytesPerSec = wf->nSamplesPerSec * wf->nBlockAlign;			////Data rate.
	wf->cbSize = 0;														////Byte count.
	return;
}

// Function used by Playbuffer() to wait for whatever is playing to finish or quit after waiting 10 seconds
static int WaitOnHeader(WAVEHDR* wh, char cDit)	
{
	long	lTime = 0;															////Start wait time at 0s.
	// wait for whatever is being played, to finish. Quit after 10 seconds.
	for (; ; ) {
		if (wh->dwFlags & WHDR_DONE) return(1);									////If the recording is cone playing, return to whatever you were doing before waiting.
		// idle for a bit so as to free CPU
		Sleep(100L);															////Take a break to free up cpu.
		lTime += 100;															////Increment the elapsed pause time.
		if (lTime >= 10000) return(0);  // timeout period						////If the elapsed time is larger than or equal to 10s, go back to what you were doing.
		if (cDit) printf("%c", cDit);											
	}
}