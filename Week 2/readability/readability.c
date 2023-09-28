#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float coleman_liau_index(float letters, float words, float sentences);

int main(void)
{

    string inputText = get_string("Text: ");
    int letters = count_letters(inputText);
    int words = count_words(inputText);
    int sentences = count_sentences(inputText);
    int grade = coleman_liau_index(letters, words, sentences);
    if (grade < 2)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

int count_letters(string text)
{
    // Make a letter counter
    int letterCounter = 0;

    // Iterate through every characters
    for (int i = 0; i < strlen(text); i++)
    {
        // Check whether the character is an alphabet or not and add 1 to the counter if it is
        if (isalpha(text[i]) != 0)
        {
            letterCounter++;
        }
    }
    return letterCounter;
}

int count_words(string text)
{
    // Make a word counter
    // Start at 1 because the last word of the text doesn't end with a whitespace
    int wordCounter = 1;

    // Iterate through every characters
    for (int i = 0; i < strlen(text); i++)
    {
        // Check for whitespaces and add 1 to the counter
        if (isspace(text[i]) != 0)
        {
            wordCounter++;
        }
    }
    return wordCounter;
}

int count_sentences(string text)
{
    // Make a sentence counter
    int sentenceCounter = 0;

    // Iterate through every characters
    for (int i = 0; i < strlen(text); i++)
    {
        // Check for period, exclamation point, or question mark and add 1 to the counter
        if (text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentenceCounter++;
        }
    }
    return sentenceCounter;
}

float coleman_liau_index(float letters, float words, float sentences)
{
    // Calculate how many letters per 100 words
    float L = letters / words * 100.0;

    // Calculate how many sentences per 100 words
    float S = sentences / words * 100.0;

    // Calculate readability using Coleman-Liau index formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Adding 0.5 so that it rounded to the nearest integer
    return index + 0.5;
}