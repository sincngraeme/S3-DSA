/* Interface: Header file for queueing functions
*  By: Michael Galle
*/
#pragma once
// #include "message.h"
#include "RS232Comm.h"


#define QUEUE_SIZE 5
#define MAX_QUOTE_LENGTH 140

typedef struct node Node;
typedef struct node* link;

struct node {
	link pNext; 
	frame data;
};


class queue {

	public:

	int nodes;
	
	queue(); 									
	int IsQueueEmpty(void); 
	void AddToQueue(link); 
	link DeQueue(void);

	private:

	link pHead, pTail;

};