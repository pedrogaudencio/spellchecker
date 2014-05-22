#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashing.h"

#define MAX_WORDS 400000
#define MAX_WORD_SIZE 28


int fill_tree(struct Hashelement *tree, const int treesize)
{
    char buf[MAX_WORD_SIZE];
    int bookmark = 0, pos = 0;
    unsigned long int hashvalue;

    while(fgets(buf, MAX_WORD_SIZE, stdin)){
        buf[strlen(buf)-1] = '\0';
        hashvalue = djb2((unsigned char*) buf);
        //printf("%d %s\n", bookmark, buf);

        pos = 0;
        while(tree[pos].hash != 0)
        {
            if(hashvalue < tree[pos].hash) {
                if(tree[pos].child1 == 0) {
                    tree[pos].child1 = bookmark;
                    break;
                }
                else
                    pos = tree[pos].child1;
            }
            else if(hashvalue > tree[pos].hash) {
                if(tree[pos].child2 == 0) {
                    tree[pos].child2 = bookmark;
                    break;
                }
                else
                    pos = tree[pos].child2;
            }
            else {
                printf("*** error while filling tree: collision between words. exit.\n");
                return -1;
            }
        }
        tree[bookmark].hash = hashvalue;
        bookmark++;
    }

    return bookmark-1;
}


void write_tree_to_file(const char *filename, struct Hashelement *tree, const int treesize)
{
    FILE *fp = fopen(filename, "wb");

    fwrite(&(treesize), sizeof(int), 1, fp);

    int i;
    for(i=0; i<treesize; i++)
    {
        fwrite(&(tree[i].hash), sizeof(unsigned long int), 1, fp);
        fwrite(&(tree[i].child1), sizeof(int), 1, fp);
        fwrite(&(tree[i].child2), sizeof(int), 1, fp);
    }
    fclose(fp);

    return;
}


int main()
{
    char *treefile = "database.bin";
    int treesize = MAX_WORDS;
    struct Hashelement *tree = (struct Hashelement*) calloc(treesize, sizeof(struct Hashelement));

	for(int i=0; i<treesize; i++)
	{
		tree[i].hash = 0;
		tree[i].child1 = 0;
		tree[i].child2 = 0;
	}

    treesize = fill_tree(tree, treesize);

    write_tree_to_file(treefile, tree, treesize);

    free(tree);

    return 0;
}
