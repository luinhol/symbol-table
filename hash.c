#include "hash.h"


typedef struct celula Celula;

struct celula
{
    Lista* paginas;
};

struct hash{
    Celula** celulas;
    int tamanho;
};

static Lista* getListaCelula(Celula* celula){
    return celula->paginas;
}

Lista* getListaHash(Hash* hashtable, int index){
    if(hashtable->celulas[index] != NULL){
        return getListaCelula(hashtable->celulas[index]);
    }
    else{
        return NULL;
    }
}

Hash* inicializaHash(int tam) {
    Hash* hashTable = (Hash*)malloc(sizeof(Hash));
    hashTable->tamanho = tam;

    hashTable->celulas = (Celula**)calloc(tam, sizeof(Celula*));

    return hashTable;
}

int getTamanhoHash(Hash* hashTable){
    return hashTable->tamanho;
}

void liberaHash(Hash* hashTable) {
    if (hashTable == NULL) {
        return;
    }

    for (int i = 0; i < hashTable->tamanho; i++) {
        Celula* celula = hashTable->celulas[i];
        if(celula != NULL){
            liberaLista(celula->paginas);
            free(celula);
        }
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
    Celula* celula;
    Lista* lista;

    // printf("inserindo pag: %s na hash na posicao %d\n", getNomePagina(pagina), index);

    if(hashTable->celulas[index] == 0){
        celula = (Celula*)malloc(sizeof(Celula));
        celula->paginas = inicializaLista();

        inserePagina(celula->paginas, pagina);

        hashTable->celulas[index] = celula;
    }
    else{
        lista = getListaCelula(hashTable->celulas[index]);
        if(getPagina(lista, getNomePagina(pagina)) == NULL){
            inserePagina(lista, pagina);
        }
    }
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

void imprimeHash(Hash* hashTable){
    Lista* lista;

    printf("estado atual da hash:\n");
    for(int i = 0; i < hashTable->tamanho; i++){
        printf("\t [%d]", i);
        if (hashTable->celulas[i] != NULL)
        {
            lista = getListaCelula(hashTable->celulas[i]);
            imprimeLista(hashTable->celulas[i]->paginas);
        }
        else {
            printf("vazio");
        }
        printf("\n");
    }
}

void imprimeHashArquivo(Hash* hashTable, FILE* saida){
    Lista* lista;
    
    fprintf(saida, "estado atual da hash:\n");
    for(int i = 0; i < hashTable->tamanho; i++){
        fprintf(saida, "\t [%d]", i);
        if (hashTable->celulas[i] != NULL)
        {
            lista = getListaCelula(hashTable->celulas[i]);
            imprimeListaArquivo(hashTable->celulas[i]->paginas, saida);
        }
        else {
            fprintf(saida, "vazio");
        }
        fprintf(saida, "\n");
    }
}