/** Define um tad Pagina.
 * @file pagina.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tad pagina
 */
typedef struct pagina Pagina;

/**
 * Funcao que inicializa uma Pagina
 * @return Pagina
 */
Pagina* inicializaPagina(char* nome);

char* getNomePagina(Pagina* p);

void imprimePagina(Pagina* p);

void liberaPagina(Pagina* p);