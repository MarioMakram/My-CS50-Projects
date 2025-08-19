#include <cs50.h>
#include <stdio.h>

int quarters_charges(int cents);
int dimes_charges(int cents);
int nickels_charges(int cents);
int pennies_charges(int cents);

int main(void)
{
    // Prompt user for a charges
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    } while (cents < 0);
    int quarters = quarters_charges(cents);
    cents -= quarters * 25; // Update the charges after calculating quarters
    int dimes = dimes_charges(cents);
    cents -= dimes * 10; // Update the charges after calculating dimes
    int nickels = nickels_charges(cents);
    cents -= nickels * 5; // Update the charges after calculating nickels
    int pennies = pennies_charges(cents);
    cents -= pennies * 1; // Update the charges after calculating pennies
    // Print the charges
    printf("The charges are: %iQuarters, %iDimes,  %iNickels, %iPeenies\n", quarters, dimes, nickels, pennies);
    
}

int quarters_charges(int cents)
{
    int quarters = 0;
    while(cents >= 25)
    {
        cents -= 25;
        quarters++;
    }
    return quarters;
}

int dimes_charges(int cents)
{
    int dimes = 0;
    while(cents >= 10)
    {
        cents -= 10;
        dimes++;
    }
    return dimes;
}

int nickels_charges(int cents)
{
    int nickels = 0;
    while(cents >= 5)
    {
        cents -= 5;
        nickels++;
    }
    return nickels;
}

int pennies_charges(int cents)
{
    int pennies = 0;
    while(cents >= 1)
    {
        cents -= 1;
        pennies++;
    }
    return pennies;
}
