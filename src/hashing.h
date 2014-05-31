#ifndef HASH_LENGTH
#define HASH_LENGTH 500009

#ifndef MAX_WORD_LENGTH
#define MAX_WORD_LENGTH 28 // Max length of a word

// Creates a hash index
typedef struct index {
    char element[MAX_WORD_LENGTH];
} Index;

// defines a table of HASH_LENGTH with an index on each position
typedef Index HT[HASH_LENGTH];

int djb2 (char *str);
void new(HT table);
void add(HT table, char word[]);
int exists(HT table, char word[]);
void check(HT table);

#endif
#endif