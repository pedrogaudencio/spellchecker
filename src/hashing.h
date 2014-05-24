#ifndef HASH_H
#define HASH_H

struct Hashelement {
    uint64_t hash;
    int child1;
    int child2;
};

uint64_t djb2 (unsigned char *str);

#endif
