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

// argumento bool "b" se traduz para excluir ou nao as paginas, b = true para excluir, e b = false para nao excluir
void liberaHash(Hash* hashTable, bool b) {
    if (hashTable == NULL) {
        return;
    }

    for (int i = 0; i < hashTable->tamanho; i++) {
        Celula* celula = hashTable->celulas[i];
        if(celula != NULL){
            if(b == false){
                liberaLista(celula->paginas);
            }
            else{
                liberaListaEPaginas(celula->paginas);
            }
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
        if (hashTable->celulas[i] != NULL)
        {
            printf("\t [%d]", i);
            lista = getListaCelula(hashTable->celulas[i]);
            // imprimeLista(hashTable->celulas[i]->paginas);
            imprimeListaELinks(hashTable->celulas[i]->paginas);
            printf("\n");
        }
        else {
            // printf("vazio");
        }
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

Lista* getPaginasComuns(Hash** hashTable, int numHashes) {
    int i = 0, j = 0;
    Lista* commonPages = inicializaLista();
    Lista* lista1 = NULL;
    Lista* lista2 = NULL;

    Hash* firstHash = hashTable[0];
    if (firstHash == NULL)
    {
        liberaLista(commonPages);
        return NULL;
    }
    int hashTam = getTamanhoHash(firstHash);

    // itero sobre cada posicao da hash
    for(i = 0; i < hashTam; i++){
        if (firstHash->celulas[i] != NULL)
        {
            // adquiro a lista de paginas de uma posicao nao nula da hash
            lista1 = getListaHash(firstHash, i);

            // itero pelas outras hashs para ver se possui pagina comum
            for(j = 1; j < numHashes; j++){
                lista2 = getListaHash(hashTable[j], i);
                commonPages = comparaListas(commonPages, lista1, lista2);
            }
        }
    }

    return commonPages;
}

void calculaPageRank(Hash* hashTable, int numPags){
    Lista* lista;
    for(int i = 0; i < hashTable->tamanho; i++){
        if (hashTable->celulas[i] != NULL)
        {
            lista = getListaCelula(hashTable->celulas[i]);
            zeraPR(lista, numPags);
        }
    }

    double pr = 0;
    double er = 1;
    while (er >= 0.000010){
        er = 0;
        for(int i = 0; i < hashTable->tamanho; i++){
            if (hashTable->celulas[i] != NULL)
            {
                lista = getListaCelula(hashTable->celulas[i]);
                invertePR(lista);
            }
        }
        for(int i = 0; i < hashTable->tamanho; i++){
            if (hashTable->celulas[i] != NULL)
            {
                lista = getListaCelula(hashTable->celulas[i]);
                er += atualizaPR(lista, numPags);
            }
        }
        er = er * (1.0/(double)numPags);
    }
}