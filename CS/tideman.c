#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
} pair;

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
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

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

    // storing an candidates name here
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
        int ranks[candidate_count]; // we are creating an ranks[] for each voters here so if we have
                                    // 3 voters then there will be an 3 ranks[] array....

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // here ranks[rank] is like ranks[0],rank[1],ranks[2] bcz we passed afn
                             // "j" as a parameter here
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks

// here is the logic of upcoming function that how it is going to work

/*  suppose rank[] = {bob,alice,charlie}
    then rank[0] = "bob" and so on for all

    now loop logic:-
    (outer loop) we are running our outer loop from  0 to candiadte_count here it is 3

    (inner loop) is going to run from i + 1 to candidate_count
    now why not from 0 bcz if we run from 0 then preferences will check all the preferences[0][0]
   [0][1] [0][2] [1][0] [1][1] and so on... and also we dont need to check index which are beside
   from our current i means if rank[] ={bob(0) ,alice(1),charlie(2)} if i = 1 then it does not
   require to check 1=1 as 1 is prefered over 2 but not 0 and 1

    here preferences[0][1]++ means we get that bob is prefered higher then alice
    so bob will get 1 point

    here we dont need to compare bob with alice & charlie as we know that it is "FIXED" that index 0
   means bob is always prefered higher then index 1 & 2
*/
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            printf("I: %d, J: %d of %d\n", i, j, ranks[j]);
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            if (preferences[j][i] > preferences[i][j])
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
    // TODO
    // "SELECTION SORT"

    for (int i = 0; i < pair_count; i++)
    {
        int strongest_pair = preferences[pairs[i].winner][pairs[i].loser] -
                             preferences[pairs[i].loser][pairs[i].winner];
        int strongest_index = i;

        for (int j = i + 1; j < pair_count; j++)
        {
            int current_pair = preferences[pairs[j].winner][pairs[j].loser] -
                               preferences[pairs[j].loser][pairs[j].winner];
            if (strongest_pair < current_pair)
            {
                strongest_pair = current_pair;
                strongest_index = j;
            }
        }

        if (strongest_index != i)
        {
            pair temp = pairs[i];
            pairs[i] = pairs[strongest_index];
            pairs[strongest_index] = temp;
        }
    }

    // "BUUBLE SORT"

    // for (int i = 0; i < pair_count; i++)
    // {
    //     for (int j = 0; j < pair_count - i - 1; j++)
    //     {
    //         int current_pair = preferences[pairs[j].winner][pairs[j].loser] -
    //         preferences[pairs[j].loser][pairs[j].winner]; int upcoming_pair = preferences[pairs[j
    //         + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j +
    //         1].winner]; if (current_pair < upcoming_pair)
    //         {
    //             pair temp = pairs[j];
    //             pairs[j] = pairs[j + 1];
    //             pairs[j + 1] = temp;
    //         }
    //     }
    // }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        // bool not_cycle = false;
        if (cycle(pairs[i].winner, pairs[i].loser) == false) // here we call a cycle function and check that is any pair is there which creates cycle if not means "false" then only locked pair to "true"
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true; // setting by default value that winner is always true
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner == true)
        {
            printf("%s\n",candidates[i]);
        }
    }

}

bool cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (cycle(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false; // if our programme return false then we are safe to locked the pair and if it return true then the current pair will be skiped
}
