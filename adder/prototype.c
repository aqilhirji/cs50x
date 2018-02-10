#include <cs50.h> 
#include <stdio.h>

void print_name(string name); // tell clang that I'll call a function that's created later

int main(void)
{
    string s = get_string(); 
    print_name(s);
}

void print_name(string name)
{
    printf("hello, %s\n", name); 
}