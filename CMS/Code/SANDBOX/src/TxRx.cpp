/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxRx.h"

/******************************************** Transmitting *******************************************/

// function for transmitting audio
void TxAudio(queue* msgQueue)
{
    // wchar_t comport[6];
    // cout << "\nCOM PORT: ";
    // wcin.sync();
    // wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input

    RS232Comm portObj(settings.com.comport, settings.com.bitrate, settings.com.bitdepth);                          // Instantiate port object and initialize settings
    soundbuf recording;
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    char c1 = '\0';         // initialize to something
    char c2;
   
    cout << "----------------------------------------------\n"; 
    cout << "Audio Mode:\n" << "Record\t\t(r)\n" << "Transmit Queue\t\t(t)\n" << "Back\t\t\t(b)\n";       // print menu
    cout << "----------------------------------------------\n"; 
    
    do {
        c1 = getch();
        if(c1 == 'r'){ 
            recording = record();													////End playback operation.
            inMsgNode = (link)malloc(sizeof(Node));                         // Allocate space for the message node
            inMsgNode->data.payload = malloc(recording.nSamples * sizeof(short));                                 // We do not need to allocate space for buffer because new memory is allocated with every call of record
            inMsgNode->data.header.payloadSize = recording.nSamples * sizeof(short);                // fill node with data
            memcpy(inMsgNode->data.payload, recording.outBuf, recording.nSamples * sizeof(short));                                 // We do not need to allocate space for buffer because new memory is allocated with every call of record
            msgQueue->AddToQueue(inMsgNode);             // add message to the queue
            cout << "[Node " << msgQueue->nodes << "\t" << inMsgNode << "]\n"; 
        }
        else if(c1 == 't'){ 
            
            cout << "----------------------------------------------\n"; 
           
            while (!msgQueue->IsQueueEmpty())        // dequeue until all have been dequed, transmitting each one 
            {
                // audio soundObj;
                outMsgNode = msgQueue->DeQueue();
                cout << "[Node " << msgQueue->nodes << "\t" << inMsgNode << "]: "; 
                portObj.TxToPort(&outMsgNode->data.header, (short*)outMsgNode->data.payload);            // output
                free(outMsgNode->data.payload); 
                free(outMsgNode);                                                       // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
            } 
    
            cout << "----------------------------------------------\n"; 
            cout << "Press b to go back\n";
        }
    } while(c1 != 'b'); 
}
// function for transmitting text
void TxText(queue* msgQueue)
{
    // wchar_t comport[6];
    // cout << "\nCOM PORT: ";
    // wcin.sync();
    // wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input

    RS232Comm portObj(settings.com.comport, settings.com.bitrate, settings.com.bitdepth);                          // Instantiate port object and initialize settings
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    // frame inMsgFrame, outMsgFrame;                                     // contains the messages' header and payload
    string message;
    comhdr header;
    char c = '\0';         // initialize to something
   
    cout << "----------------------------------------------\n"; 
    cout << "Text Mode:\n" << "Add Message\t\t(m)\n" << "Transmit Queue\t\t(t)\n" << "Back\t\t\t(b)\n\n";
    cout << "----------------------------------------------\n"; 

    do {
        c = getch();
        if(c == 'm'){
            cout << "Message: ";
            cin.sync();
            getline(cin, message);                         // Get the user's message
            inMsgNode = (link)malloc(sizeof(Node));                                 // Allocate space for the message node
            inMsgNode->data.payload = (char*)malloc(message.size());                // Allocate space for the message itself
            inMsgNode->data.header.payloadSize = message.size();                    // store the message size for transmission
            memcpy(inMsgNode->data.payload, message.c_str(), message.size());       // cpy the message into the newly allocated space
            msgQueue->AddToQueue(inMsgNode);                                        // add the message to the queue
            cout << "[Node " << msgQueue->nodes << "\t" << inMsgNode << "]\n"; 
        }
        else if(c == 't'){
           
            cout << "----------------------------------------------\n"; 
          
            while (!msgQueue->IsQueueEmpty())        // dequeue until all have been dequed 
            {
                outMsgNode = msgQueue->DeQueue();
                cout << "[Node " << msgQueue->nodes << "\t" << inMsgNode << "]: "; 
                cout.write((char*)outMsgNode->data.payload, outMsgNode->data.header.payloadSize);          // print the message 
                cout << '\n';                 
                portObj.TxToPort(&outMsgNode->data.header, (char*)outMsgNode->data.payload);
                free(outMsgNode->data.payload); 
                free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
            }
        
            cout << "----------------------------------------------\n"; 
            cout << "Press b to close menu\n";
        }
    } while(c != 'b');
}
// function for transmitting images
void TxImage()
{

}
/******************************************** Recieving *******************************************/

