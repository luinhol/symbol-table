#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "pagina.h"
#include "lista.h"

typedef struct hash Hash;

Hash* inicializaHash(int tam);

Lista* getListaHash(Hash* hashtable, int index);

int getTamanhoHash(Hash* hashTable);

void liberaHash(Hash* hashTable, bool b);

uint32_t funcaoHash(char* s, int len, uint32_t M);

void insereHash(Hash* hashTable, char* s, Pagina* pagina);

Pagina* procuraHash(Hash* hashTable, char* string);

void imprimeHash(Hash* hash);

void imprimeHashArquivo(Hash* hash, FILE* arquivo);

Lista* getPaginasComuns(Hash** hashTable, int numHashes);