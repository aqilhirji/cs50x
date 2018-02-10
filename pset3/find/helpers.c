/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
#define MAXX 65536 

/**
 * Returns true if value is in array of n values, else false.
 * BINARY SEARCH -- keep order at log(n) or O(logn)
 */
bool search(int value, int values[], int n)
{
    
    int min = 0; //initialize min for search index
    int max = (n - 1); //initialize max search index
    
    while (max >= min)
    {
        int mid = (max - min)/ 2 + min; //recalculate mid
        
        if(value == values[mid])
        {
        return true; //if the values aer equal return true
        }
        else if (value < values[mid]) //if the value is less than middle, throw away top half
        {
            max = (mid - 1);
        }
        else if (value > values[mid]) // if the value is more than middle, throw away bottom half
        {
            min = (mid + 1); 
        }
    }
    
    return false; //once there's nothing left to throw away
}

/**
 * Sorts array of n values.
 * using count sort to keep at order n or O(n)
 */
void sort(int values[], int n)
{
// create the counting array with the defined max "slots" as per header (0 each slot)
int counting_array[MAXX] = { 0 };

//for loop to add one to the counting slot for each number in the array 
for (int i = 0; i < n; i++)
{
    counting_array[values[i]]++; 
}

int l = 0; //intialize l to 0 for loop fx

//create the new sorted array called values. 
for (int j = 0; j < MAXX; j++)
{
    if (counting_array[j] > 0)
    {
        for (int k = 0; k < counting_array[j]; k++)
        {
            values[l] = j; 
            //printf("%d", values[k]);
            l++; 
        }
    }
}
return; 
}

    
    
