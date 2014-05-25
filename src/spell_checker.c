#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//#include <mpi.h>

#define MAX_WORD_LENGTH 29

int get_indices2 (FILE *fp, int *indices)
{
    int count = 0;
    char buf[255], letter = 'a';

	indices[0] = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%s",buf);
		indices[(int)buf[0] - ((int)buf[0] > 96 ? 97 : 65) + 1] += 1;   //small or capital letter
        count++;
    }

	indices[26] -= 1;	//last word in dictionnary is read twice for some reasons...;

	int ii;
	for(ii=2; ii<27; ii++)
	{
		indices[ii] += indices[ii-1];	//get the starting index for every letter by adding the words for every previous letter to the current one;
	}                                   //first entry: 0, last entry: number of words;

    return count-1;
}

void fill_array (FILE *fp, int *indices, char *words, const int nwords)
{
    char buf[MAX_WORD_LENGTH];
	int *positions = (int*)calloc(26,sizeof(int)), flag = 0;    //saves the current writing position for every letter;

	int ii;
    for(ii=0; ii<nwords; ii++)
    {
        fscanf(fp,"%s",buf);
		flag = (indices[(int)buf[0] - ((int)buf[0] > 96 ? 97 : 65)] + positions[(int)buf[0] - ((int)buf[0] > 96 ? 97 : 65)]) * MAX_WORD_LENGTH;
        strcpy(&(words[flag]),buf);
		positions[(int)buf[0] - ((int)buf[0] > 96 ? 97 : 65)] += 1;
    }

    return;
}

int check_for_typo (char *words, int *indices, char *typo)
{
    int istypo = 1, id = (int)typo[0]-((int)typo[0] > 96 ? 97 : 65);

	int ii;

	if((int)typo[0] < 65 || (int)typo[0] > 122 || ((int)typo[0] > 90 && (int)typo[0] < 97)) //first char not a letter;
    {
        return 1;
    }

	for(ii=indices[id]; ii<indices[id+1]; ii++)
	{
		if( !strcmp( &(words[ii*MAX_WORD_LENGTH]), typo) ) {
			istypo = 0;
			break;
		}
	}

    return istypo;
}

void write_tree_to_file (const char *filename)
{
	FILE *fp = fopen(filename,"wb");

	fclose(fp);

	return;
}

void read_tree_from_file (const char *filename)
{
	FILE *fp = fopen(filename,"rb");
	if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n",filename);
        return;
    }

	return;
}

void pick_random_words (const char *filename, char **testwords, const int howmany, const int treesize)
{
	FILE *fp = fopen(filename,"r");
	if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n",filename);
        return;
    }

	int ii, jj, line;
	char buf[255];
	for(ii=0; ii<howmany; ii++)
	{
		fseek(fp,0,SEEK_SET);
		line = rand() % treesize + 1;
		for(jj=0; jj<line; jj++)
		{
			fscanf(fp,"%s",buf);
		}
		strcpy(testwords[ii],buf);
	}
	fclose(fp);

	return;
}

int main (int argc, char **argv)
{
	//MPI_Init(&argc,&argv);

	srand(time(NULL));

    char *filename = "pt-ao.txt";
	//double time = MPI_Wtime();
	int *indices = (int*)calloc(27,sizeof(int));	//saves the starting index for every letter + the number of words in the last entry;

    FILE *fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n",filename);
        return -1;
    }

    int nwords = get_indices2(fp,indices);
    char *words = (char*)calloc(nwords*MAX_WORD_LENGTH,sizeof(char));

	rewind(fp);
    fill_array(fp,indices,words,nwords);

	fclose(fp);

	//printf("%2.3lf sec. for initialisation.\n",MPI_Wtime()-time);

	int ii;
	/*
	for(ii=0; ii<27; ii++)
	{
		printf("indices[%d] = %d\n",ii,indices[ii]);
	}
	*/


	int howmany = 1000;
	char **testwords = (char**)calloc(howmany,sizeof(char*));
	for(ii=0; ii<howmany; ii++)
	{
		testwords[ii] = (char*)calloc(32,sizeof(char));
	}

	pick_random_words(filename,testwords,howmany,nwords);

	//time = MPI_Wtime();

	int ntypos = 0;
	for(ii=0; ii<howmany; ii++)
	{
		ntypos += check_for_typo(words,indices,testwords[ii]);
	}
	ntypos += check_for_typo(words,indices,"abcdefg");
	ntypos += check_for_typo(words,indices,"BLABLA");
	ntypos += check_for_typo(words,indices,"ichunddu");

	//printf("%2.3lf words per sec. checked.\n",(double)howmany/(MPI_Wtime()-time));
	printf("crosscheck: ntypos = %d\n",ntypos);

	//MPI_Finalize();

    return 0;
}
