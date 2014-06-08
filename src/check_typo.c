#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"
#include "typos.h"

HT dictionary;
HTYPO typotable;
int k = 5, linha = 1;

// http://pt.wikipedia.org/wiki/Quick_sort#C.2FC.2B.2B
void quickSort(TypoIndex valor[], int esquerda, int direita)
{
	int i, j, x;
	TypoIndex y;
	i = esquerda;
	j = direita;
	x = valor[(esquerda + direita) / 2].count;
 
	while(i <= j)
	{
		while(valor[i].count < x && i < direita)
			i++;
		while(valor[j].count > x && j > esquerda)
			j--;
		if(i <= j) {
			y = valor[i];
			valor[i] = valor[j];
			valor[j] = y;
			i++;
			j--;
			/*if(valor[i].count == valor[j].count){
				if(strcmp(valor[i].element, valor[j].element)<0){
					y = valor[i];
					valor[i] = valor[j];
					valor[j] = y;
					i++;
					j--;
				} else {
					y = valor[j];
					valor[j] = valor[i];
					valor[i] = y;
					j++;
					i--;
				}
			} else {*/
			//}
		}
	}
	if(j > esquerda)
		quickSort(valor, esquerda, j);
	if(i < direita)
		quickSort(valor,  i, direita);
}

void read()
{
	char buf[100000];
	int typos_found = 0;
	while(typos_found <= k && fgets(buf, 100000, stdin)){
		char word[MAX_WORD_LENGTH];
		int wi = 0;
		for(int i = 0; i<=100000; i++){
			if(buf[i]=='\n'){
				linha++;
				//printf("%s\n", word);
				break;
			}
			word[wi] = buf[i];
			wi++;
			if(buf[i] == ' '){
				word[wi-1] = '\0';
				//printf("%s\n", word);
				handle_word(dictionary, typotable, word, linha);
				for(int i = 0; i<=MAX_WORD_LENGTH; i++)
					word[i] = '\0';
				wi=0;
			}
		}
		typos_found = get_typos_found();
	}
}

// loads database stored in disk
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

	// checks if k is given as a parameter
	if(argc == 2){
		k = atoi(argv[1]);
		if(k > MAX_TYPOS)
			k = 100000;
	}

	read();
	quickSort(typotable, 0, TYPOHASH_LENGTH);

	for(int i = 0; i < TYPOHASH_LENGTH; ++i){
		if(typotable[i].count != 0){
			printf("%s (%d) ", typotable[i].element, typotable[i].count);
			list_print(typotable[i].lines);
			printf("\n");
		}
	}

	return 0;
}
