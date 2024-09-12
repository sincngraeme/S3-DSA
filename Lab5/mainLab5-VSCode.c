/* main() for VoteOn function 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "VoteOn.h"

struct TestStruct {
	int		i;
	float	f;
	char	c;
	short	s;
};

int main()
{
	// Define the variables used to test the function
	/************************************************************************************************************************************** */
	// Structures
	struct TestStruct a = { 11, 123, 'a', 3217 };	 // a and c are identical
	struct TestStruct b = { 11, 332, 'b', 3217 };
	//struct TestStruct c = { 11, 123, 'a', 3217 };    // a and c are identical -- NOTE: Not true for the version of memcmp() used by VS Code compiler
	struct TestStruct d = { 11, 123, 'd', 3217 };    

	// Changes to code for VSCode 
	/* ******************************************************************************************************** */
	struct TestStruct* c; 											// Use the heap instead of the stack !!!!!
	c = (struct TestStruct*)malloc(sizeof(struct TestStruct)); 	
	memcpy((void*)c, (void*)&a, sizeof(struct TestStruct));

	// changed &c to c below since it is already a pointer  

	/* ********************************************************************************************************* */

	// Arrays of pointers to structures 
	struct TestStruct* List[] = { &a, &b, c, &b, c, &a, &b, &a };   // 3 a's, 2 c's, 3 b's. (So 5 out of 8 are same - we should print either the location of the a or the location of the c).
	struct TestStruct *List2[] = { &b, &a, c };					  // 2 out of 3 are the same since a and c are identical
	struct TestStruct *List3[] = { &b, &a, &d };					  // all different
	struct TestStruct *List4[] = { &b, &a, &d, c };				  // even # of elements, two are identical
	int		i;

	// Variables
	int w = 231, y = 230, z = 231;

	// Array of pointers to variables
	int *x[] = { &w, &y, &z };

	// Test the function 
	/****************************************************************************************************************************************** */
	// Test the function on arrays of pointers to structures
	i = VoteOn((void **)List, 8, sizeof(struct TestStruct));			// Notice how it is cast a 'pointer to a pointer' (using **) 
	printf("Voting on big list returned %d\n", i);						// This is because 'List' is a 'pointer' to the first element of an array of 'pointers' to structs => 'pointer to a pointer'
																		// Result: should be the location of a which is at index 0 (a and c are identical and repeated the most)
	i = VoteOn((void **)List2, 3, sizeof(struct TestStruct));
	printf("Voting on short list returned %d\n", i);					// Result:  should be index 1 since a and c are the same (a is at index 1)

	i = VoteOn((void **)List3, 3, sizeof(struct TestStruct));			
	printf("Voting on failed list returned %d\n", i);					// Result: should be -1 since none of the elements are the same

	i = VoteOn((void **)List4, 4, sizeof(struct TestStruct));
	printf("Voting on even list returned %d\n", i);						// Result: should be index 1 since a and c are the same (a is at index 1)

	i = VoteOn((void **)x, 3, sizeof(int));								// Again notice that x is cast as a 'pointer to a pointer' (using **) 
	printf("Voting on ints returned %d\n", i);							// This is because 'x' is a 'pointer' to the first element of an array of 'pointers' to int's
																		// Result: should be index 0 since w and z are the same (w is at index 0) 
	system("pause");
	return(0);
}
