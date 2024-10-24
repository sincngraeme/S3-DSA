/*	Filename: main.cpp
Author: Michael Galle
Date: Updated 2022
Details: Testing mainline for Windows sound API
*/

#include "sound.h"
#include <stdio.h>
#include <windows.h>

int	main(int argc, char *argv[])
{
	extern short iBigBuf[];												// buffer
	extern long  lBigBufSize;											// total number of samples
	short* iBigBufNew = (short*)malloc(lBigBufSize*sizeof(short));		// buffer used for reading recorded sound from file

	char save;															////Character buffer for saving command.
	char replay;														////Character buffer for replay command.
	char c;																// used to flush extra input
	FILE* f;															////Initialize file pointer.

	// initialize playback and recording
	InitializePlayback();												////Program initialization. Setup playback.
	InitializeRecording();												////Program initialization. Setup recording.

	// start recording
	RecordBuffer(iBigBuf, lBigBufSize);									////Record some audio into the buffer.
	CloseRecording();													////End recording opertaion.

	// playback recording 
	printf("\nPlaying recording from buffer\n");
	PlayBuffer(iBigBuf, lBigBufSize);									////Play the recorded audio from the buffer.
	ClosePlayback();													////End playback operation.

	// save audio recording  
	printf("Would you like to save your audio recording? (y/n): "); 
	scanf("%c", &save);											////Check for save command.
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((save == 'y') || (save == 'Y')) {								////Check the command result.
		/* Open input file */
		f = fopen("C:\\myfiles\\recording.dat", "wb");				////Open the save location.
		if (!f) {														////Error handling.
			printf("unable to open %s\n", "C:\\myfiles\\recording.dat");
			return 0;
		}
		printf("Writing to sound file ...\n");
		fwrite(iBigBuf, sizeof(short), lBigBufSize, f);					////Write the buffer contents into memory.
		fclose(f);
	}

	// replay audio recording from file -- read and store in buffer, then use playback() to play it
	printf("Would you like to replay the saved audio recording from the file? (y/n): ");
	scanf("%c", &replay);											////Check for replay command.
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((replay == 'y') || (replay == 'Y')) {							////Check the command result.
		/* Open input file */
		f = fopen("C:\\myfiles\\recording.dat", "rb");				////Open the saved file location.
		if (!f) {														////Error handling.
			printf("unable to open %s\n", "C:\\myfiles\\recording.dat");
			return 0;
		}
		printf("Reading from sound file ...\n");
		fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
		fclose(f);														////Close file location.
		InitializePlayback();											////Get ready to play audio.
		printf("\nPlaying recording from saved file ...\n");
		PlayBuffer(iBigBufNew, lBigBufSize);							////Play the audio from the file.
		ClosePlayback();												////End playback operation.
	}
	
	printf("\n");
	system("pause");													////Program pause.
	return(0);
}