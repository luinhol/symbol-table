/** Define um tad Lista de Paginas.
 * @file lista.h
 * @author Lucas Pereira Taborda
 */

/**
 * Tad lista de Pagina
 */
typedef struct lista Lista;

#ifndef LISTA_H
#define LISTA_H

#include <math.h>
#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Funcao que inicializa uma Lista
 * @return Lista
 */
Lista* inicializaLista();

/**
 * Funcao que insere uma Pagina na Lista
 * @param lista Lista que sera inserido o No
 * @param pagina Pagina a ser inserida na Lista
 */
void inserePagina(Lista* lista, Pagina* pagina);

/**
 * Funcao que retira uma Pagina da Lista
 * @param lista Lista que sera retirado a Pagina
 * @param pagina Pagina a ser retirada
 */
void removePagina(Lista* lista, Pagina* pagina);

/**
 * Funcao que imprime uma Lista
 * @param lista Lista a ser impressa
 */
void imprimeLista(Lista* lista);

/**
 * Funcao que imprime uma Lista e o link entre as paginas
 * @param lista Lista a ser impressa
 */
void imprimeListaELinks(Lista* lista);

/**
 * Destrutor de Lista
 * @param lista Lista a ser destruida
 */
void liberaLista(Lista* lista);

/**
 * Destrutor de Lista que tambem destroi as paginas da lista
 * @param lista Lista a ser destruida
 */
void liberaListaEPaginas(Lista* lista);

/**
 * Funcao que retorna a primeira Pagina da lista
 * @param lista Lista
 * @return Primeira Pagina
 */
Pagina* getPrim(Lista* lista);

/**
 * Funcao que retorna uma Pagina presente na lista
 * @param lista Lista que sera procurada a Pagina
 * @param nome Nome da Pagina a ser procurada
 * @return Pagina presente na lista
 */
Pagina* getPagina(Lista* lista, char* nome);

/**
 * Funcao que caminha para a proxima Pagina da lista
 * @param lista Lista
 * @return Proxima Pagina presente na lista
 */
Pagina* proxPagina(Lista* lista);

/**
 * Funcao que compara duas listas e retorna uma lista com as paginas comuns
 * @param commonPages Lista de paginas comuns
 * @param lista Lista de paginas a ser comparada
 * @return CommonPages - (Paginas que nao estao em lista)
 */
Lista* comparaListas(Lista* commonPages, Lista* lista);

/**
 * Funcao que zera o pageRank de todas as Paginas de uma lista
 * @param lista Lista
 * @param numPags Numero de paginas
 */
void zeraPR(Lista* lista, int numPags);

/**
 * Funcao que adquire o somatorio do pageRank das paginas de uma lista
 * @param lista Lista
 * @return Somatorio do pageRank
 */
double catchINPR(Lista* lista);

/**
 * Funcao que atualiza pageRank de uma lista
 * @param lista Lista
 * @param numPags Numero de paginas
 * @return Somatorio e(k)
 */
double atualizaPR(Lista* lista, int numPags);

/**
 * Funcao que imprime uma lista de pageRank de uma lista de paginas
 * @param lista Lista
 */
void imprimePRLista(Lista* lista);

/**
 * Funcao que troca o pageRank antigo pelo novo e vice-versa
 * @param lista Lista
 */
void invertePR(Lista* lista);

/**
 * Funcao que ordena uma Lista, por pageRank
 * @param lista Lista
 */
void selectionSort(Lista* lista);

/**
 * Funcao que copia uma lista
 * @param listaCpy Lista destino da copia
 * @param lista Lista origem da copia
 * @return Lista resultado da copia
 */
Lista* copiaLista(Lista* listaCpy, Lista* lista);

#endif // LISTA_H