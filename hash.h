#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include "pagina.h"
#include "lista.h"

typedef struct hash Hash;

Hash* inicializaHash(int tam);

void liberaHash(Hash* hashTable);

uint32_t funcaoHash(char* s, int len, uint32_t M);

void insereHash(Hash* hashTable, char* s, Pagina* pagina);

Pagina* procuraHash(Hash* hashTable, char* string);