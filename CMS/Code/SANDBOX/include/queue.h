/* Interface: Header file for queueing functions
*  By: Michael Galle
*/
#pragma once
// #include "message.h"



#define QUEUE_SIZE 5
#define MAX_QUOTE_LENGTH 140

class queue {

	public:

	typedef struct node Node;
	typedef Node* link;

	struct node {
		link pNext; 
		void* data;
	};

	queue(); 									
	int IsQueueEmpty(void); 
	void AddToQueue(queue::link); 
	link DeQueue(void);

	private:

	link pHead, pTail;

};