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

    while ((p != NULL) && strcmp(getNomePagina(p->pagina), nome))
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