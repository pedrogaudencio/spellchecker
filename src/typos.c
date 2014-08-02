#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashing.h"
#include "typos.h"
#include "linkedlist.h"

int typos_found = 0;

/* Cria uma nova tabela e preenche-a com '\0'
 * @param table tabela de hash de erros
 */
void new_typotable(HTYPO table)
{
	for (int i = 0; i < TYPOHASH_LENGTH; i++){
		table[i].element[0] = '\0';
		table[i].count = 0;
    	table[i].lines = list_new();
	}
}

/* Acede à variável local typos_found
 * @return número de erros encontrados até ao momento
 */
int get_typos_found()
{
	return typos_found;
}

/* Verifica se um erro já existe na tabela
 * param table tabela de hash dos erros
 * param typo erro a ser verificado
 * @return o índice do erro se existe, -1 se não existe
 */
int exists_typo(HTYPO table, char typo[])
{
	int index = djb2(typo) % TYPOHASH_LENGTH;

	// abs(index)
	if(index < 0)
		index *= -1;

	// if the position has '\0', the word doesn't exist
	if(table[index].element[0] == '\0'){
		return -1;
	}

	// checks every index until the end of the table
	while(strcmp(table[index].element, "") != 0 && strcmp(table[index].element, typo) != 0){
		//printf("%d %s\n", index, table[index].element);
		index++;
		if(index == TYPOHASH_LENGTH){
			index = 0;
		}
	}

	// if table[index].element == word, the word exists
	if(strcmp(table[index].element, typo)==0)
		return index;

	return -1;
}

/* Faz hash ao erro e guarda-o na tabela de hash, incrementa
 * 1 na sua contagem e adiciona a linha correspondente.
 * param table tabela de hash dos erros
 * param typo erro a ser adicionado
 * param line linha correspondente ao erro
 */
void add_typo(HTYPO table, char* typo, int line)
{
	int index = djb2(typo) % TYPOHASH_LENGTH;

	if(index < 0)
    	index *= -1;

    int check = exists_typo(table, typo); // -1 se não existe, index se existe

    // se existir, modifica
    if(check >= 0){
    	table[check].count++;

		if(list_length(table[check].lines) < 50){
			list_insert(table[check].lines, line);
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

/* Transforma todas as letras de uma palavra em lowercase.
 * param word palavra a ser transformada
 * param w palavra lowercase com o valor de word
 */
void to_lowercase(char word[], char w[])
{
	int s = strlen(word);
	for(int i = 0; i < s; i++)
		w[i] = tolower(word[i]);

	w[s] = '\0';
}

/* Trata de um possível erro. Se a palavra não existe,
 * verifica se todas as letras em lowercase também não
 * existem - se isto se verificar, adiciona-a como erro.
 * param table tabela de hash com o dicionario
 * param typo_table tabela de hash com os erros
 * param word palavra a ser verificada
 * param line linha correspondente à palavra
 */
void handle_word(HT table, HTYPO typo_table, char word[], int line)
{
	//printf("<%s>", word);
	if(!exists(table, word)){
		char w[MAX_WORD_LENGTH];
		to_lowercase(word, w);
		//printf("lower: %s\n", word);
		if(!exists(table, w)){
			add_typo(typo_table, word, line);
			typos_found++;
		}
	}
}