
struct Hashelement {
    unsigned long int hash;
    int child1;
    int child2;
};


unsigned long int djb2 (unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}