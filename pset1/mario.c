#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // assigns and initializes vars
int h = 0; // height 
//gets valid input

    
    do
    {
    printf("What's the pyramid height?\n");
    h = get_int(); 
    if (h == 0) // exit on 0 value
    {
        return 0;
    }
    }
    while ((h <= 0) || (h > 23));
    
 //  printf("%i\n", h); //only left in as scaffolding in checking the input learning purposes

    
// // prints correct triangles     
    for (int i = 1; i <= h; i++) // number of loops (lines to print)
    {
        for (int j = 0; j < h-i; j++) // number of spaces
        {
            printf(" "); 
        }
        for (int k = 0; k < i; k++) // number of hashes
        {
            printf("#");
        }
        printf("  "); // print the gap
        
        for (int l = 0; l < i; l++) // number of hashes other side
        {
            printf("#");
        }
        printf("\n"); // adds new line for next set
    }

}