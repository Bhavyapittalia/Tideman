#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes

    // TIPS TO THINK HERE IS :- "ALWAYS LOOK AT OUR PROGRAMME "LINE BY LINE" WHEN WE DONT UNDERSTAND
    // THAT HOW IT IS WORKING...SO THIS IS THE BEST KEY TO FIND AND UNDERSTANDING THE PROBLEM"

    for (int i = 0; i < voter_count; i++)
    {
        // here voter = i which is (voter_count and its value is "2" for example)
        // AND "i" MEANS (voter_count which is "outer loop")

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // here rank = j  which is (candiate_count and its value is "3" for example)
            // AND "j" MEANS (candidate_count which is "inner loop")

            // if our vote() return true means found valid vote then from here it will be "CALL
            // AGAIN FREASHLY" the vote()

            // means we will call an "vote()" total 6 times here as 2*3 = 6

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                // here "i" -> voter -> that we send as a parameter there
                // and  "j" -> rank  -> that we send as a parameter there
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)  // its an infinate loop and it will stop when someone inside from the loop tell it to stop running it
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            // printf("%d\n", preferences[voter][rank]);
            return true;

            // here is the brief explanation that how this loop is working

            /*1) i = 0
              2) strcmp "alice","bob" <- supposing first preference is bob
              3) Not matched

              4) then i = 1
              5) strcmp  "bob" , "bob"
              6) Matched
              7) preferences[voter][rank] = 1
              8) return true "loop gets over here"

            ===  now again "fresh loop" will start by calling from "main()" ===

              1) i = 0
              2) strcmp "alice","charlie" <- suppsing second pref..
              3) Not matched

              4) Then i = 2
              5) "bob","charlie"
              6) Not matched

              7) Then i = 3
              8) "charlie,"charlie"
              9)  Matched
              10) preferences[voter][rank] = 3
              11) return true and again loop will be terminated
            */
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
   for (int i = 0; i < candidate_count; i++)
   {
       if(candidates[i].votes > voter_count / 2)
       {
          printf("%s\n",candidates[i].name);
          return true;
       }
   }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minimum_vote = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < minimum_vote)
        {
            minimum_vote = candidates[i].votes;
        }
    }
    return minimum_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && min != candidates[i].votes)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
