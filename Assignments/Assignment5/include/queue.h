/* Interface: Header file for queueing functions
*  By: Michael Galle
*/

#pragma once
#include "message.h"
#define QUEUE_SIZE 5
#define MAX_QUOTE_LENGTH 140

const int iLen = MAX_QUOTE_LENGTH;

struct queueitem
	{
		char message[iLen];
		short int sid;			// Sender ID
		short int rid;			// Receiver ID 
		char priority;			// Priority of message
		short int seqNum;		// Sequence number of the message
		char later[25];			// Character we might use later 
		messageitem contents;
		int hashNumber;
		int messageNumber;
	};

	typedef struct queueitem queueItem;
	typedef struct queuenode queueNode;
	typedef queueNode* queuelink;

	struct queuenode
	{
		queuelink pNext; 
		queueItem Data;
	};

class Queue
{
	public: 

	Queue();

	// Function that gets q random quote from the FortuneCookies file 
	//int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths);  // buff is a character array (need top pass the node element that is a character array)
	void InitQueue(void); 
	int IsQueueEmpty(void); 
	void AddToQueue(queuelink); 
	queuelink DeQueue(void);

	private:

	queuelink pHead, pTail;

};




