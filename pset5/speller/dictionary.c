/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Initialise check pointer to the root
    check_ptr= root;

    // Iterate through the characters in the word
    for (int j=0; j<strlen(word); j++)
    {
        //Store the character in temp
        char temp = word[j];

        if (temp=='\'')
        {
            check_ptr= check_ptr -> children[26];
        }
        else
        {
            // Character is an uppercase alphabet
            if (temp >= 'A' && temp <= 'Z')
            {
            // Convert to lowercase
            temp = temp + 32;
            }
        // Convert the alphabet into an integer i with the corresponding number (A=0, B=1 ... Z=25)
        int k = temp - 'a';
        check_ptr= check_ptr -> children[k];
        }
        // Check if NULL
        if (check_ptr==NULL)
        {
            return false;
        }
    }

    if (check_ptr -> is_word)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // Open file and check for errors
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open the dictionary file.\n");
        return false;
    }

    // Allocate memory for root
    root= calloc(1, sizeof(node));
    load_ptr= root;

    // Iterate through dictionary until EOF
    int c;
    dic_count=0;
    while ((c = fgetc(fp)) != EOF)
    {
        // Character is an alphabet (assuming lowercase)
        if (c >= 97 && c <= 122)
        {
            // Convert the alphabet into an integer i with the corresponding number (A=0, B=1 ... Z=25)
            int i = c - 'a';

            // Check if there is already a node at the address, if not, create a node at that location and allocate it the required memory
            if (load_ptr -> children[i] == NULL)
            {
                load_ptr -> children[i]= calloc(1, sizeof(node));
                // Check if malloc was successfull
                if (load_ptr -> children[i] == NULL)
                {
                    fprintf(stderr, "Malloc Error");
                    return 1;
                }
                load_ptr= load_ptr -> children[i];
            }
            else
            {
                load_ptr= load_ptr -> children[i];
            }
        }
        // Else if the character is an apostrophe, check if the 26th children is null, if it isn't, allocate a node.
        else if (c=='\'')
        {
            // Check if there is already a node at the address, if not, create a node at that location and allocate it the required memory
            if (load_ptr -> children[26] == NULL)
            {
                load_ptr -> children[26]= calloc(1, sizeof(node));
                // Check if malloc was successfull
                if (load_ptr -> children[26] == NULL)
                {
                    fprintf(stderr, "Malloc Error");
                    return 1;
                }
            }
            load_ptr = load_ptr -> children[26];
        }
        else
        {
        // Set load pointer to true
        load_ptr -> is_word=true;
        // Increase dictionary count
        dic_count++;
        // Reset load pointer
        load_ptr = root;
        }
    }

    // Close file pointer
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dic_count !=0)
    {
        return dic_count;
    }
    return 0;
}

// Clean
void freeit (node *ptr)
{
    // Iterate over the children
    for(int i = 0; i < 27; i++)
    {
        // If node has children
        if(ptr->children[i] != NULL)
        {
            // Call recursively
            freeit (ptr->children[i]);
        }
    }
    free(ptr);

}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // Create a node pointer 'curr' to point to the first node
    unload_ptr = root;

    freeit(unload_ptr);

    return true;

}
