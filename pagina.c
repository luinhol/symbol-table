/** Define um tad Pagina.
 * @file pagina.c
 * @author Lucas Pereira Taborda
 */

#include "pagina.h"

struct pagina
{
    char* nome;
    int numLinksSaindo;
    int numLinksEntrando;
    Lista* linksEntrando;
    double pageRank;
    double oldPageRank;
};

Pagina* inicializaPagina(char* nome){
    Pagina* pagina = (Pagina*)malloc(sizeof(Pagina));
    pagina->nome = nome;
    pagina->linksEntrando = inicializaLista();
    pagina->numLinksEntrando = 0;
    pagina->numLinksSaindo = 0;
    pagina->pageRank = 0;
    pagina->oldPageRank = 0;
    return pagina;
}

char* getNomePagina(Pagina* p){
    return p->nome;
}

double getPageRank(Pagina* p){
    return p->pageRank;
}

void imprimePagina(Pagina* p){
    printf("%s", p->nome);
}

void imprimePaginaELinks(Pagina* p){
    printf("pagina: %s, numLinksSaindo: %d, numLinksEntrando: %d, linksEntrando: ", p->nome, p->numLinksSaindo, p->numLinksEntrando);
    imprimeLista(p->linksEntrando);
}

void imprimePaginaArquivo(Pagina* p, FILE* saida){
    fprintf(saida, "nome pagina: %s", p->nome);
}

void adcionaLink(Pagina* origem, Pagina* destino){
    inserePagina(destino->linksEntrando, origem);
    destino->numLinksEntrando++;
    origem->numLinksSaindo++;
}

Lista* getLinksEntrando(Pagina* p){
    return p->linksEntrando;
}

int getNumLinksEntrando(Pagina* p){
    return p->numLinksEntrando;
}

int getNumLinksSaindo(Pagina* p){
    return p->numLinksSaindo;
}

double getOldPR(Pagina* p){
    return p->oldPageRank;
}

void liberaPagina(Pagina* p){
    liberaLista(p->linksEntrando);
    free(p->nome);
    free(p);
}

int comparaPagina(Pagina* p1, Pagina* p2){
    return strcasecmp(getNomePagina(p1), getNomePagina(p2));
}

void setPR(Pagina* p, int numPags){
    p->pageRank = 1 / (double)numPags;
    p->oldPageRank = 1 / (double)numPags;
}

double attPR(Pagina* p, int numPags){
    Lista* linksChegando = p->linksEntrando;
    double a = 0.85;
    double pr = 0;
    double somatorio = 0;
    if(p->numLinksSaindo == 0){
        somatorio = catchINPR(linksChegando);
        pr = ((1.0-a)/(double)numPags) + (a*getOldPR(p)) + (a*somatorio);
    }
    else{
        somatorio = catchINPR(linksChegando);
        pr = ((1.0-a)/(double)numPags) + (a*somatorio);
    }

    p->pageRank = pr;
    return pr;
}

void invertePRPagina(Pagina* p){
    double aux = p->oldPageRank;
    p->oldPageRank = p->pageRank;
    p->pageRank = aux;
}

void printPR(Pagina* p){
    printf("%.14f", p->pageRank);
}