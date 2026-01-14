#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int check_letters(string text);
int check_words(string text);
int check_sentence(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = check_letters(text);
    int words = check_words(text);
    int sentence = check_sentence(text);
    float L = letters / (words / 100.0);
    float S = sentence / (words / 100.0);
    int l = round(L);//测试四舍五入
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = index * 10 / 1;
    int GRADE = 0;
        printf("letters:%i words:%i sentence:%i l:%i index:%f \n",letters,words,sentence,l,index);//测试
    if (grade % 10 > 4)
    {
        GRADE = grade / 10 + 1;
    }
    else
    {
        GRADE = grade / 10;
    }
    if (1 <= GRADE && GRADE <= 16)
    {
        printf("Grade %i\n",GRADE);
    }
    else if (GRADE > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
    return 0;
}

int check_letters(string text)
{
    int total = 0;
    for (int i = 0, s = strlen(text); i < s; i++)
    {
        char c = text[i];
        if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')
        {
            total = total + 1;
        }
    }
    return total;
}

int check_words(string text)
{
    int total = 1;
    for (int i = 0, s = strlen(text); i < s; i++)
    {
        if (text[i] == ' ')
        {
            total = total + 1;
        }
    }
    return total;
}

int check_sentence(string text)
{
    int total = 0;
    for (int i = 0,s = strlen(text); i < s; i++)
    {
        char c = text[i];
        if (c == '.' || c == '!' || c == '?')
        {
            total = total + 1;
        }
    }
    return total;
}