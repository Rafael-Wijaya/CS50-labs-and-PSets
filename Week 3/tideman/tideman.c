#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool create_cycle(int pointer, int pointed);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check through the candidates array for matching name
    // If it match, record the candidates index in ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Record voters preferences in preferences array from rank 1 (0) to the last rank
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Check through the preferences array
    // If more voters prefer candidate i over candidate j, i is the winner, j is the loser
    // If more voters prefer candidate j over candidate i, i is the loser, j is the winner
    // Add the pair to the pairs array
    // Pairs who tied are not added to the pairs array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort pairs array with selection sort
    // Find a pair with the highest strength of victory
    // Swap the pair with the first pair

    int current_strength, next_strength, max_index;

    // Finding the index with the largest strength of victory
    for (int i = 0; i < pair_count - 1; i++)
    {
        max_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            current_strength = preferences[pairs[max_index].winner][pairs[max_index].loser] -
                               preferences[pairs[max_index].loser][pairs[max_index].winner];
            next_strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (next_strength > current_strength)
            {
                max_index = j;
            }
        }

        // Swap pairs
        pair temp = pairs[i];
        pairs[i] = pairs[max_index];
        pairs[max_index] = temp;
    }
    return;
}

// Check if a pair will create a cycle
bool create_cycle(int pointer, int pointed)
{
    // if a source (pointer) is pointed, it will create a cycle
    if (pointer == pointed)
    {
        return true;
    }

    // Check if a pointed candidate also point to another candidate
    // If it is, check if the pointed candidate point to the source (pointer)
    for (int i = 0; i < candidate_count; i ++)
    {
        if (locked[pointed][i])
        {
            if (create_cycle(pointer, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Check through the sorted pairs array
    // Using create_cycle function, check if a pair will create a cycle
    // If it is, break but continue the loop (continue)
    // If not, the winner point to the loser (locked[winner][loser] = true)
    for (int i = 0; i < pair_count; i++)
    {
        if (create_cycle(pairs[i].winner, pairs[i].loser))
        {
            continue;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Check through the candidate array
    // If the candidate is not pointed by another candidate, print that candidate as the winner
    for (int i = 0; i < candidate_count; i++)
    {
        bool pointed = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                pointed = true;
            }
        }

        if (!pointed)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}