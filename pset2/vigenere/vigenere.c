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
    string key = argv[1];
    for (int l = 0, m = strlen(key); l < m; l++)
    {
        // checks that each character of command line input is alphabetical
        if (isalpha(key[l]) == 0)
        {
            printf("Please enter an alphabetical key for the command line argument.");
            return 1; // exits with output 1
        }
        else 
        {
        }
    }
    // get original text input from user to be encrypted
    printf("plaintext:");
    string original_text = get_string(); 
    // check to make sure the user doesn't input an empty string
    if (original_text != NULL)
    {
        printf("ciphertext:");
        //assign initialize counter i, and assign static j to strlen original text
        //assign key counter m, assign static n to strlen for key
        //isupper and islower build alphabetical checks into the program so isalpha isn't necessary
        for (int i = 0, m = 0, j = strlen(original_text), n = strlen(key); i < j; i++) 
        {
            //check case of input character and if upper shift it by the caesar cipher if upper
            if (isupper(original_text[i]) && isupper(key[m%n]))
            {
                printf("%c", (((original_text[i] - 65 + (key[m%n])) - 65) % 26) + 65);
                m++;
            }
            //check case of input character and if lower shift it by the caesar cipher if lower
            else if (islower(original_text[i]) && islower(key[m%n]))
            {
                printf("%c", (((original_text[i] - 97 + (key[m%n])) - 97) % 26) + 97);
                m++;
            }
            //check case of input character and if upper shift it by the caesar cipher if lower
            else if (isupper(original_text[i]) && islower(key[m%n]))
            {
                printf("%c", (((original_text[i] - 65 + (key[m%n])) - 97) % 26) + 65);
                m++;
            }
            //check case of input character and if lower shift it by the caesar cipher if upper
            else if (islower(original_text[i]) && isupper(key[m%n]))
            {
                printf("%c", (((original_text[i] - 97 + (key[m%n])) - 65) % 26) + 97);
                m++;
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