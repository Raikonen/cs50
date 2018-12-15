/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdlib.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

// Define nodes in the try
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

// Create a starting node pointer named root
node *root;

// Current node pointer for load
node *load_ptr;

// Create node pointer for check
node *check_ptr;

// Create node pointer for unload
node *unload_ptr;

// Create previous node pointer for unload
node *prev_ptr;

// Initialise dictionary word counter
int dic_count;

// Character variable
char *word;



#endif // DICTIONARY_H
