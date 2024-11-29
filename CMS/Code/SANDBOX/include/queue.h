/* Interface: Header file for queueing functions
*  By: Michael Galle
*/
#pragma once
// #include "message.h"



#define QUEUE_SIZE 5
#define MAX_QUOTE_LENGTH 140

typedef struct node Node;
typedef struct node* link;

struct node {
	link pNext; 
	void* data;
};


class queue {

	public:
	
	queue(); 									
	int IsQueueEmpty(void); 
	void AddToQueue(link); 
	link DeQueue(void);

	private:

	link pHead, pTail;

};