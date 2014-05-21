#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashing.h"


int get_nwords(const char *filename)
{
    FILE *fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n", filename);
        return -1;
    }

    int count = 0;
    char buf[28];

    while(!feof(fp)) {
        fscanf(fp,"%s",buf);
        count++;
    }

    fclose(fp);

    return count-1;
}


void fill_tree(const char *filename, struct Hashelement *tree, const int treesize)
{
    FILE *fp = fopen(filename,"r");
    if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n",filename);
        return;
    }

    char buf[28];
    int bookmark = 0, pos = 0;
    unsigned long int hashvalue;

    for(int i=0; i<treesize; i++)
    {
        fscanf(fp,"%s",buf);
        hashvalue = djb2((unsigned char*)buf);

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
                return;
            }
        }
        tree[bookmark].hash = hashvalue;
        bookmark++;
    }
    fclose(fp);
}


void write_tree_to_file(const char *filename, struct Hashelement *tree, const int treesize)
{
    FILE *fp = fopen(filename,"wb");

    fwrite(&(treesize),sizeof(int),1,fp);

    int i;
    for(i=0; i<treesize; i++)
    {
        fwrite(&(tree[i].hash),sizeof(unsigned long int),1,fp);
        fwrite(&(tree[i].child1),sizeof(int),1,fp);
        fwrite(&(tree[i].child2),sizeof(int),1,fp);
    }
    fclose(fp);

    return;
}


int main()
{
    char *filename = "../assets/pt-ao.txt";
    char *treefile = "database.bin";
    int treesize = get_nwords(filename);
    struct Hashelement *tree = (struct Hashelement*) calloc(treesize, sizeof(struct Hashelement));

	for(int i=0; i<treesize; i++)
	{
		tree[i].hash = 0;
		tree[i].child1 = 0;
		tree[i].child2 = 0;
	}

    fill_tree(filename, tree, treesize);

    write_tree_to_file(treefile, tree, treesize);

    return 0;
}
