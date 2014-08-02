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

/* Cria uma nova tabela de hash e preenche os elementos de todas
 * as posições com uma palavra vazia.
 * @param table tabela de hash a ser preenchida
 */
void new(HT table)
{
	for(int i = 0; i < HASH_LENGTH; i++)
		table[i].element[0] = '\0';
}

/* Faz hash à palavra e guarda-o na tabela de hash, incrementa
 * 1 na sua contagem e adiciona a linha correspondente.
 * param table tabela de hash das palavras
 * param word palavra a ser adicionado
 */
void add(HT table, char word[])
{
	int index = djb2(word) % HASH_LENGTH;

	if(index < 0)
    	index = index * -1;

    while(table[index].element[0] != '\0')
    	index++;

	strcpy(table[index].element, word);
}

/* Verifica se uma palavra existe na tabela
 * param table tabela de hash das palavras
 * param word palavra a ser verificada
 * @return 1 se o erro já existe, 0 se não existe
 */
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
	while(strcmp(table[index].element, "") != 0 && strcmp(table[index].element, word) != 0){
		index++;
		if(index == HASH_LENGTH)
			index = 0;
	}

	// if table[index].element == word, the word exists
	if(!strcmp(table[index].element, word))
		return 1;

	return 0;
}