// function for recieving audio
int RxAudio()
{
    int timeout = 0;
    short* buf;
    DWORD nBytes = 0;  
    RS232Comm portObj(settings.com.comport, settings.com.bitrate, settings.com.bitdepth);              // instantiate port object and initialize port settings 
    queue msgQueue;                                    // instantiate queue object
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    frame msgFrame;                                     // contains the messages' header and payload
    DWORD prevnBytes;                                   // temp variable for storing previous nummber of bytes to prevent the wrong value beign assigned.
    audio soundObj;
    soundbuf recording;
    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k' && timeout < 5)
    {
        // if there are no error flags set and the number of bytes recieved from payload is not 0 
        if((nBytes = portObj.RxFromPort(&portObj.header, &buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR)               
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << nBytes << " bytes read.";                          // 0 bytes on payload
            timeout++; 
        }
        else if(nBytes == MAXDWORD)            // if we are recieving 0 btyes
        {
            nBytes = prevnBytes;               // The previous number of bytes contains the paylod size - we do not want to assign MAXDWORD - will result in segfault
            if(portObj.msgStatus) timeout++;        // if the msg flag is set high then something has been recieved
            // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(nBytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << nBytes << " bytes read.";
            return 1;
        } else {                            // Then data must have been recieved and must be correct size
            
            timeout = 0;                // if we are recieving reset 
            inMsgNode = (link)malloc(sizeof(Node));                       // Allocate space for the message node
            inMsgNode->data.payload = (short*)malloc(portObj.header.payloadSize);
            inMsgNode->data.header.payloadSize = portObj.header.payloadSize;
            memcpy(inMsgNode->data.payload, buf, portObj.header.payloadSize); 
            msgQueue.AddToQueue(inMsgNode);      // add the message to the queue
        }
        prevnBytes = nBytes;           // store so it can be accessed after next read operation
    }
    // Now we dequeue

    cout << "----------------------------------------------\n"; 

    while (!msgQueue.IsQueueEmpty())        // dequeue until all have been dequed 
    {
        soundObj.InitializePlayback();
        outMsgNode = msgQueue.DeQueue();
        cout << "[Node " << msgQueue.nodes << "\t" << outMsgNode << "]\n"; 
        soundObj.PlayBuffer((short*)outMsgNode->data.payload, outMsgNode->data.header.payloadSize / sizeof(short));
        soundObj.ClosePlayback();
        free(outMsgNode->data.payload); 
        free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
    }

    cout << "----------------------------------------------\n"; 
    cout << "Press b to close menu\n";
    while(getch() != 'b'); 
    return 0;
}
// function for recieving text
int RxText()
{
    DWORD nbytes = 0;
    short* buf;
    RS232Comm portObj(settings.com.comport, settings.com.bitrate, settings.com.bitdepth);              // instantiate port object and initialize port settings 
    queue msgQueue;                                    // instantiate queue object
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    DWORD prevnBytes;                                   // temp variable for storing previous nummber of bytes to prevent the wrong value beign assigned.
    int timeout = 0;                                    // The number of 0 byte receptions that we will allow after the msgStatus flag has been set high
    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k' && timeout < 5)
    {
        // if there are no error flags set and the number of bytes recieved from payload is not 0 
        if((nbytes = portObj.RxFromPort(&portObj.header, &buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR)               
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << nbytes << " bytes read.";                          // 0 bytes on payload
            while(!msgQueue.IsQueueEmpty())
            {
                outMsgNode = msgQueue.DeQueue();
                free(outMsgNode->data.payload);
                free(outMsgNode);
            }
            return 1;                 // recieve from port
        }
        else if(nbytes == MAXDWORD)            // if we are recieving 0 btyes
        {
            nbytes = prevnBytes;               // The previous number of bytes contains the paylod size - we do not want to assign MAXDWORD - will result in segfault
            if(portObj.msgStatus) timeout++;        // if the msg flag is set high then something has been recieved
            // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << nbytes << " bytes read.";
            while(!msgQueue.IsQueueEmpty())
            {
                outMsgNode = msgQueue.DeQueue();
                free(outMsgNode->data.payload);
                free(outMsgNode);
            }
            return 1;
        } else {                            // Then data must have been recieved and must be correct size
            // Struct Initialization
            inMsgNode = (link)malloc(sizeof(Node));                       // Allocate space for the message node
            inMsgNode->data.payload = (char*)malloc(portObj.header.payloadSize);
            inMsgNode->data.header.payloadSize = portObj.header.payloadSize;                // fill node with data
            memcpy(inMsgNode->data.payload, buf, portObj.header.payloadSize);               // copy buffer into node
            msgQueue.AddToQueue(inMsgNode);      // add the message to the queue
        }
        prevnBytes = nbytes;           // store so it can be accessed after next read operation
    }
    //return 1;                           // If we reached here the user terminated the loop and the transmission was incomplete
    // Now we dequeue
    //cout << setBlnk << "\nDequeueing..." << curUp << resetGraph;
     
    cout << "----------------------------------------------\n"; 
    
    while (!msgQueue.IsQueueEmpty())        // dequeue until all have been dequed 
    {
        outMsgNode = msgQueue.DeQueue();                                                                            // dequeue 
        cout << "[Node " << msgQueue.nodes << "\t" << outMsgNode << "]: "; 
        cout.write((char*)outMsgNode->data.payload, outMsgNode->data.header.payloadSize);                           // print the payload message stored in the message frame for a given node.
        cout << "\n"; 
        free(outMsgNode->data.payload); 
        free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
    }
    
    cout << "----------------------------------------------\n"; 
    cout << "Press b to close menu\n";
    while(getch() != 'b'); 
    return 0;
}
