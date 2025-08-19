#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string t);
int count_words(string t);
int count_sentences(string t);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = ((float) letters / (float) words) * 100.0;
    float S = ((float) sentences / (float) words) * 100.0;

    // Compute the Coleman-Liau index
    float index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // Print the grade level
    if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) (index));
    }
}

int count_letters(string t)
{
    int counter = 0;
    // Return the number of letters in text
    for (int i = 0, len = strlen(t); i < len; i++)
    {
        if ((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z'))
        {
            counter += 1;
        }
    }
    return counter;
}
int count_words(string t)
{
    int counter = 0;
    // Return the number of words in text
    for (int i = 0, len = strlen(t); i < len; i++)
    {
        if (isspace(t[i]) || t[i] == '\0')
        {
            counter += 1;
        }
    }
    return (counter + 1);
}
int count_sentences(string t)
{
    int counter = 0;
    // Return the number of sentences in text
    for (int i = 0, len = strlen(t); i < len; i++)
    {
        if (t[i] == '!' || t[i] == '.' || t[i] == '?')
        // if (!isalpha (t[i]) || !isalnum (t[i]))
        {
            counter += 1;
        }
    }
    return counter;
}
