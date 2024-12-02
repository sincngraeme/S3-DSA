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
    wchar_t comport[6];
    cout << "\nCOM PORT: ";
    wcin.sync();
    wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input

    RS232Comm portObj(comport, 19200, 8);                          // Instantiate port object and initialize settings
    soundbuf recording;
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    char c1 = '\0';         // initialize to something
    char c2;
   
    cout << "Audio Mode:\n" << "Record\t\t(r)\n" << "Transmit Queue\t\t(t)\n" << "Back\t\t\t(b)\n";       // print menu

    do {
        c1 = getch();
        if(c1 == 'r'){ 
            recording = record();													////End playback operation.
            cout << "Queueing...";
            //queue 
             
            inMsgNode = (link)malloc(sizeof(Node));                         // Allocate space for the message node
            inMsgNode->data.header.payloadSize = recording.outBufSize;                // fill node with data
            inMsgNode->data.payload = recording.outBuf;                                 // We do not need to allocate space for buffer because new memory is allocated with every call of record
            msgQueue->AddToQueue(inMsgNode);             // add message to the queue
        }
        else if(c1 == 't'){ 
            while (!msgQueue->IsQueueEmpty())        // dequeue until all have been dequed, transmitting each one 
            {
                outMsgNode = msgQueue->DeQueue();
                //portObj.TxToPort(&msgFrame.header, (short*)msgFrame.payload);            // output
                audio soundObj;
                soundObj.PlayBuffer((short*)outMsgNode->data.payload, outMsgNode->data.header.payloadSize / sizeof(short)); 
                soundObj.ClosePlayback();
                getchar();
                free(outMsgNode);                                                       // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
            } 
        
            system("pause");
        }
    } while(c1 != 'b'); 
}
// function for transmitting text
void TxText(queue* msgQueue)
{
    wchar_t comport[6];
    cout << "\nCOM PORT: ";
    wcin.sync();
    wcin.getline(comport, sizeof(comport));                      // wide version of cin for user input

    RS232Comm portObj(comport, 19200, 8);                          // Instantiate port object and initialize settings
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    // frame inMsgFrame, outMsgFrame;                                     // contains the messages' header and payload
    string message;
    comhdr header;
    char c1 = '\0';         // initialize to something
    char c2;
   
    cout << "----------------------------------------------\n"; 
    cout << "Text Mode:\n" << "Add Message\t\t(m)\n" << "Transmit Queue\t\t(t)\n" << "Back\t\t\t(b)\n\n";
    cout << "----------------------------------------------\n"; 

    do {
        c1 = getch();
        if(c1 == 'm'){
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
        else if(c1 == 't'){
           
            cout << "----------------------------------------------\n"; 
          
            while (!msgQueue->IsQueueEmpty())        // dequeue until all have been dequed 
            {
                outMsgNode = msgQueue->DeQueue();
                cout << "[Node " << msgQueue->nodes << "\t" << inMsgNode << "]\n"; 
                cout << "Message: ";
                cout.write((char*)outMsgNode->data.payload, outMsgNode->data.header.payloadSize);          // print the message 
                cout << '\n';                 
                free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
            }
        
            cout << "----------------------------------------------\n"; 
            cout << "Press b to close menu\n";
        }
    } while(c1 != 'b');
}
// function for transmitting images
void TxImage()
{

}
/******************************************** Recieving *******************************************/

// function for recieving audio
int RxAudio(short** buf, DWORD* nbytes, wchar_t* comport)
{
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings 
    queue msgQueue;                                    // instantiate queue object
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    frame msgFrame;                                     // contains the messages' header and payload
    DWORD prevnBytes;                                   // temp variable for storing previous nummber of bytes to prevent the wrong value beign assigned.
    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k')
    {
        // if there are no error flags set and the number of bytes recieved from payload is not 0 
        if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR)               
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";                          // 0 bytes on payload
            return 1;                 // recieve from port
        }
        else if(*nbytes == MAXDWORD)            // if we are recieving 0 btyes
        {
            *nbytes = prevnBytes;               // The previous number of bytes contains the paylod size - we do not want to assign MAXDWORD - will result in segfault
            if(portObj.msgStatus) break;        // if the msg flag is set high then something has been recieved
            // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(*nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
            return 1;
        } else {                            // Then data must have been recieved and must be correct size

            // Struct Initialization
            // msgFrame.header = &portObj.header;       // store header
            // msgFrame.payload = *buf;                 // store payload
            inMsgNode = (link)malloc(sizeof(Node));                       // Allocate space for the message node
            inMsgNode->data = msgFrame;                // fill node with data
            cout << "adding to queue"; 
            msgQueue.AddToQueue(inMsgNode);      // add the message to the queue
        }
        prevnBytes = *nbytes;           // store so it can be accessed after next read operation
    }
    //return 1;                           // If we reached here the user terminated the loop and the transmission was incomplete
    // Now we dequeue
    cout << "dequeueing\n";
    while (!msgQueue.IsQueueEmpty())        // dequeue until all have been dequed 
    {
        outMsgNode = msgQueue.DeQueue();
        msgFrame = outMsgNode->data;            // temp header variable to access data since the queue only contains void ptr
        cout << (char*)msgFrame.payload << '\n';                           // print the payload message stored in the message frame for a given node.
        free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
    }
    return 0;
}
// function for recieving text
int RxText(char** buf, DWORD* nbytes, wchar_t* comport)
{
    RS232Comm portObj(comport, 19200, 8);              // instantiate port object and initialize port settings 
    queue msgQueue;                                    // instantiate queue object
    link outMsgNode, inMsgNode;                         // for queueing and dequeuing
    frame msgFrame;                                     // contains the messages' header and payload
    DWORD prevnBytes;                                   // temp variable for storing previous nummber of bytes to prevent the wrong value beign assigned.
    int timeout = 0;                                    // The number of 0 byte receptions that we will allow after the msgStatus flag has been set high
    cout << setBlnk << "\nWaiting..." << curUp << resetGraph;

    while(((kbhit()) ? getch() : 0) != 'k' && timeout < 5)
    {
        // if there are no error flags set and the number of bytes recieved from payload is not 0 
        if((*nbytes = portObj.RxFromPort(&portObj.header, buf)) == 0 || portObj.RS232CommErr != RS232_NO_ERR)               
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << "," << *nbytes << " bytes read.";                          // 0 bytes on payload
            return 1;                 // recieve from port
        }
        else if(*nbytes == MAXDWORD)            // if we are recieving 0 btyes
        {
            *nbytes = prevnBytes;               // The previous number of bytes contains the paylod size - we do not want to assign MAXDWORD - will result in segfault
            if(portObj.msgStatus) timeout++;        // if the msg flag is set high then something has been recieved
            // if a message has been recieved and we are now recieving 0 bytes the full message has been read
        }
        else if(*nbytes != portObj.header.payloadSize)
        {
            cout << "ERROR reading from port: 0x" << portObj.RS232CommErr << ", payload size:" << portObj.header.payloadSize << "does not match " << *nbytes << " bytes read.";
            return 1;
        } else {                            // Then data must have been recieved and must be correct size
            // Struct Initialization
            // msgFrame.header = &portObj.header;       // store header
            // msgFrame.payload = *buf;                 // store payload
            inMsgNode = (link)malloc(sizeof(Node));                       // Allocate space for the message node
            inMsgNode->data = msgFrame;                // fill node with data
            cout << "adding to queue"; 
            msgQueue.AddToQueue(inMsgNode);      // add the message to the queue
        }
        prevnBytes = *nbytes;           // store so it can be accessed after next read operation
    }
    //return 1;                           // If we reached here the user terminated the loop and the transmission was incomplete
    // Now we dequeue
    //cout << setBlnk << "\nDequeueing..." << curUp << resetGraph;
     
    cout << "dequeueing\n";
    while (!msgQueue.IsQueueEmpty())        // dequeue until all have been dequed 
    {
        outMsgNode = msgQueue.DeQueue();
        msgFrame = outMsgNode->data;            // temp header variable to access data since the queue only contains void ptr
        cout << (char*)msgFrame.payload << '\n';                           // print the payload message stored in the message frame for a given node.
        free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
    }
    return 0;
}
// function for transmitting images
void RxImage()
{

}
