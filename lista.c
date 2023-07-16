/** Define um tad Lista de No.
 * @file lista.c
 * @author Lucas Pereira Taborda
 */

#include "lista.h"

// estrutura auxiliar celular
typedef struct celula Celula;

struct celula
{
    Pagina* pagina;
    Celula* prox;
};

// estrutura lista que contem ponteiro para primeiro e ultimo da lista, alem de um ponteiro iterador
struct lista
{
    Celula* prim;
    Celula* ult;
    Celula* iterator;
};

Lista* inicializaLista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->iterator = NULL;

    return lista;
}

void inserePagina(Lista* lista, Pagina* pagina){
    Celula* nova = (Celula*)malloc(sizeof(Celula));

    if (lista->prim == NULL)
    {
        lista->prim = nova;
        lista->iterator = lista->prim;
    }
    else
    {
        lista->ult->prox = nova;
    }
    

    lista->ult = nova;
    nova->prox = NULL;
    nova->pagina = pagina;
}

void imprimeLista(Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        imprimePagina(p->pagina);
        printf(" ");
        p = p->prox;
    }
}

void imprimeListaELinks(Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        imprimePaginaELinks(p->pagina);
        p = p->prox;
        printf("\n\t");
    }
}

void imprimeListaArquivo(Lista* lista, FILE* arquivo){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        imprimePaginaArquivo(p->pagina, arquivo);
        fprintf(arquivo, " ");
        p = p->prox;
    }
}

void liberaLista(Lista* lista){
    Celula* p = lista->prim;
    Celula* ant = NULL;

    while (p !=NULL)
    {
        ant = p;
        // liberaPagina(p->pagina);
        p = p->prox;
        free(ant);
    }
    free(lista);
}

void liberaListaEPaginas(Lista* lista){
    Celula* p = lista->prim;
    Celula* ant = NULL;

    while (p !=NULL)
    {
        ant = p;
        liberaPagina(p->pagina);
        p = p->prox;
        free(ant);
    }
    free(lista);
}

Pagina* getPrim(Lista* lista){
    return lista->prim->pagina;
}

// caminha ate encontrar um No com o mesmo identificador informado
Pagina* getPagina(Lista* lista, char* nome){
    Celula* p = lista->prim;

    while ((p != NULL) && strcasecmp(getNomePagina(p->pagina), nome))
    {
        p = p->prox;
    }

    if (p != NULL)
    {
        return p->pagina;
    }
    
    return NULL;
}

// caminha o iterador para o proximo No da lista e retorna esse No
Pagina* proxPagina(Lista* lista){
    Celula* cel;
    if(lista->iterator == NULL){
        lista->iterator = lista->prim;
        return NULL;
    }

    lista->iterator = lista->iterator->prox;
    cel = lista->iterator;
    if(cel == NULL){
        return NULL;
    }
    Pagina* pagina = cel->pagina;
    
    return pagina;
}

Lista* comparaListas(Lista* commonPages, Lista* lista1, Lista* lista2){
    if(lista1 == NULL || lista2 == NULL){
        return commonPages;
    }
    Pagina* pag1 = getPrim(lista1);

    while(pag1 != NULL){
        Pagina* pag2 = getPrim(lista2);
        
        if(getPagina(lista2, getNomePagina(pag1)) != NULL){
            inserePagina(commonPages, pag1);
        }

        pag1 = proxPagina(lista1);
    }
    
    return commonPages;
}

void zeraPR(Lista* lista, int numPags){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        setPR(p->pagina, numPags);
        p = p->prox;
    }
}

double catchINPR(Lista* lista){
    double pr = 0;
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        pr += getOldPR(p->pagina)/getNumLinksSaindo(p->pagina);
        p = p->prox;
    }
    return pr;
}

double atualizaPR(Lista* lista, int numPags){
    double er = 0, oldPR = 0;

    Celula* p = lista->prim;

    while (p !=NULL)
    {
        oldPR = getOldPR(p->pagina);
        er = fabs(attPR(p->pagina, numPags) - oldPR);
        p = p->prox;
    }

    return er;
}

void imprimePRLista(Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        printPR(p->pagina);
        printf(" ");
        p = p->prox;
    }
}

void invertePR(Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        invertePRPagina(p->pagina);
        p = p->prox;
    }
}

void selectionSort(Lista* lista) {
    Celula* i;
    Celula* j;
    Celula* maxCel;

    double max;

    for (i = lista->prim; i != NULL; i = i->prox) {
        max = getPageRank(i->pagina);
        maxCel = i;
        for (j = i->prox; j != NULL; j = j->prox) {
            if (getPageRank(j->pagina) > max) {
                max = getPageRank(j->pagina);
                maxCel = j;
            }
        }
        if (maxCel != i) {
            Pagina* temp = i->pagina;
            i->pagina = maxCel->pagina;
            maxCel->pagina = temp;
        }
    }
}