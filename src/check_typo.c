#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"
#include "typos.h"

HT dictionary;
HTYPO typotable;
int k = 5;
int linha = 0;

/*void is_typo()
{

}*/

void read()
{
	char buf[MAX_WORD_LENGTH];
	while(fgets(buf, MAX_WORD_LENGTH, stdin)){
		char* word;
		word = strtok(buf, " ");
		while(word != NULL) {
			if(word[strlen(word)-1] == '\n'){
				word[strlen(word)-1] = '\0';
				linha ++;
				if(!(word[0] == '\0'))
					//printf("--linha vazia--\n");
				//else
					//handle_word(dictionary, typotable, word, linha);
					printf("<%s>\t| linha %d\n", word, linha);
		}
		else
			//handle_word(dictionary, typotable, word, linha);
			printf("<%s>", word);
		word = strtok(NULL, " ");
		}
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
	/*if(argc == 2){
		k = atoi(argv[1]);
		if(k > MAX_TYPOS)
			k = 100000;
	}*/

	read();

	handle_word(dictionary, typotable, "cOnA", linha);
	int index = djb2("cOnA") % HASH_LENGTH;
	printf("typo: %s\ncount: %s\nlines:", typotable[index].element, typotable[index].count);
	list_print(typotable[index].lines);
	handle_word(dictionary, typotable, "cOnA", linha);

	//check(dictionary);

	return 0;
}
