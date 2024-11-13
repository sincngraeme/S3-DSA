#include <stdlib.h>
#include <Windows.h>    
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define CTRL_KEY(k) ((k) & 0x1f)		// allows for processing ctrl inputs

class Debug {
    private:
        // int dTxAudio();
        int dTxText();
        // int dTxImage();
        // int dRxAudio();
        // int dRxText();
        // int dRxImage();
        // int dSetParameters();

    public:
        void debugGeneral(int select);

};