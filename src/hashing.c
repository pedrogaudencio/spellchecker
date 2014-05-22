/*
* DJB2 is a fast hash function which also provides
* good uniqueness.
* See http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned long int djb2 (unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
