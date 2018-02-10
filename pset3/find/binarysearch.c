#include <cs50.h>

#include "helpers.h"
#define MAXX 65536 

/**
 * Returns true if value is in array of n values, else false.
 * BINARY SEARCH
 */
bool search(int value, int values[], int n)
{
    
    int min = 0; //initialize min for search index
    int max = (n - 1); //initialize max search index
    
    while (max >= min)
    {
        int mid = (max + min)/ 2; //recalculate mid
        
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