
#define MAX_QUOTE_LENGTH 140	// define the maximum buffer size
#define QUEUE_SIZE 5			// define the size of the queue

class Recursion
{
	private:

	typedef struct node Node;	// typedef for nodes
	typedef struct item* Item; 	// typedef for contents of nodes
	typedef Node* link;			// typedef for pointers of nodes

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

	public:

	// Recursive Queue functions

	link returnHead(link pHead);
	int count(link p);
	link deleteR(link parent, link child, Item v);
	void visit(link h);
	void traverse(link h, void (*visit)(link));
	void traverseR(link h, void (*visit)(link));
};