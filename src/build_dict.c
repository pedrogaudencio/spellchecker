#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"

HT dictionary;

// reads words from file and adds them to the dictionary
void read(HT dictionary)
{
	char buf[MAX_WORD_LENGTH];

	while(fgets(buf, MAX_WORD_LENGTH, stdin) != NULL){
        strtok(buf, "\n");
        add(dictionary, buf);
    }
}

// writes dictionary to disk
void write(char *filename)
{
  FILE *file = fopen(filename, "wb");

  for (int i = 0; i < HASH_LENGTH; ++i)
  {
  	fwrite(&dictionary[i].element, sizeof(char)*MAX_WORD_LENGTH, 1, file);
  }
  
  fclose(file);
}

int main()
{
	new(dictionary);
	read(dictionary);

	write("database.bin");

	return 0;
}
