/** Define um tad Lista de No.
 * @file lista.h
 * @author Lucas Pereira Taborda
 */

#include "no.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tad lista de No
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
 * @param no No a ser inserido na Lista
 */
void insereNo(Lista* lista, No* no);

/**
 * Funcao que retira um No da Lista
 * @param lista Lista que sera retirado o No
 * @param id id do No a ser retirado
 */
void retiraNo(Lista* lista, int id);

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
No* getPrim(Lista* lista);

/**
 * Funcao que retorna um No presente na lista
 * @param lista Lista que sera procurado o No
 * @param id id do No a ser procurado
 * @return No presente na lista
 */
No* getNo(Lista* lista, int id);

/**
 * Funcao que caminha para o proximo No da lista
 * @param lista Lista
 * @return proximo No presente na lista
 */
No* proxNo(Lista* lista);