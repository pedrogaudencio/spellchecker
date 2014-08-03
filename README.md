spellchecker
============

Spellchecker built from a given dictionary.

Compile
-------
`gcc build_dict.c hashing.c -Wall -std=gnu99 -o build_dict.o`

`gcc check_typo.c hashing.c typos.c linkedlist.c -Wall -std=gnu99 -o check_typo.o`

Generate hashtable from dictionary
----------------------------------
Pipe the content of the `pt-ao.txt` file into `build_dict.o`:

`./build_dict.o < pt-ao.txt`


Check for typos
---------------
Pipe the content of a text file into `check_typo.o`:

`./check_typo.o < text_with_typos.txt`

If no *k* parameter is given to `check_typo.o`, the default typo list will be printed with the 5 most common ones. Otherwise, the accepted range is between 1 and 100000 (e.g. `./check_typo.o 50 < text_with_typos.txt` for *k*=50).
