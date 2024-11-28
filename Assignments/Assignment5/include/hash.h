#pragma once
#include "treenode.h"
#include"treefunc.h"
#include "queue.h"
#define HASH_TABLE_SIZE 29
#define MAX_NUM_QUOTES 1140
#define CURRENT_NUM_QUOTES 110

// Creates the hash table that implements separate chaining to handle collisions
// static link* heads;                          // array of pointers to the linked-lists in the hash table
// static Item NullItem = {}; 	        	  // children of leaf nodes
// static int hashTable[CURRENT_NUM_QUOTES] = {-1};        //iMsgList
// static int hashOccurrances[HASH_TABLE_SIZE] = {-1};     //iHashTab
// static link root;			                  // root (private var)
// static link* heads;      // array of pointers to the linked-lists in the hash table
// static int M;		  // number of linked lists
// static int N;		  // total number of items in the hash table	

class Hash
{
    private:

        // Creates the hash table that implements separate chaining to handle collisions
        Item NullItem = {}; 	        	  // children of leaf nodes
        link root;			                  // root (private var)
        int M;		  // number of linked lists
        int N;		  // total number of items in the hash table	


        int hashU(char* c);
        // void STinit(int m);
        // void STinsert(item item);
        // item STsearch(int v);
        // void STdelete(item item);
    
    public:

        queuenode* heads;      // array of pointers to the linked-lists in the hash table
        int hashTable[CURRENT_NUM_QUOTES] = {-1};        //iMsgList
        int hashOccurrances[HASH_TABLE_SIZE] = {0};     //iHashTab
        int hash(char* c);
        // void insert(item item);
        

};


