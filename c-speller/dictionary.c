// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
unsigned int word_count = 0;

const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';

    int index = hash(temp);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        // if (strcasecmp(cursor->word, temp) == 0)
        // {
        //     return true;
        // }
        // Create lowercase copies of both strings
        char dict_word_lower[LENGTH + 1];
        int len_word = strlen(cursor->word);
        for (int i = 0; i < len_word; i++)
        {
            dict_word_lower[i] = tolower(cursor->word[i]);
        }
        dict_word_lower[len_word] = '\0';

        // Compare lowercase versions
        if (strcmp(dict_word_lower, temp) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    if (isalpha(word[0]))
    {
        return toupper(word[0]) - 'A';
    }
    else
    {
        return 0;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }

    strcpy(n->word, word);
    int index = hash(word);

    // Insert into linked list at the hash index
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
