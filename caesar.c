#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int get_key(string argv);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int check_key = get_key(argv[1]);
    if (check_key == 1)
    {
        return 1;
    }
    int key = atoi(argv[1]);
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, s = strlen(plain); i < s; i++)
    {
        if (isalpha(plain[i]))
        {
            if (isupper(plain[i]))
            {
                char LETTER = (plain[i]-'A' + key) % 26 +'A';
                printf("%c", LETTER);
            }
            else
            {
                char letter = (plain[i]-'a' + key) % 26 + 'a';
                printf("%c", letter);
            }
        }
        else
        {
            printf("%c",plain[i]);
        }        
    }
    printf("\n");
    return 0;
}

int get_key(string argv)
{
    for (int i = 0, s = strlen(argv); i < s; i++)
    {
        if (isdigit(argv[i]));
        else
        {   
            printf("Usage: ./caesar key\n");         
            return 1;
        }
    }
    return 0;
}