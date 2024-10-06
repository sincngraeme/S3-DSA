/* Interface: Header file for File IO for getting messages from a file randomly
*  By: Michael Galle
*/

#pragma once

#define MAX_QUOTE_LENGTH 140
#define QUEUE_SIZE 5

const char filePath[] = "FortuneCookies.txt";

// These functions will produce the inputs to the GetMessageFromFile() function
int frandNum(int min, int max);							// Function gets a random number between min and max (max is the number of quotes in the file)
int fnumQuotes(void);									// Function returns number of quotes in the file (only need to run once)
long int* fquoteIndices(int numQuotes);					// Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
int* fquoteLength(int numQuotes, long int* quoteIndices); // Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH

const int iLength = MAX_QUOTE_LENGTH;

typedef struct node Node;
typedef struct item Item; 
typedef Node* link;

struct item {
	char message[iLength];
	short int sid;			// Sender ID
	short int rid;			// Receiver ID 
	char priority;			// Priority of message
	short int seqNum;		// Sequence number of the message
	char later[25];			// Character we might use later 
};

struct node {
	link pNext; 
	Item Data;
};

// Function that gets q random quote from the FortuneCookies file 
int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths);  // buff is a character array (need top pass the node element that is a character array)
void InitQueue(void); 
int IsQueueEmpty(void); 
void AddToQueue(link); 
link DeQueue(void);