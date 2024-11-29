#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			//need for dynamic allocation of memory.
#include <time.h>			//needed for srand.
#include "treefunc.h"
#include "treenode.h"
#include "message.h"
#include "hash.h"
#include "queue.h"

int main()
{
    Hash hashing; 
    int iMsgList [CURRENT_NUM_QUOTES];
    int numQuotes = fnumQuotes();									    // Number of quotes
	long int* quoteIndices = fquoteIndices(numQuotes);					// Index locations of the quotes
	int* quoteLengths = fquoteLength(numQuotes, quoteIndices);		    // Length of each quote (up to MAX_QUOTE_LENGTH) - cut off after

    for(int i = 0; i < HASH_TABLE_SIZE, i++)
    {
        Queue i;            //Dynamically allocate queue objects by changing variable name.
    }
   
    for(int i = 0; i <  CURRENT_NUM_QUOTES; i++)
    {
        queuenode* p = (queuenode*)malloc(sizeof(queuenode));
        GetMessageFromFile(p->Data.contents.message, MAX_QUOTE_LENGTH, i, numQuotes, quoteIndices, quoteLengths);
        p->Data.hashNumber = hashing.hash(p->Data.contents.message);
       
        if(hashing.hashTable[p->Data.hashNumber] == -1)
        {
            InitQueue();
            AddToQueue(p);
            hashing.heads[p->Data.hashNumber] = *p;
            hashing.hashTable[i] = p->Data.hashNumber;
            hashing.hashOccurrances[p->Data.hashNumber]++;
            p->Data.messageNumber = i;
        }

        else if(hashing.hashTable[p->Data.hashNumber] != -1)
        {
            AddToQueue(p);
            iMsgList[i] = hashing.hashTable[p->Data.hashNumber];
            hashing.hashTable[i] = p->Data.hashNumber;
            hashing.hashOccurrances[p->Data.hashNumber]++;
        }

        else
        {

        }

        //printf("Message\t%d \thas a hash number:\t%d\t and the message is: %s\n\n", i, hashTable[i], message);
    }

    free(quoteIndices);
	free(quoteLengths);
    queuenode* b = (queuenode*)malloc(sizeof(queuenode));
    printf("Hash #:\t\tNumber of Occurrances:\t\tMessage Numbers:\n\n");
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        *b = hashing.heads[i];
        printf("%d...............%d.............................\n", i, hashing.hashOccurrances[i]);
        printf("%d, ", b->Data.messageNumber);
        int j = 0;

        if((b->pNext != NULL) & (j <= CURRENT_NUM_QUOTES))
        {
            printf("%d, ", b->Data.messageNumber);
            b = b->pNext;
            j++;
        }

        printf("%d\n", b->Data.messageNumber);

        // for(int j = 0; j <= hashing.hashOccurrances[i]; j++, b = b->pNext)
        // {
        //     printf("%d, ", b->Data.messageNumber);
        // }

        // printf("%d", i, hashing.hashOccurrances[i]);             
    }
    		
    return 0;

};