#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"
#include "typos.h"

int c = 0;

/*
* DJB2 is a fast hash function which also provides
* good uniqueness.
* See http://www.cse.yorku.ca/~oz/hash.html
*/
int djb2 (char *str)
{
    unsigned hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// creates new hashtable and fills it with '\0'
void new(HT table)
{
	for (int i = 0; i < HASH_LENGTH; i++)
		table[i].element[0] = '\0';
}

// hashes the word and puts it in table[hash]
void add(HT table, char word[])
{
	int index = djb2(word) % HASH_LENGTH;

	if(index < 0)
    	index = index * -1;

    while(table[index].element[0] != '\0')
    	index++;

	strcpy(table[index].element, word);
}

// returns 1 if exists and 0 if not
int exists(HT table, char word[])
{
	int index = djb2(word) % HASH_LENGTH;

	// abs(index)
	if(index < 0)
		index *= -1;

	// if the position has '\0', the word doesn't exist
	if(table[index].element[0] == '\0'){
		//printf("empty position\n");
		return 0;
	}

	// checks every index until the end of the table
	while(strcmp(table[index].element, word) != 0){
		//printf("%d %s\n", index, table[index].element);
		index++;
		if(index == HASH_LENGTH)
			return 0;
	}

	// if table[index].element == word, the word exists
	if (!strcmp(table[index].element, word))
		return 1;

	else return 0;
}

// checks if every word was stored correctly
void check(HT table)
{
	printf("checking... ");
	char buf[MAX_WORD_LENGTH];
	FILE *fp = fopen("pt-ao.txt","r");
	if(fp == NULL) {
        printf("*** error: could not open file. exit.\n");
        exit(1);
    }

	while(fgets(buf, MAX_WORD_LENGTH, fp) != NULL)
	{
		strtok(buf, "\n");
		if(exists(table, buf))
			c++;
	}

	printf("%d words.\n", c-1);

	fclose(fp);
}
