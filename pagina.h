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
 * @return Pagina
 */
Pagina* inicializaPagina(char* nome);

char* getNomePagina(Pagina* p);

double getPageRank(Pagina* p);

void imprimePagina(Pagina* p);

void imprimePaginaELinks(Pagina* p);

void imprimePaginaArquivo(Pagina* p, FILE* saida);

void adcionaLink(Pagina* origem, Pagina* destino);

Lista* getLinksEntrando(Pagina* p);

int getNumLinksEntrando(Pagina* p);

int getNumLinksSaindo(Pagina* p);

double getOldPR(Pagina* p);

void liberaPagina(Pagina* p);

int comparaPagina(Pagina* p1, Pagina* p2);

void setPR(Pagina* p, int numPags);

double attPR(Pagina* p, int numPags);

void printPR(Pagina* p);

void invertePRPagina(Pagina* p);

#endif // PAGINA_H