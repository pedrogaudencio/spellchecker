#include "linkedlist.h"
#include "hashing.h"

#ifndef MAX_TYPOS
#define MAX_TYPOS 100000

// Creates a hash typo index
typedef struct typoindex {
    char element[MAX_WORD_LENGTH];
    char count[7];
    struct list* lines;
} TypoIndex;

// defines a table of HASH_LENGTH with an index on each position
typedef TypoIndex HTYPO[HASH_LENGTH];

void new_typotable(HTYPO table);
int get_typos_found();
int exists_typo(HTYPO table, char typo[]);
void add_typo(HTYPO table, char typo[], char line[]);
void handle_word(HT table, HTYPO typo_table, char word[], int line);

#endif