#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_key(string argv);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int check_key = get_key(argv[1]);
    if (check_key == 1)
    {
        return 1;
    }
    string key = argv[1];
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, s = strlen(plain); i < s; i++)
    {
        if (isupper(plain[i]))
        {
            int permutation = plain[i] - 'A';
            if (isupper(key[permutation]))
            {
                printf("%c", key[permutation]);
            }
            else
            {
                printf("%c", key[permutation] - 'a' + 'A');
            }
        }
        else if (islower(plain[i]))
        {
            int permutation = plain[i] - 'a';
            if (isupper(key[permutation]))
            {
                printf("%c", key[permutation] - 'A' + 'a');
            }
            else
            {
                printf("%c", key[permutation]);
            }
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}

int get_key(string argv)
{
    int s = strlen(argv);
    if (s != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < s; i++)
    {
        if (!isalpha(argv[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        for (int n = 0; n < i; n++)
        {
            if (toupper(argv[n]) == toupper(argv[i]))
            {
                printf("key must not contain repeated characters.");
                return 1;
            }
        }
    } 
    return 0;
}