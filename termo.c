/** Define um tad Termo.
 * @file termo.c
 * @author Lucas Pereira Taborda
 */

#include "termo.h"

struct termo
{
    // termo em si
    char* palavra;
    // paginas que contem a palavra
    Hash* paginas;
};

// funcao que inicializa um termo
Termo* inicializaTermo(char* palavra, int numPaginas){
    Termo* termo = (Termo*)malloc(sizeof(Termo));

    Hash* hash = inicializaHash((numPaginas*2) - 1);

    termo->palavra = palavra;

    termo->paginas = hash;

    return termo;
}

char* getNomeTermo(Termo* termo){
    return termo->palavra;
}

Hash* getHash(Termo* termo){
    return termo->paginas;
}

void adcionaPagina(Termo* termo, Pagina* pagina){
    insereHash(termo->paginas, getNomePagina(pagina), pagina);
}

void liberaTermo(Termo* termo){
    if(termo != NULL){
        liberaHash(termo->paginas, false);
        free(termo->palavra);
        free(termo);
    }
}

int comparaTermos(const void* a, const void* b){
    Termo* termo1 = (Termo*)a;
    Termo* termo2 = (Termo*)b;
    return strcasecmp(getNomeTermo(termo1), getNomeTermo(termo2));
}