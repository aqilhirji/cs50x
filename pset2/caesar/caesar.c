#include <stdio.h> 
#include <string.h> 
#include <math.h> 
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2) {}
    else 
    {
        //error code generated when not exactly one cipher value is passed as command line input.
        printf("Please enter a single cipher value for the command line argument.");
        return 1; // exits with output 1
    }
    //convert input argv from command line to an integer for cipher
    int k = atoi(argv[1]);
    //printf("%i\n", k); //scaffold used in testing
    
    // get original text input from user to be encrypted
    printf("plaintext:");
    string original_text = get_string(); 
    // check to make sure the user doesn't input an empty string
    if (original_text != NULL)
    {
        printf("ciphertext:");
        //assign initialize counter i, and assign static j to 
        for (int i = 0, j = strlen(original_text); i < j; i++)
        {
            //check case of first character and if upper shift it by the caesar cipher 
            if (isupper(original_text[i]))
            {
                printf("%c", ((original_text[i] - 65 + k) % 26) + 65);
            }
            //check case of first character and if lower shift it by the caesar cipher
            else if (islower(original_text[i]))
            {
                printf("%c", ((original_text[i] - 97 + k) % 26) + 97);
            }
            //if the character is neither upper or lower case, just return it unchanged
            else
            {
                printf("%c", original_text[i]);
            }
        }
        // new line to make the terminal look nicer on output
        printf("\n");
    }
    else 
    {
        //error code generated when null text entered as plaintext string
        printf("Please enter a string for plaintext value");
        return 1; // exits with output 1
    }
}