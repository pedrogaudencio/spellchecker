#include "linkedlist.h"
#include "hashing.h"

#ifndef TYPOSHASH
#define TYPOSHASH

#ifndef MAX_TYPOS
#define MAX_TYPOS 100000

#ifndef TYPOHASH_LENGTH
#define TYPOHASH_LENGTH 110017

// Creates a hash typo index
typedef struct typoindex {
    char element[MAX_WORD_LENGTH];
    int count;
    struct list* lines;
} TypoIndex;

// defines a table of TYPOHASH_LENGTH with an index on each position
typedef TypoIndex HTYPO[TYPOHASH_LENGTH];

void new_typotable(HTYPO table);
int get_typos_found();
int exists_typo(HTYPO table, char typo[]);
void add_typo(HTYPO table, char typo[], int line);
void handle_word(HT table, HTYPO typo_table, char* word, int line);
char* low(char* word, char* w);

#endif
#endif
#endif