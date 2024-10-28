// main.cpp : This file contains the testing 'main' for the BST functions (client) 
//

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treenode.h"
#include "treefunc.h"
#include "message.h"

int main()
{
    srand(time(NULL));
    BSTInit();                              // Initialize the BST 
    Item* p = NULL;                         
    int i, num;                 
    char buffer[MAX_QUOTE_LENGTH];          //Changed buffer size to accomodate message.

    // Input from user
    printf("\nHow many node would you like to put into the BST?\n"); 
    while (scanf("%d", &num) != 1) {
        printf("\nPlease enter an integer!\n"); 
        while (getchar() != '\n');
    }

    // Fill the BST
    for (i = 0; i < num; i++) {
        p = (Item*)malloc(sizeof(Item)); 
        printf("\n\nItem %d: ", i); 
        //memcpy(buffer, messagemain(), MAX_QUOTE_LENGTH);
        //strcpy(buffer, messagemain());               //Replaced %s with quote from file
        //buffer[139] = '\0';                         //Took care of this in GetMessageFromFile() in message.cpp, on lines 137-145.
        strcpy(p->buff, messagemain());
        printf("%s \n\n", p->buff);
        Insert(*p);
    }

    // Print the BST 'Inorder'
    printf("\nPrinting the BST Inorder"); 
    Print();                                        // Print the contents of the BST

    // Search BST for the last inserted item 
    printf("\n\nSearching the BST for the last inserted item\n");
    if (Search(p->buff).buff) {
        printf("\nFound last item in the tree: %s\n", Search(p->buff).buff);
    } 

    // Run the count() function on the tree
    printf("\n***********************************************************\n");
    printf("\nThe number of nodes in the tree is: %d\n", count(getRoot()));

    // Run the height function on the tree 
    printf("\n***********************************************************\n");
    printf("\nThe height of the tree is: %d\n", height(getRoot()));

    // Free the nodes in the BST - Not in the YouTube Video
    /*************************************************************************/
    //free(getRoot());  // Incorrect - this just frees the first node and causes a memory leak since the other nodes are not free()'d
    printf("\n***********************************************************\n");
    printf("\nNow freeing the nodes in the tree from the bottom up via postorder traversal");
    freeBST(getRoot());
    p = NULL;
       
    return(0);
}

