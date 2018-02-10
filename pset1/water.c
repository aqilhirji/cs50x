#include <stdio.h> 
#include <cs50.h>

int main(void)
{
    printf("How long was your shower in minutes?\n");
    int t; 
    do
    {
    t = get_int();
    }
    while (t <= 0);
    int n; 
    n = 12 * t;
    printf("That means you've used %i bottles of water.\n", n);
}