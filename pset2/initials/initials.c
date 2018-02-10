#include <stdio.h> 
#include <string.h> 
#include <math.h> 
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    string name_1 = get_string();
    if (name_1 != NULL) // check that string from user is not null - exit if null
    {
       // printf("notnull"); // scaffold for learning purposes
    }
    else
    {return 0;}
    if (isspace(name_1[0]) == 0) // check if first character is a space - if not return first char
    {
      printf("%c", toupper(name_1[0]));  
    }
    else {}
    for (int i = 0, j = strlen(name_1); i<(j-1); i++) // check from first char, if one char is space and next is letter return char
    // j - 1 in the last line is important because of i+1 specified below
    {
        //printf("%d", isspace(name_1[i])); // scaffold for educational purposes
        //printf("    %d\n", isspace(name_1[i+1])); // scaffold for educational purposes
        if (isspace(name_1[i]) != 0 && isspace(name_1[i+1]) == 0)
        {printf("%c", toupper(name_1[i+1]));}
        else {}
    }
    printf("\n");  // add new line 
}