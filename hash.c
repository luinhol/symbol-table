/** Define um tad Hash de Paginas.
 * @file hash.c
 * @author Lucas Pereira Taborda
 */

#include "hash.h"


typedef struct celula Celula;

// estrutura celula contendo pagina
struct celula
{
    Lista* paginas;
};

// estrutura que armazena a hash e seu tamanho
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

// funcao que insere uma pagina na hash
void insereHash(Hash* hashTable, char* s, Pagina* pagina) {
    int index = funcaoHash(s, strlen(s), hashTable->tamanho);
    Celula* celula;
    Lista* lista;

    if(hashTable->celulas[index] == 0){ // se a lista nao foi inicializada na posicao index, inicializa a lista e insere a pagina
        celula = (Celula*)malloc(sizeof(Celula));
        celula->paginas = inicializaLista();

        inserePagina(celula->paginas, pagina);

        hashTable->celulas[index] = celula;
    }
    else{
        lista = getListaCelula(hashTable->celulas[index]);  // caso a lista ja tenha sido inicializada
        if(getPagina(lista, getNomePagina(pagina)) == NULL){    // verifica se a pagina ja esta na lista
            inserePagina(lista, pagina);    // caso ainda nao esteja, insere na lista
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

// funcao que retorna uma lista com as paginas comuns entre as hashs
Lista* getPaginasComuns(Hash** hashTable, int numHashes) {
    int i = 0, j = 0;
    Lista* commonPages = NULL;
    Lista* lista = NULL;

    // adquire a primeira hash
    Hash* firstHash = hashTable[0];
    if (firstHash == NULL)
    {
        liberaLista(commonPages);
        return NULL;
    }
    int hashTam = getTamanhoHash(firstHash);
    
    // adquire a lista com todas as paginas da primeira hash
    commonPages = getListaTodaHash(firstHash);

    // itera pelas outras hashs para ver se possui pagina comum
    for(j = 1; j < numHashes; j++){
        Hash* nextHash = hashTable[j];
        lista = getListaTodaHash(hashTable[j]);
        commonPages = comparaListas(commonPages, lista);    // cas possua uma pagina em comum, adciona a lista de paginas comuns
        liberaLista(lista);
    }

    return commonPages;
}

// calcula o pageRank de todas as paginas de uma hash
void calculaPageRank(Hash* hashTable, int numPags){
    Lista* lista;

    // "zera" o pageRank de todas as paginas
    for(int i = 0; i < hashTable->tamanho; i++){
        if (hashTable->celulas[i] != NULL)
        {
            lista = getListaCelula(hashTable->celulas[i]);
            zeraPR(lista, numPags);
        }
    }

    double pr = 0;
    double er = 1;

    // itera sobre as paginas, recalculando os pageRanks, ate ele para de mudar significativamente
    while (er >= 0.000010){
        er = 0;
        // percorre a hash trocando o pageRank antigo pelo pageRank atual
        for(int i = 0; i < hashTable->tamanho; i++){
            if (hashTable->celulas[i] != NULL)
            {
                lista = getListaCelula(hashTable->celulas[i]);
                invertePR(lista);
            }
        }
        // percorre a hash atualizando o pagerank atual e acumulando o "er"
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

Lista* getListaTodaHash(Hash* hashTable){
    Lista* lista = NULL;
    Lista* listaCpy = inicializaLista();
    
    for(int i = 0; i < hashTable->tamanho; i++){
        if (hashTable->celulas[i] != NULL)
        {
            lista = getListaCelula(hashTable->celulas[i]);
            if(lista != NULL){
                copiaLista(listaCpy, lista);
            }
        }
    }
    return listaCpy;
}