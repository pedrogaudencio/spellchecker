#ifndef HASH_H
#define HASH_H

struct Hashelement {
    unsigned long int hash;
    int child1;
    int child2;
};

unsigned long int djb2 (unsigned char *str);

#endif
