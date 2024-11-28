/* treenode.h - Interface for the tree node structure in the BST
 * By: Michael 
 *
 */

#pragma once

#include "message.h"

//const int iLength = 140; 			//already defineds

typedef struct item Item; 
typedef struct BSTNode Node; 
typedef struct BSTNode* link; 

// Define Item - content of the BST nodes
struct item {
	char buff[iLength];	 // 'Keys' for the BST 
	int senderID; 
	int receiverID;
	int priority;
	int seqNum; 
	char infoArray[15];  // useful for project
	messageitem treeCont;
	int hashNumber;
};

struct BSTNode {
	Item contents;			// msg.buff contains the 'key' which is a quote from the FortuneCookies.txt file
	link pLeft;			// Left subtree
	link pRight;		// Right subtree
};
int treemain();