// main.cpp : This file contains the testing 'main' for the BST functions (client) 
//

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>                       //need for srand().
#include <stdio.h>                      //need for keyboard input.
#include <stdlib.h>                     //need for rand() and srand().
#include <string.h>                     //need for string functions.
#include "treenode.h"                   //need for tree node and link structures.
#include "treefunc.h"                   //need for tree management (arboury haha) functions.
#include "message.h"                    //need for message file access functions and FortuneCookies.txt file.

int treemain()
{
    srand(time(NULL));
    BSTInit();                              // Initialize the BST 
    Item* p;                         
    int i = 0, num = 0;
    char buffer[MAX_QUOTE_LENGTH];          //Changed buffer size to accomodate message.

    // Input from user
    printf("\nHow many node would you like to put into the BST?\n"); 
    while (scanf("%d", &num) != 1) {
        printf("\nPlease enter an integer!\n"); 
        while (getchar() != '\n');
    }

    // Fill the BST
    for (i = 0; i < num; i++) {
        p = (Item*)calloc(1, sizeof(Item)); 
        printf("\n\nItem %d: ", i); 
        //const char* item = messagemain();
        strcpy(p->buff, "When we jumped into Sicily, the units became separated, and I couldn't find anyone.  Eventually I stumbled across two colonels, a major, th");            //encapsulated main from message function set.
        printf("%s\n\n", p->buff);                     //print the string in p->buff .
        Insert(*p, i);                                     //insert the contents of p into the tree, to be sorted linguistically/alphabetically by strcmp().
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

