#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void rotate(int k, string pt);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        // printf("%c\n", argv[1][i]);
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);

    string plaintext = get_string("Plaintext: ");

    // string ciphertext = rotate(key, plaintext);

    // printf("plaintext:  %s\n", plaintext);
    printf("ciphertext:  "); rotate(key, plaintext);

}


void rotate (int k, string pt)
{
    char ci[strlen(pt)];
    for (int i = 0, len = strlen(pt); i < len; i++)
    {
        if (islower(pt[i]))
        {
            ci[i] = (char) ((int) (pt[i] - 'a') + k) % 26 + (int) 'a';
            printf("%c",ci[i]);
        }
        if (isupper(pt[i]))
        {
            ci[i] = (char) ((int) (pt[i] - 'A') + k) % 26 + (int) 'A';
            printf("%c",ci[i]);
        }
        if (!isalpha(pt[i]))
        {
            ci[i] = pt[i];
            printf("%c",ci[i]);
        }
    }
}