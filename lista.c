/** Define um tad Lista de Paginas.
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

void liberaLista(Lista* lista){
    Celula* p = lista->prim;
    Celula* ant = NULL;

    while (p !=NULL)
    {
        ant = p;
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
    lista->iterator = lista->prim;
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
    }
    else{
        lista->iterator = lista->iterator->prox;
    }
    cel = lista->iterator;
    if(cel == NULL){
        return NULL;
    }
    Pagina* pagina = cel->pagina;
    
    return pagina;
}

Lista* comparaListas(Lista* commonPages, Lista* lista){
    if(commonPages == NULL || lista == NULL){
        return commonPages;
    }
    // adquire a primeira pagina da lista commonPages
    Pagina* pag = getPrim(commonPages);

    // itera sobre a lista commonPages
    while(pag != NULL){
        if(getPagina(lista, getNomePagina(pag)) == NULL){   // caso nao encontre a pagina na outra lista
            removePagina(commonPages, pag); // remove de commonPages
        }
        if(commonPages != NULL){
            pag = proxPagina(commonPages);
        }
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
        pr += getOldPR(p->pagina)/getNumLinksSaindo(p->pagina); // PR(k-1)(j) / |Out(j)|
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
        er = fabs(attPR(p->pagina, numPags) - oldPR);   // e(k) = |PR(k)(i) - PR(k-1)(i)|
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

Lista* copiaLista(Lista* listaCpy, Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        inserePagina(listaCpy, p->pagina);
        p = p->prox;
    }

    return listaCpy;
}

void removePagina(Lista* lista, Pagina* pag){
    Celula* ant = NULL;
    Celula* p = lista->prim;

    while (p != NULL && (p->pagina != pag))
    {
        ant = p;
        p = p->prox;
    }

    if((lista->prim == NULL) || (p == NULL)){
        lista->iterator = NULL;
        return;
    }
    if((lista->prim == lista->ult) && (lista->prim == p)){
        free(p);
        lista->iterator = NULL;
        lista->prim = NULL;
        lista->ult = NULL;
        return;
    }
    else if(lista->prim == p){
        lista->prim = p->prox;
        lista->iterator = NULL;
        free(p);
    }
    else if(lista->ult == p){
        ant->prox = NULL;
        lista->ult = ant;
        lista->iterator = lista->ult;
        free(p);
    }
    else if(p !=NULL)
    {
        lista->iterator = ant;
        ant->prox = p->prox;
        free(p);
    }
    return;
}