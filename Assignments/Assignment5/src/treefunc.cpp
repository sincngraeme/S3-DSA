/* treefunc.cpp - Implementation of the tree functions in the BST
 * By: Michael
 *
 */

#include "treenode.h"
#include "treefunc.h"
#include "message.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Private variables 
static link root;																// Root of the BST
static Item NullItem; /*= { "Not found - Leaf has been reached" };	*/				// Indicate that a leaf was reached


// Function Implementations

link NEW(Item item, link left, link right)	// Create a new BST node
{							
	printf("\n6.0\n");					
	link pNew = (link)calloc(sizeof(Node), 1);
	printf("\n6.1\n");
	pNew->contents = item;
	printf("\n6.2\n");
	pNew->pLeft = left;
	printf("\n6.3\n");
	pNew->pRight = right; 
	printf("\n6.4\n");
	return(pNew);
}

void BSTInit(void)
{															// Initialize a BST
	root = NEW(NullItem, NULL, NULL);			// Remove this line from Video - otherwise will need to fill empty root with content 
	root = NULL;								// Use this so that content will be added at same time root is created
}
	
Item BSTSearch(link h, char* szKey) {											// Private search function called by 'Search()'
	int rc;
	if (h == NULL) return(NullItem);
	rc = strcmp(szKey, h->contents.buff); 
	if (rc == 0) return(h->contents);

	// Recursive subcalls
	if (rc < 0) return(BSTSearch(h->pLeft, szKey));								// Go left
	else        return(BSTSearch(h->pRight, szKey));
}

Item Search(char* szKey) {														// Public search function
	return(BSTSearch(root, szKey)); 
}

link BSTInsert(link h, Item item) {												// Private insert function called by 'Insert()'
	int rc; 
	if (h == NULL)
	{
		return(NEW(item, NULL, NULL));
	} 
	rc = strcmp(item.buff, h->contents.buff);

	// Recursive subcalls for traversing the tree to get to a leaf
	if (rc < 0) h->pLeft = BSTInsert(h->pLeft, item);
	else        h->pRight = BSTInsert(h->pRight, item);

	return(h);
}

void Insert(Item item) {														// Public insert function 
	root = BSTInsert(root, item);
}

link BSTInsert(link h, Item item, int i) {												// Private insert function called by 'Insert()'
	printf("\n3.0\n");
	int rc; 
	printf("\n3.1\n");
	if (h == NULL)
	{
		printf("\n3.2\n");
		NEW(item, NULL, NULL);
		printf("\n3.3\n");
		return h;
	} 
	printf("\n3.4\n");
	rc = strcmp(item.buff, h->contents.buff);
	printf("\n3.5\n");
	// Recursive subcalls for traversing the tree to get to a leaf
	if (rc < 0) h->pLeft = BSTInsert(h->pLeft, item, i);
	else        h->pRight = BSTInsert(h->pRight, item, i);

	return(h);
}

void Insert(Item item, int i) {	
	printf("\n4.0\n");													// Public insert function 
	root = BSTInsert(root, item, i);
}

void BSTPrint(link h) {															// Private print function called by Print() - Inorder traversal
	if (h == NULL) return; 
	// Recursive subcalls
	BSTPrint(h->pLeft);						// Left
	printf("\nKey: %s\n", h->contents.buff);		// Center
	BSTPrint(h->pRight);					// Right
}

void Print(void) {
	BSTPrint(root); 
}

int height(link h) {															// Returns the height of the BST
	int iLeftH, iRightH;

	if (h == NULL) return(0);				// Base / Terminal condition - reached leaf
											// Updated from video where this returned -1
	// Recursive subcalls 
	iLeftH = height(h->pLeft);
	iRightH = height(h->pRight);

	if (iLeftH > iRightH) return(iLeftH + 1);
	else return(iRightH + 1); 
}

int count(link h) {																// Returns number of nodes in the BST
	if (h == NULL) return(0);													// Baser case / terminal condition 
	return(count(h->pLeft) + count(h->pRight) + 1);
}

link getRoot(void) {															// Returns a pointer to the root of the BST
	return(root);
}


// New function - free nodes in BST via 'postorder' (Left child, right child, parent) traversal of tree to delete from bottom up
void freeBST(link node) {
	if (node == NULL) return;		// Base case - Reached NULL child of leaf node to be free()'d

	// 'Postorder' (L, R, C) traversal
	freeBST(node->pLeft);			// Left
	freeBST(node->pRight);			// Right
	printf("\nNow freeing: %s\n", (node->contents.buff) + 1);  // Delete parent
	free(node);						// Centre (free parent of NULL leaf node)
	
	return;
}