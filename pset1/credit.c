#include <stdio.h>
#include <cs50.h>
#include <string.h> 
#include <ctype.h>
#include <math.h> 


int main(void)
{
    int long long cc = 0; 
    do
    {
    printf("Number:\n"); 
    cc = GetLongLong(); // get credit card input from user
    } 
    while (cc < 0); 
    
    //find the number of digits in the card, end if not 13, 15, or 16
    int len = 0; 
    len = floor(log10(llabs(cc))) + 1; 
    //printf("Length %i", len); scaffolding for checking length calculation - left for educational reasons
    
     if (len == 13 || len == 15 || len == 16 )
     {
     }
     else 
     {
         printf("INVALID\n");
         return 0; 
     }
    //start the checksum portion (Luhn's Algorithm), first find the second to last digit 
    //and every second one from there backwards (second last digit has index=len-2) and add individual digits
    int long long chk_1 = 0; // intializing first part of checksum
   
    for(int i = 0; i < (len/2); i++)
    {
       // cc_chk1 
        int long long floor_pre_modulo = (floor(cc/(pow(10,((i*2)+1))))); 
        int long long modulo_i = floor_pre_modulo % 10; 
       // printf("modulo_i %i\n", modulo_i);
        int long long digits_1 = modulo_i * 2;
        int long long add_digits_1 = digits_1 % 10;// last digit 
        int long long add_digits_2 = floor(digits_1/10); //first digit (or 0 if single digit)
        //printf("d1 %i\n", digits_1); //scaffold for testing
        //printf("d1a %i\n", add_digits_1); //scaffold for testing
       // printf("d2a %i\n", add_digits_2); // scaffold for testing
        chk_1 = chk_1 + add_digits_1 + add_digits_2;
        //printf("chk_1 %i\n", chk_1);
    }
    
    //printf("chk_1 %lli\n", chk_1); //scaffold
    
    // this part checks the remaining digits from the end, 1, 3, 5, 7, etc and adds them to a chk2 varibLe. This 
    //will depend on the length of the credit card number and use a for loop. 
    int long long chk_2 = 0; //initializing the second part of checksum
    
    for(int j = 0; j <= (len/2); j++)
    {
        int long long floor_pre_modulo_chk2 = (floor(cc/(pow(10,((j*2))))));
        int long long modulo_j = floor_pre_modulo_chk2 % 10; 
        //printf("modulo_2 %i\n", floor_pre_modulo_chk2);
        chk_2 = chk_2 + modulo_j; 
        //printf("chk_2 %i\n", chk_2); 
    }
    
    //printf("chk_2 %lli\n", chk_2); //scaffold
    
    int long long check_sum = chk_1 + chk_2; // calculate checksum
    //printf("check_sum %lli\n", check_sum); //scaffold
    
    int long long chksum_ld = check_sum % 10; //assign last digit of checksum to chksum_ld
    //printf("check_sum_ld %lli\n", chksum_ld); //scaffold
    // print invalid and exit if checksum does not have a 0 last digit
    if (chksum_ld == 0)
    {
        
    }
    else 
    {
        printf("INVALID\n");
        return 0; 
    }
    
    //now check the first digits for cc type 
    
    int long long first_two = (floor(cc/(pow(10,(len-2))))); 
    //printf("first_two %lli\n", first_two); //scaffold
    int long long first_one = (floor(cc/(pow(10,(len-1)))));
    //printf("first_one %lli\n", first_one); //scaffold
    
    // assign the type of card or return invalid if no match found. 
    
    if (first_one == 4)
    {
        printf("VISA\n");
        return 0; 
    }
    else if (first_two == 34 || first_two == 37)
    {
        printf("AMEX\n");
        return 0; 
    }
    else if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
    {
        printf("MASTERCARD\n");
        return 0; 
    }
    else
    {
        printf("INVALID\n");
        return 0; 
    }
}