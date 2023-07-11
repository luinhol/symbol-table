/** Define um tad Lista de No.
 * @file lista.c
 * @author Lucas Pereira Taborda
 */

#include "lista.h"

// estrutura auxiliar celular
typedef struct celula Celula;

struct celula
{
    No* no;
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

void insereNo(Lista* lista, No* no){
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
    nova->no = no;
}

void retiraNo(Lista* lista, int id){
    Celula* ant = NULL;
    Celula* p = lista->prim;

    while (p !=NULL && (id == getId(p->no)))
    {
        ant = p;
        p = p->prox;
    }

    if(lista->prim == NULL){
        return;
    }
    if(lista->prim == lista->ult){
        liberaNo(lista->prim->no);
        free(p);
        
        lista->prim = NULL;
        lista->ult = NULL;
        return;
    }
    else if(lista->prim == p){
        liberaNo(lista->prim->no);
        lista->prim = p->prox;
        free(p);
    }
    else if(lista->ult == p){
        liberaNo(lista->ult->no);
        ant->prox = NULL;
        lista->ult = ant;
        free(p);
    }
    else
    {
        ant->prox = p->prox;
        liberaNo(p->no);
        free(p);
    }
    lista->iterator = lista->prim;
    return;
}

void imprimeLista(Lista* lista){
    Celula* p = lista->prim;

    while (p !=NULL)
    {
        imprimeNo(p->no);
        printf(" ");
        p = p->prox;
    }
}

void liberaLista(Lista* lista){
    Celula* p = lista->prim;
    Celula* ant = NULL;

    while (p !=NULL)
    {
        ant = p;
        liberaNo(p->no);
        p = p->prox;
        free(ant);
    }
    free(lista);
}

No* getPrim(Lista* lista){
    return lista->prim->no;
}

// caminha ate encontrar um No com o mesmo identificador informado
No* getNo(Lista* lista, int id){
    Celula* p = lista->prim;

    while ((p != NULL) && (id != getId(p->no)))
    {
        p = p->prox;
    }

    return p->no;
}

// caminha o iterador para o proximo No da lista e retorna esse No
No* proxNo(Lista* lista){
    if(lista->iterator == NULL){
        lista->iterator = lista->prim;
        return NULL;
    }

    Celula* cel = lista->iterator;
    No* no = cel->no;

    lista->iterator = cel->prox;
    
    return no;
}