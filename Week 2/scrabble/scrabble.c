#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Check which player has more points and print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    // TODO: Print the winner
}

int compute_score(string word)
{
    // Variabel to count the score
    int score = 0;

    // Iterate through every characters of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // Check whether the character is an alphabet or not
        if (isalpha(word[i]) != 0)
        {
            // Change the character to uppercase and add the points to the score
            char upperChar = toupper(word[i]);
            score += POINTS[upperChar - 65];
        }

        // If the character is not an alphabet add zero to the score
        else
        {
            score += 0;
        }
    }
    return score;
}
