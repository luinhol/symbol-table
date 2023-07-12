/** Define um tad Lista de Pagina.
 * @file lista.h
 * @author Lucas Pereira Taborda
 */

#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tad lista de Pagina
 */
typedef struct lista Lista;

/**
 * Funcao que inicializa uma Lista
 * @return Lista
 */
Lista* inicializaLista();

/**
 * Funcao que insere um No na Lista
 * @param lista Lista que sera inserido o No
 * @param pagina No a ser inserido na Lista
 */
void inserePagina(Lista* lista, Pagina* pagina);

/**
 * Funcao que retira um No da Lista
 * @param lista Lista que sera retirado o No
 * @param id id do No a ser retirado
 */
void retiraPagina(Lista* lista, int id);

/**
 * Funcao que imprime uma Lista
 * @param lista Lista a ser impressa
 */
void imprimeLista(Lista* lista);

/**
 * Destrutor de Lista
 * @param lista Lista a ser destruida
 */
void liberaLista(Lista* lista);

/**
 * Funcao que retorna o primeiro No da Lista
 * @param lista Lista
 */
Pagina* getPrim(Lista* lista);

/**
 * Funcao que retorna um No presente na lista
 * @param lista Lista que sera procurado o No
 * @param id id do No a ser procurado
 * @return No presente na lista
 */
Pagina* getPagina(Lista* lista, char* nome);

/**
 * Funcao que caminha para o proximo No da lista
 * @param lista Lista
 * @return proximo No presente na lista
 */
Pagina* proxPagina(Lista* lista);