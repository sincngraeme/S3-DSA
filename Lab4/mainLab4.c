#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crc.h"

int main()
{
    // Declare variables
    char message[] = "123456789";       //message buffer
    char* CRCstring;
    crc compCRC;
    int nBytes = strlen(message);

    int newMessageSize = nBytes + 5 + 3;
    char* newMessage = (char*)malloc(newMessageSize * sizeof(char));

    compCRC = crcSlow(message, strlen(message));  //pointer to where the message starts

    for (int i = 0; i <= nBytes; i++)
    {
        compCRC = crcSlow(message, nBytes);
        sprintf(CRCstring, " 0x%x", compCRC);
        strcpy(newMessage, (char*)message);
        strcat(newMessage, CRCstring);
        printf("sent message with CRC: %s\n", newMessage);
        message[i] = '0';
    }

    free(newMessage);
    return 0;
}