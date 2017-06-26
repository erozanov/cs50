/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

node* hashtable[HASHSIZE];
unsigned int dictionary_size = 0;

int hash(const char* key)
{
    int weight = 1;
    int result = 0;
    for(int i = 0, n =  strlen(key); i < n; i++)
    {
        result  += key[i] * weight;
        weight++;
    }
    return result % HASHSIZE;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int word_len = strlen(word);
    char word_res[word_len + 1];
    
    for(int i = 0; i < word_len; i++)
    {
        int ch = word[i];
        char result = (ch >= 'A' && ch <= 'Z') ? tolower(ch) : ch; 
        word_res[i] = result;
    }
    word_res[word_len] = '\0';
    
    int hashres = hash(word_res);
    
    if (hashres > HASHSIZE) 
    {
        return false;
    }
    
    node* cursor = hashtable[hashres];
    
    if (cursor == NULL) 
    {
        return false;
    }
    
    //iterator
    while(cursor != NULL)
    {
        if(strcmp(cursor->word, word_res) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* in = fopen(dictionary, "r");
    
    if (in == NULL)
    {
        printf("Could not open dictionary");
        fclose(in);
        return false;
    }
    while (!feof(in))
    {
        node* current = malloc(sizeof(node));
        fscanf(in, "%s\n", current->word);
        //check if string in dictionary exist but it not characters

        int hashres = hash(current->word);
        
        if (hashres > HASHSIZE)
        {
            printf("hash value >  HASHSIZE");
            return false;
        }
        
        if (hashtable[hashres] == NULL)
        {
            hashtable[hashres] = current;
        } else 
        {
            node* head = hashtable[hashres];
            current->next = head;
            hashtable[hashres] = current;
        }
        dictionary_size++;

    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionary_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < HASHSIZE; i++)
    {
        node* cursor = hashtable[i];
        while(cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
