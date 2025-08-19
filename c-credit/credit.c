#include <cs50.h>
#include <stdio.h>

bool validation(long long credit); // function prototype for validation function

int main(void)
{
    // prompt user for credit card number
    long long credit = get_long_long("NUMBER: ");

    if (credit / 1000000000000 > 0 && credit / 1000000000000000 < 10)
    {
        if (credit / 1000000000000 > 0 && credit / 1000000000000 < 10 &&
            credit / 1000000000000 == 4)
        {
            if (validation(credit) ==
                true) // if the credit card number is valid according to the Luhn algorithm
            {
                printf("VISA\n"); // print valid message
            }
            else // if the credit card number is not valid according to the Luhn algorithm
            {
                printf("INVALID\n"); // print invalid message
            }
        }

        else if (credit / 100000000000000 > 0 && credit / 100000000000000 < 10 &&
                 (credit / 10000000000000 == 34 || credit / 10000000000000 == 37))
        {
            if (validation(credit) ==
                true) // if the credit card number is valid according to the Luhn algorithm
            {
                printf("AMEX\n"); // print valid message
            }
            else // if the credit card number is not valid according to the Luhn algorithm
            {
                printf("INVALID\n"); // print invalid message
            }
        }

        else if (credit / 1000000000000000 > 0 && credit / 1000000000000000 < 10 &&
                 credit / 1000000000000000 == 4)
        {
            if (validation(credit) ==
                true) // if the credit card number is valid according to the Luhn algorithm
            {
                printf("VISA\n"); // print valid message
            }
            else // if the credit card number is not valid according to the Luhn algorithm
            {
                printf("INVALID\n"); // print invalid message
            }
        }

        else if (credit / 1000000000000000 > 0 && credit / 1000000000000000 < 10 &&
                 (credit / 100000000000000 == 51 || credit / 100000000000000 == 52 ||
                  credit / 100000000000000 == 53 || credit / 100000000000000 == 54 ||
                  credit / 100000000000000 == 55))
        {
            if (validation(credit) ==
                true) // if the credit card number is valid according to the Luhn algorithm
            {
                printf("MASTERCARD\n"); // print valid message
            }
            else // if the credit card number is not valid according to the Luhn algorithm
            {
                printf("INVALID\n"); // print invalid message
            }
        }
        else
        {
            printf("INVALID\n"); // print invalid message
        }
    }
    else // if the credit card number is not between 13 and 16 digits
    {
        printf("INVALID\n"); // print invalid message
    }
}

bool validation(long long credit)
{
    int sum_even = 0; // variable to hold the sum of even digits
    int sum_odd = 0;  // variable to hold the sum of odd digits
    int count = 0;    // variable to hold the number of digits
    bool x = false;   // variable to hold the result of the Luhn algorithm check
    for (int i = 0; credit > 0; i++)
    {
        int digit = credit % 10; // get the last digit of the credit card number
        credit /= 10;            // remove the last digit from the credit card number

        if (count % 2 == 0) // if the digit is in an even position (counting from the right)
        {
            sum_odd += digit; // add the digit to the sum of odd digits
        }
        else // if the digit is in an odd position
        {
            digit *= 2;    // double the digit
            if (digit > 9) // if the doubled digit is greater than 9
            {
                digit -= 9; // subtract 9 from the digit to get the sum of its digits
            }
            sum_even += digit; // add the digit to the sum of even digits
        }
        count++; // increment the count of digits
    }
    x = ((sum_even + sum_odd) % 10 == 0)
            ? true
            : false; // check if the sum of even and odd digits is divisible by 10
    return x;        // return the result of the Luhn algorithm check
}
