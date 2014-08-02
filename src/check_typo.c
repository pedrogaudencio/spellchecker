#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"
#include "typos.h"

HT dictionary;
HTYPO typotable;
int k = 5, linha = 1;

/* Algoritmo para comparar na ordenação da Hashtable de erros
 * por contagem decrescente e lexicograficamente.
 * Baseado em http://www.cplusplus.com/reference/cstdlib/qsort/
 * @param a primeiro elemento
 * @param b segundo elemento
 * @return qual dos elementos será primeiro
 */
int compare(const void* p1, const void* p2)
{
	const TypoIndex *typo1 = p1;
    const TypoIndex *typo2 = p2;

	if(typo1->count == typo2->count)
		return strcmp(typo1->element, typo2->element) < 0;
	else
		return typo1->count - typo2->count;
}

/* Lê o input do stdin e trunca as palavras a cada espaço ou newline.
 * Caso newline, incrementa 1 no contador global das linhas.
 */
void read()
{
	char buf[100000];
	while(fgets(buf, 100000, stdin)){
		char word[MAX_WORD_LENGTH];
		int wi = 0;
		for(int i = 0; i<=100000; i++){
			if(buf[i]=='\n'){
				word[wi] = '\0';
				//printf("<%s> (newline)\n", word);
				handle_word(dictionary, typotable, word, linha);
				for(int i = 0; i<=MAX_WORD_LENGTH; i++)
					word[i] = '\0';
				wi=0;
				linha++;
				break;
			}
			word[wi] = buf[i];
			wi++;
			if(buf[i] == ' '){
				word[wi-1] = '\0';
				//printf("<%s>\n", word);
				handle_word(dictionary, typotable, word, linha);
				for(int i = 0; i<=MAX_WORD_LENGTH; i++)
					word[i] = '\0';
				wi=0;
			}
		}
	}
}

/* Carrega a base de dados previamente construída e guardada em disco.
 * @param filename nome do ficheiro da base de dados
 */
void load(char *filename)
{
	new(dictionary);
	FILE *fp = fopen(filename, "rb");
	if(fp == NULL) {
		printf("*** error: could not open file %s. exit.\n", filename);
		exit(1);
	}

	for (int i = 0; i < HASH_LENGTH; ++i)
		fread(&dictionary[i].element, sizeof(char)*MAX_WORD_LENGTH, 1, fp);

	fclose(fp);
}


int main(int argc, char **argv)
{
	load("database.bin");
	new_typotable(typotable);

	// verifica se k é dado como argumento
	if(argc == 2){
		k = atoi(argv[1]);
		if(k > MAX_TYPOS)
			k = 100000;
	}

	read();

	if(linha > 2)
		qsort(typotable, TYPOHASH_LENGTH, sizeof(TypoIndex), compare);

	for(int i = TYPOHASH_LENGTH; (k>0 && i>=0); i--){
		if(typotable[i].count != 0){
			printf("%s (%d) ", typotable[i].element, typotable[i].count);
			list_print(typotable[i].lines);
			printf("\n");
			k--;
		}
	}

	return 0;
}
