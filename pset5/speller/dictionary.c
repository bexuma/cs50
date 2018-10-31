// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

FILE *dict;

typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict = fopen(dictionary, "r");

    if (!dict)
    {
        return false;
    }

    node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        unload();
        return false;
    }
    head->next = NULL;

    node hashtable[26][10000];

    char word[LENGTH + 1];

    int bucket = 0;

    int index = 0;

    while (fscanf(dict, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        // checking if there is any space left for malloc-ing that many bytes (do check after any malloc)
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(new_node->word, word);
        new_node->next = head;

        head = new_node;

        if (word[0] - 97 == bucket)
        {
            index++;
        }
        else
        {
            bucket++;
            index = 0;
        }


        hashtable[bucket][index] = *new_node;

        printf("%s \n", hashtable[0][1].word);
        // printf("%s \n", hashtable[0][2]->word);
        // printf("%s \n\n", hashtable[0][3]->word);

    }

    return true;
}

// // Returns true if word is in dictionary else false
// bool check(const char *word)
// {
//     char first_c = word[0];

//     return false;
// }

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int n = 0;
    char c;

    while(!feof(dict))
    {
        c = fgetc(dict);
        if(c == '\n')
        {
            n++;
        }
    }

    return n;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (dict)
    {
        fclose(dict);
    }

    return true;
    // return false;
}
