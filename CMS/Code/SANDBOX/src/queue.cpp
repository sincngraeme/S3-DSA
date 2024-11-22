#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "queue.h"
#include "message.h"

Queue::Queue()
{  
	InitQueue();
}

void* Queue::addQueueNode(pcomhdr header, void* payload)
{
    messagelink p;                                          //initialize queue node
    p = (messagelink)malloc(sizeof(messageNode));           //allocate space for node
    p->Data.header = *header;
    p->Data.message = payload;                              //copy the received frame data into the message buffer in the queue node
    p->Data.length = header->payloadSize;               //store the length of the message in the struct
    if(p->Data.length == NULL)		                //check to see if the frame contains any data
		{
			free(p);										//if no data, free the memory
			return NULL;								    //we dont want to add if there is an error
		}
 
    AddToQueue(p);                                          //add the node to the queue
    free(p);                                                //free the memory
    return 0;
}

void* Queue::popQueueNode()
{
    messagelink q;                                          //initialize queue node
    q = (messagelink)malloc(sizeof(messageNode));           //allocate space for node
    void* frame;                                            //initialize intermediate variable so memory can be freed before returning the frame
    
    if (!IsQueueEmpty())                                    //if queue not empty
    {                                 
        q = DeQueue();                                      //receive node pointer from the queue
        frame = q->Data.message;		                    //assign the frame data to the termporary frame pointer
        free(q);									        //data has been accessed so free q
        return frame;                                       //return the frame pointer to whatever initiated the funciton call
    }

    else                                 
    {
        free(q);                                            //free memory
        return NULL;                                        //return null pointer
    }
}

