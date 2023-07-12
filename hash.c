#include "hash.h"


typedef struct celula Celula;

struct celula
{
    char* str;
    Lista* paginas;
};

struct hash{
    Celula** celulas;
    int tamanho;
};

Hash* inicializaHash(int tam) {
    Hash* hashTable = (Hash*)malloc(sizeof(Hash));
    hashTable->tamanho = tam;

    hashTable->celulas = (Celula**)calloc(tam, sizeof(Celula*));

    return hashTable;
}

void liberaHash(Hash* hashTable) {
    if (hashTable == NULL) {
        return;
    }

    for (int i = 0; i < hashTable->tamanho; i++) {
        Celula* celula = hashTable->celulas[i];
        free(celula);
    }

    free(hashTable->celulas);
    free(hashTable);
}

uint32_t funcaoHash(char* s, int len, uint32_t M) {
    uint32_t h = 0;

    for (int i = 0; i < len; i++) {
        h = (251*h + s[i]) % M;
    }

    return h;
}

void insereHash(Hash* hashTable, char* s, Pagina* pagina) {
    int index = funcaoHash(s, strlen(s), hashTable->tamanho);

    Celula* celula = (Celula*)malloc(sizeof(Celula));
    celula->str = s;

    inserePagina(celula->paginas, pagina);

    hashTable->celulas[index] = celula;
}

Pagina* procuraHash(Hash* hashTable, char* string) {
    int index = funcaoHash(string, strlen(string), hashTable->tamanho);
    Pagina* p;

    Celula* celula = hashTable->celulas[index];
    p = getPagina(celula->paginas, string);

    if (p != NULL) {
        return p;
    }

    return NULL; // Valor não encontrado
}