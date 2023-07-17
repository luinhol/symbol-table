/** Define um tad Pagina.
 * @file pagina.h
 * @author Lucas Pereira Taborda
 */

/**
 * Tad pagina
 */
typedef struct pagina Pagina;

#ifndef PAGINA_H
#define PAGINA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/**
 * Funcao que inicializa uma Pagina
 * @param nome Nome da Pagina
 * @return Pagina
 */
Pagina* inicializaPagina(char* nome);

/**
 * Funcao que retorna o nome de uma Pagina
 * @param p Pagina
 * @return Nome da Pagina
 */
char* getNomePagina(Pagina* p);

/**
 * Funcao que retorna o pageRank de uma Pagina
 * @param p Pagina
 * @return PageRank da Pagina
 */
double getPageRank(Pagina* p);

/**
 * Funcao que imprime uma Pagina
 * @param p Pagina
 */
void imprimePagina(Pagina* p);

/**
 * Funcao que imprime uma Pagina e Seus links
 * @param p Pagina
 */
void imprimePaginaELinks(Pagina* p);

/**
 * Funcao que adciona um link a uma Pagina
 * @param origem Pagina de origem
 * @param destino Pagina de destino
 */
void adcionaLink(Pagina* origem, Pagina* destino);

/**
 * Funcao que retorna uma lista com os links que entram em uma Pagina
 * @param p Pagina
 * @return Lista com os links que entram na Pagina
 */
Lista* getLinksEntrando(Pagina* p);

/**
 * Funcao que retorna o numero de links entrando em uma Pagina
 * @param p Pagina
 * @return Numero de links entrando na Pagina
 */
int getNumLinksEntrando(Pagina* p);

/**
 * Funcao que retorna o numero de links saindo de uma Pagina
 * @param p Pagina
 * @return Numero de links saindo da pagina
 */
int getNumLinksSaindo(Pagina* p);

/**
 * Funcao que retorna o valor antigo do pageRank de uma Pagina
 * @param p Pagina
 * @return PageRank antigo da Pagina
 */
double getOldPR(Pagina* p);

/**
 * Libera uma pagina
 * @param p Pagina
 */
void liberaPagina(Pagina* p);

/**
 * Compara duas Paginas
 * @param p1 Pagina1
 * @param p2 Pagina2
 * @return Retorno da funcao strcasecmp entre p1 e p2
 */
int comparaPagina(Pagina* p1, Pagina* p2);

/**
 * Funcao que "zera" o PR de uma Pagina para o valor inicial
 * @param p Pagina
 * @param numPags Numero de paginas
 */
void setPR(Pagina* p, int numPags);

/**
 * Funcao que atualiza o pageRank de uma Pagina
 * @param p Pagina
 * @param numPags Numero de paginas
 * @return Novo valor do pageRank
 */
double attPR(Pagina* p, int numPags);

/**
 * Funcao que imprime pageRank de uma pagina
 * @param p Pagina
 */
void printPR(Pagina* p);

/**
 * Funcao que inverte o pageRank de uma Pagina
 * @param p Pagina
 */
void invertePRPagina(Pagina* p);

#endif // PAGINA_H