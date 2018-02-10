#define _XOPEN_SOURCE
#include <stdio.h> 
#include <string.h> 
#include <math.h> 
#include <cs50.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h> 

int dictionary_test(char *pass, char *plaintext); 

int brute_test(char *pass, char *plaintext); 

int main(int argc, string argv[])
{
	void incrementChar(char string[], int index);

if (argc == 2) {}
    else 
    {
        //error code generated when not exactly one cipher value is passed as command line input.
        printf("Please enter a single hashed password for the command line argument.");
        return 1; // exits with output 1
    }
//get salt from password entered, salt should be first two chars of input hash  
string s = argv[1]; 
char salt[3];
strncpy(salt, s, 2);
salt[2] = '\0';

// process the hash and return password as quickly as possible. 
//step 1 - guess and check common words (four chars or less)
//step 2 - (later) brute force try every method
//step 1
//open dictionary file, and save under var dict

FILE *dict = fopen("/usr/share/dict/words", "r");
char password[255]; 

// check every word in dictionary file < 4 chars using crypto and salt to see if matches hash. 
//If match return 0 and word that was checked. If not move onto brute force method. 
while (fgets(password, 255, (FILE*)dict) != NULL)
{
	if (strlen(password) <= 5 && strcmp(crypt(password, salt), argv[1]) == 0)
	{
		printf("%s", password); 
		return 0; 
	}
	else 
	{

	}
}
fclose(dict);
// step 2
char test_brute[5] = { '\0', '\0', '\0', '\0', '\0' };

    do
    {
        // Compares until next null character
        if (strcmp(crypt(test_brute, salt), argv[1]) == 0)
        {
            // Print password
            printf("%s\n", test_brute);

            return 0;
        }

        // Increment letter
        incrementChar(test_brute, 0);
    }
    while (test_brute[4] == '\0');

    printf("Password not found\n");

    return 0;
}

// Function to increment character and carry over if necessary
void incrementChar(char string[], int index)
{
    if (string[index] == '\0')
    {
        string[index] = '!';
    }
    else if (string[index] == '~')
    {
        string[index] = '!';
        incrementChar(string, index + 1);
    }
    else
    {
        string[index]++;
    }
}





