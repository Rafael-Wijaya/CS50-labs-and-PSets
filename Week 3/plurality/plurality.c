#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Checking through the array of candidates to determine whether the vote is valid or not
    // If valid, add 1 to the vote count and return true
    // If not valid, return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Assume the first element of the candidates array (votes) is the highest number
    int highest_vote = candidates[0].votes;

    // Iterate through the array to find the highest number of votes
    // Check for every elements after the first element of the array.
    // If it is higher than the highest_vote, replace the highest_vote with the current element of the array
    for (int i = 1; i < candidate_count; i++)
    {
        if (highest_vote < candidates[i].votes)
        {
            highest_vote = candidates[i].votes;
        }
    }

    // Iterate through the candidates array
    // Check if the candidate's votes match the highest_vote
    // If it is, the candidate's votes is the highest and print the name of the candidates
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == highest_vote)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}