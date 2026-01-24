#include <stdio.h>
#include <cs50.h>

bool search(node *tree, int number);

typedef struct node
{
    int number;
    struct node *next;
}node;

int main(void)
{
    node *tree = NULL;
    int n = get_in("Number: ");
    bool b = search(tree, n);
    if (b = false)
    {
        printf("No found.\n");
    }
    else
    {
        printf("Found.\n");
    }

}

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else if (number == tree->number)
    {
        return ture;
    }
}