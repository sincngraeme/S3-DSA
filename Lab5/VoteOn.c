// contains definition for VoteOn function
#include "VoteOn.h"
#include <string.h>

int VoteOn( void *Instances[], int nInstances, int nSize)
{
    int i, j;                       // indeces for the for loops (j is look ahead).
    int maxRepeats = 0;             //Counts the max number of repetitions in a row.
    int maxIndex = -1;              //Tracks the index of the last instance which has the most repeats.
    int curRepeats;                 //Counts the current number of repeats for a given instance.

    for (i = 0; i < nInstances; i++)    //Scroll through the rows of the array.
    {
        curRepeats = 0;                 //No repeats to begin with.
        
        for (j = i + 1; j < nInstances; j++)    //Scroll hrough the columns of the index, within a given row.
        {
            if(memcmp(Instances[i], Instances[j], nSize) == 0)  //Compare the contents of two array elements
            {
                curRepeats++;                                   //If the same, increase the repetition counter.
            }
            
        }
        if(curRepeats > maxRepeats)                             //If the current element's count exceeds the running maximum, the maximum count is increased.
        {
            maxRepeats = curRepeats;
            maxIndex = i;                                       //Record address of new max-repeated element.
        }
    }

    return maxIndex;                                             //Return the index of an instance of the most repeated array element.
    
}