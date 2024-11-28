/*  TxMode.cpp
*   
*   By: Nigel Sinclair
*   Description: Implementation of Data transmission
*/
#define UNICODE

#include "TxRx.h"


/******************************************** Transmitting *******************************************/


// function for transmitting audio
void TxAudio(short* buf, DWORD szBuf, wchar_t* comport)
{
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings
    
    // set up header
    port1.header.payloadSize = szBuf;                            

    port1.TxToPort(&port1.header, buf);             // output
}
// function for transmitting text
void TxText(char* buf, DWORD szBuf, wchar_t* comport)
{
    RS232Comm port1(comport, 19200, 8);                          // Instantiate port object and initialize settings

    // set up header
    port1.header.payloadSize = szBuf;

    port1.TxToPort(&port1.header, buf);             // output
    port1.TxToPort(&port1.header, buf);             // output
    port1.TxToPort(&port1.header, buf);             // output
    port1.TxToPort(&port1.header, buf);             // output
    port1.TxToPort(&port1.header, buf);             // output
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
            frame msg;                  // contains the messages' header and payload
            msg.header = &portObj.header;       // store header
            msg.payload = *buf;                 // store payload
            Node msgNode;                       // for queue
            msgNode.data = &msg;                // fill node with data
            
            msgQueue.AddToQueue(&msgNode);      // add the message to the queue
        }
        prevnBytes = *nbytes;           // store so it can be accessed after next read operation
    }
    //return 1;                           // If we reached here the user terminated the loop and the transmission was incomplete
    // Now we dequeue
    while (!msgQueue.IsQueueEmpty())        // dequeue until all have been dequed 
    {
        Node msgNode = *msgQueue.DeQueue();
        comhdr header = *(pcomhdr)msgNode.data;         // temp header variable to access data
    }
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
            msgFrame.header = &portObj.header;       // store header
            msgFrame.payload = *buf;                 // store payload
            inMsgNode = (link)malloc(sizeof(Node));                       // Allocate space for the message node
            inMsgNode->data = &msgFrame;                // fill node with data
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
        msgFrame = *(frame*)outMsgNode->data;            // temp header variable to access data since the queue only contains void ptr
        cout << (char*)msgFrame.payload << '\n';                           // print the payload message stored in the message frame for a given node.
        free(outMsgNode);                                      // free the msgNode which we dequeued - the msgFrame is not a ptr and does not need to be freed
    }
}
// function for transmitting images
void RxImage()
{

}
