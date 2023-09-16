// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;
unsigned int NUMBER_OF_WORDS = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *temp = table[index];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word,word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for(int j = 0; word[j] != '\0'; j++)
    {
        sum += tolower(word[j]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // opening file to read
    unsigned int index;
    FILE *inputfile = fopen(dictionary, "r");
    if (inputfile == NULL)
    {
        return false;
    }

    char word[1024];
    while(fscanf(inputfile, "%s",word) != EOF)
    {
        // create memory to store words.
        node *ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            fclose(inputfile);
            return false;
        }
        // copy string into memory and get index of hash table
        strcpy(ptr->word,word);
        index = hash(ptr->word);

        // insert node in hash table
        ptr->next = table[index];
        table[index] = ptr;
        NUMBER_OF_WORDS++;
    }
    fclose(inputfile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return NUMBER_OF_WORDS;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate over table. for each node in table, iterate over links and free their memory
    for (int i = 0; i < N; i++)
    {
        node *temp, *cursor;
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
