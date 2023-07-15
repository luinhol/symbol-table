/** Define um tad Termo.
 * @file termo.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "hash.h"
#include "pagina.h"

/**
 * Estrutura que armazena termos da entrada
 */
typedef struct termo Termo;

Termo* inicializaTermo(char* palavra, int numPaginas);

char* getNomeTermo(Termo* termo);

Hash* getHash(Termo* termo);

void adcionaPagina(Termo* termo, Pagina* pagina);

void liberaTermo(Termo* termo);