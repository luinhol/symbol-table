/** Define um tad Termo.
 * @file termo.c
 * @author Lucas Pereira Taborda
 */

#include "termo.h"

// estrutura de dados que armazena informacoes da entrada
struct termo
{
    // termo em si
    char** palavra;
    // paginas que contem a palavra
    Hash* paginas;
};

// funcao que inicializa um termo
Termo* inicializaTermo(char** palavra, int numPaginas){
    Termo* termo = (Termo*)malloc(sizeof(Termo));

    termo->palavra = palavra;

    termo->paginas = inicializaHash(numPaginas);

    return termo;
}

void adcionaPagina(Termo* termo, Pagina* pagina){
    
}