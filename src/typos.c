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
	for (int i = 0; i < TYPOHASH_LENGTH; i++){
		table[i].element[0] = '\0';
		table[i].count = 0;
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
	int index = djb2(typo) % TYPOHASH_LENGTH;

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
		if(index == TYPOHASH_LENGTH)
			return 0;
	}

	// if table[index].element == word, the word exists
	if (!strcmp(table[index].element, typo))
		return 1;

	else return 0;
}

// hashes the word and puts it in table[hash]
void add_typo(HTYPO table, char* typo, int line)
{
	int index = djb2(typo) % TYPOHASH_LENGTH;

	if(index < 0)
    	index *= -1;

    // se existir, modifica
    if(exists_typo(table, typo)){
    	table[index].count++;

		if(list_length(table[index].lines) < 50){
			list_insert(table[index].lines, line);
		}
    } // se nao existir, adiciona desta maneira
    else {
	    while(table[index].element[0] != '\0'){
	    	index++;

		    if(index == TYPOHASH_LENGTH)
		    	index = 0;
		}

		strcpy(table[index].element, typo);
		table[index].count++;
		list_insert(table[index].lines, line);
    }
}

// TODO: mudar isto para devolver nova palavra em vez de alterar a recebida
void to_lowercase(char* word)
{
	for(int i = 0; i < strlen(word); i++){
		//printf("%c\n", word[i]);
		word[i] = tolower(word[i]);
	}
}

/*void to_lowercase(char* word, char* w)
{
	for(int i = 0; i < strlen(word); i++)
		w[i] = tolower(word[i]);

	w[strlen(word)] = '\0';
}*/

// 
void handle_word(HT table, HTYPO typo_table, char* word, int line)
{
	//printf("normal: %s\n", word);
	if(!exists(table, word)){
		//char* lword = to_lowercase(word);
		to_lowercase(word);
		//printf("lower: %s\n", word);
		if(!exists(table, word)){
			add_typo(typo_table, word, line);
			typos_found++;
		}
	}
}