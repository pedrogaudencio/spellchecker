#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "hashing.h"


int check_for_typo(struct Hashelement *tree, const int treesize, uint64_t thehash)
{
    int istypo = 1, pos = 0;

    while(1) {
        if(tree[pos].hash == thehash) {
            istypo = 0;
            break;
        }
        else if(thehash < tree[pos].hash) {
            if(tree[pos].child1 == 0)
                break;
            else
                pos = tree[pos].child1;
        }
        else if(thehash > tree[pos].hash) {
            if(tree[pos].child2 == 0)
                break;
            else
                pos = tree[pos].child2;
        }
    }

    return istypo;
}


void read_tree_from_file(const char *filename, struct Hashelement **tree, int *treesize)
{
    FILE *fp = fopen(filename,"rb");
    if(fp == NULL) {
        printf("*** error: could not open file %s. exit.\n", filename);
        return;
    }

    fread(treesize,sizeof(int),1,fp);

    *tree = (struct Hashelement*) calloc(*treesize, sizeof(struct Hashelement));

    int i;
    for(i=0; i<*treesize; i++) {
        fread(&((*tree)[i].hash), sizeof(uint64_t), 1, fp);
        fread(&((*tree)[i].child1), sizeof(int), 1, fp);
        fread(&((*tree)[i].child2), sizeof(int), 1, fp);
    }
}

int main (void)
{
    char *treefile = "database.bin";
    int treesize;
    struct Hashelement *tree;

    read_tree_from_file(treefile, &tree, &treesize);

    printf("%s is typo? %d\n","zurzidora",check_for_typo(tree,treesize,djb2((unsigned char*)"zurzidora")));
    printf("%s is typo? %d\n","zurzidor",check_for_typo(tree,treesize,djb2((unsigned char*)"zurzidor")));
    printf("%s is typo? %d\n","urzidora",check_for_typo(tree,treesize,djb2((unsigned char*)"urzidora")));
    printf("%s is typo? %d\n","urzidor",check_for_typo(tree,treesize,djb2((unsigned char*)"urzidor")));
    printf("%s is typo? %d\n","consonavam",check_for_typo(tree,treesize,djb2((unsigned char*)"consonavam")));
    printf("%s is typo? %d\n","ASDFGHJ",check_for_typo(tree,treesize,djb2((unsigned char*)"ASDFGHJ")));
    printf("%s is typo? %d\n","urzido",check_for_typo(tree,treesize,djb2((unsigned char*)"urzido")));
    printf("%s is typo? %d\n","DFGHJ",check_for_typo(tree,treesize,djb2((unsigned char*)"DFGHJ")));
    printf("%s is typo? %d\n","DFG",check_for_typo(tree,treesize,djb2((unsigned char*)"DFG")));

    return 0;
}
