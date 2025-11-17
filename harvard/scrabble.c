#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int checkScore(char word[])
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // now converting lower into upper and vice versa...
        if (isupper(word[i]))
        {
            sum = sum + points[word[i] - 'A'];

            //  if word is "Cat"

            // then "points[word[i] - 'A']" will be calculated like "points['C' - 'A'] and the value
            // will be 2 (according to ASCII VALUE 67(c) - 65(a)) means 2th index of points array
            // whose value is 3 at 2th index so the value of 'c' will be "3" .. and then "points['A'
            // - 'A']" (65-65 = 0) will be 0th index of points array and its value is 1...and then
            // "points['T' - 'A']" will be (95-65 =20) will  be 20th index of points array and its
            // value is 1....

            // so at last 3+1+1 = 5 will be final points

            // here points[] will get its "i" index from "word[i] - A"
        }
        if (islower(word[i]))
        {
            sum = sum + points[word[i] - 'a'];
        }
    }
    return sum;
}

int main()
{

    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    printf("%d\n", checkScore(word_1));
    printf("%d\n", checkScore(word_2));

    if (checkScore(word_1) > checkScore(word_2))
    {
        printf("Player 1 wins !\n");
        return 0;
    }

    if (checkScore(word_1) < checkScore(word_2))
    {
        printf("Player 2 wins !\n");
        return 0;
    }

    if (checkScore(word_1) == checkScore(word_2))
    {
        printf("Tie !!\n");
        return 0;
    }

    return 0;
}
