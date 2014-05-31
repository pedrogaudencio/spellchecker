#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashing.h"
#include "typos.h"
#include "linkedlist.h"

int typos_found = 0;

// creates new hashtable and fills it with '\0'
void new_typotable(HTYPO table)
{
	for (int i = 0; i < HASH_LENGTH; i++){
		table[i].element[0] = '\0';
		table[i].count[0] = '\0';
    	table[i].lines = list_new();
	}
}

int get_typos_found()
{
	return typos_found;
}

// returns 1 if exists and 0 if not
int exists_typo(HTYPO table, char typo[])
{
	int index = djb2(typo) % HASH_LENGTH;

	// abs(index)
	if(index < 0)
		index *= -1;

	// if the position has '\0', the word doesn't exist
	if(table[index].element[0] == '\0'){
		return 0;
	}

	// checks every index until the end of the table
	while(strcmp(table[index].element, typo) != 0){
		//printf("%d %s\n", index, table[index].element);
		index++;
		if(index == HASH_LENGTH)
			return 0;
	}

	// if table[index].element == word, the word exists
	if (!strcmp(table[index].element, typo))
		return 1;

	else return 0;
}

// hashes the word and puts it in table[hash]
void add_typo(HTYPO table, char* typo, char line[])
{
	int index = djb2(typo) % HASH_LENGTH;

	if(index < 0)
    	index *= -1;

    // se existir, modifica
    if(exists_typo(table, typo)){
    	int c = atoi(table[index].count);
    	c++;
		sprintf(table[index].count, "%d\n", c);
		if(list_length(table[index].lines) < 50){
			list_insert(table[index].lines, line);
		}
    } // se nao existir, adiciona desta maneira
    else {
	    while(table[index].element[0] != '\0')
	    	index++;

		strcpy(table[index].element, typo);
		sprintf(table[index].count, "%d\n", 1);
		list_insert(table[index].lines, line);
    }
}

char* to_lowercase(char* word)
{
	char c;
	char w[strlen(word)];
	for(int i = 0; word[i]; i++){
		c = word[i];
		w[i] = tolower(c);
	}
	word = w;
	return word;
}

void handle_word(HT table, HTYPO typo_table, char word[], int line)
{
	//printf("normal: %s\n", word);
	if(!exists(table, word)){
		//if(word[0] > )
		char* lword = to_lowercase(word);
		//char lword[strlen(word)];
		//strcpy(lword, to_lowercase(word));
		//printf("lower: %s\n", lword);
		if(!exists(table, lword)){
			char l[7];
			sprintf(l, "%d", line);
			add_typo(typo_table, word, l);
			typos_found++;
		}
	} else 
		printf("all is fine.\n");
}