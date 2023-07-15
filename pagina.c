/** Define um tad Pagina.
 * @file pagina.c
 * @author Lucas Pereira Taborda
 */

#include "pagina.h"

struct pagina
{
    char* nome;
    int numLinksSaindo;
    // Lista* linkPaginasEntrando;
    int pageRank;
};

Pagina* inicializaPagina(char* nome){
    Pagina* pagina = (Pagina*)malloc(sizeof(Pagina));
    pagina->nome = nome;
    pagina->numLinksSaindo = 0;
    // pagina->linkPaginasSaindo = inilializaLista();
    pagina->pageRank = 0;
    return pagina;
}

char* getNomePagina(Pagina* p){
    return p->nome;
}

void imprimePagina(Pagina* p){
    printf("nome pagina: %s", p->nome);
}

void imprimePaginaArquivo(Pagina* p, FILE* saida){
    fprintf(saida, "nome pagina: %s", p->nome);
}

void liberaPagina(Pagina* p){
    free(p->nome);
    free(p);
}