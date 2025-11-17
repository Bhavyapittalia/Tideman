#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // here i am checking that is there are 2 arguments or not
    if (argc != 2)
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }

    // so by running one foe loop we are doing three task here
    // 1) avoiding digits & special char 2) checking length 3) if satisfy both upper conditions then convert it into uppercase ifthey are on lowercase
    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./subsitution key\n");
            return 1;
        }

        // if(strlen(argv[1]) != 26)
        if(length != 26)
        {
            printf("There must be an 26 character\n");
            return 1;
        }

        if (islower(argv[1][i]))
        {
            argv[1][i] =toupper(argv[1][i]);
        }
    }

    // now checking is there any repeated characters are there or not
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        for(int j = i + 1; j < strlen(argv[1]); j++) // if here we put j = i then it will print that every characters are repeating bcz i and j both index will be same so we have to do j = i + 1
        {
              if(argv[1][i] == argv[1][j])
              {
                printf("Repeated Character are not allowed\n");
                return 1;
              }
        }
    }

    // now converting into cipher text
    string Plain_Text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i <= strlen(Plain_Text) - 1; i++)
    {
        int Aplha_Value = Plain_Text[i];

        if (isalpha(Aplha_Value) && isupper(Aplha_Value))
        {
            // argv[1][i] = isupper(argv[1][i]);
            printf("%c", argv[1][Plain_Text[i] - 'A']);
        }
        if (isalpha(Aplha_Value) && islower(Aplha_Value))
        {
            printf("%c", argv[1][Plain_Text[i] - 'a'] + 32);
        }
        if (!isalpha(Aplha_Value))
        {
            printf("%c", Aplha_Value);
        }
    }
    printf("\n");
}
