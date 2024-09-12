// contains definition for VoteOn function

int VoteOn( void *Instances[], int nInstances, int nSize)
{
    int i, j;                       // indeces for the for loops (j is look ahead)
    int maxRepeats = 0;
    int maxIndex = -1;
    int curRepeats;

    for (i = 0; i < nInstances; i++)
    {
        curRepeats = 0;
        
        for (j = i; j < nInstances; j++)
        {
            if(memcmp(Instances[i], Instances[j], nSize) == 0);
            curRepeats++;
        }
        if(curRepeats > maxRepeats) 
        {
            maxRepeats = curRepeats;
            maxIndex = i;
        }
    }

    return maxIndex;
    
}