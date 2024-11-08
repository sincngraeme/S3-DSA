
#pragma once
#define MAX_QUOTE_LENGTH 140	// define the maximum buffer size
#define QUEUE_SIZE 5			// define the size of the queue

typedef struct node Node;	// typedef for nodes
typedef struct item Item; 	// typedef for contents of nodes
typedef Node* link;			// typedef for pointers of nodes

//const int iLength = MAX_QUOTE_LENGTH;	// assign max quote length to a constant integer to be used in the interface

struct item {				// item structure
	char message[MAX_QUOTE_LENGTH];	// message
	short int sid;			// Sender ID
	short int rid;			// Receiver ID 
	char priority;			// Priority of message
	short int seqNum;		// Sequence number of the message
	char later[25];			// Character we might use later 
};

struct node {				// node structure
	link pNext; 			// linking data
	Item Data;				// informational data
};

// Recursive Queue functions
link returnHead();
int count(link x);
link deleteR(link parent, link child, Item v);
void visit(link h);
void traverse(link h, void (*visit)(link));
void traverseR(link h, void (*visit)(link));
