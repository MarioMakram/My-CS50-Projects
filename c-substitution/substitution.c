#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

void cipher(string key, string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // if key is 26 letters
    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("key must be 26 characters\n");
        return 1;
    }

    for (int x = 0; x < 26; x++)
    {
        if (!isalpha(key[x]))
        {
            printf("key must olny contain alphabetic characters\n");
            return 1;
        }
        for (int y = x + 1; y < 26; y++)
        {
            if (key[x] == key[y] || key[x] == key[y - 32] || key[x] == key[y + 32])
            {   
                printf("key most not contain repeated characters\n");
                return 1;
            }
        }
    }
    
    string plaintext = get_string("Plaintext: ");

    printf("ciphertext: "); 
    cipher(key, plaintext);
    

}

void cipher(string key, string plaintext)
{
    char ci[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (islower(plaintext[i]))
        {
            ci[i] = key[(plaintext[i] - 'a')];
            printf("%c",ci[i]);
        }
        else if (isupper(plaintext[i]))
        {
            ci[i] = key[(plaintext[i] - 'A')];
            printf("%c",ci[i]);
        }
        else
        {
            ci[i] = plaintext[i];
            printf("%c",ci[i]);
        }

    }
}