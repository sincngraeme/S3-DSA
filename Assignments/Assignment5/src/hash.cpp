#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "hash.h"
#include "message.h"
#include "treefunc.h"
#include "treenode.h"


int Hash::hashU(char* c)
{
	int h, a = 31415, b = 27183;

	for ( h=0; *c != '\0'; c++)
    {
	  a =(a*b)%(HASH_TABLE_SIZE-1);   
	  h = (*c + a*h) % HASH_TABLE_SIZE;
	}

	return(h);
}

int Hash::hash(char* c)
{
    int h = hashU(c);

    return (h);
}

// void Hash::STinit()
// {	                    // Make all elements in the ST the heads of linked-lists	
// 	int i;	    			                                    // Initialize the number of linked-lists
// 	link* heads = (link*)malloc(HASH_TABLE_SIZE*sizeof(link)); 	// make hash-table as array of linked lists 

// 	for ( i=0; i < HASH_TABLE_SIZE; ++i)
//     { 
// 		heads[i] = NEW({}, NULL, NULL);	    // All linked-lists are empty to start
// 	} 						                // Alternatively set heads[i] = NULL	

// }

// void Hash::STinit(int m) {	  // Make all elements in the ST the heads of linked-lists	
// 	int i;
// 	N = 0; 		  // Initialize number of items in hash table 	    	
// 	M = m;		  // Initialize the number of linked-lists
// 	heads = (link*)malloc(M*sizeof(link)); 	// make hash-table as array of linked lists 
// 	for ( i=0; i < M; ++i) { 
// 		heads[i] = NEW(NULLitem, NULL);	// All linked-lists are empty to start
// 	} 						// Alternatively set heads[i] = NULL	
// }

// void Hash::STinsert(item item)
// {
// 	//int i = hashU(key(item), M);
// 	heads[i] = NEW(item, heads[i], NULL); 
// 	N++; 
// } 

// void Hash::insert(item item)
// {

//     heads[i] = NEW(item, heads[i], NULL);
// }

// item Hash::STsearch(int v)
// { 
// 	return(Search(heads[hashU(v,M)],v)); 
// }

// void Hash::STdelete(item item)
// {
// 	int i = hashU(key(item), M);
// 	heads[i] = deleteR(heads[i], item); 
// 	N--; 
// }