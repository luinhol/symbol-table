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
 * Tad termo
 */
typedef struct termo Termo;

/**
 * Funcao que inicializa um Termo
 * @param palavra Palavra a ser inicalizadaa
 * @param numPaginas Numero de Paginas total
 * @return Termo inicializado
 */
Termo* inicializaTermo(char* palavra, int numPaginas);

/**
 * Funcao que retorna o nome (string) de um termo
 * @param termo Termo
 * @return Nome (string) do termo
 */
char* getNomeTermo(Termo* termo);

/**
 * Funcao que retorna a hash das Paginas que o Termo está
 * @param termo termo
 * @return Hash das Paginas que o Termo esta
 */
Hash* getHash(Termo* termo);

/**
 * Funcao que adciona uma Pagina ao Termo
 * @param termo Termo
 * @param pagina Pagina que o termo esta contido (que sera inserida no termo)
 */
void adcionaPagina(Termo* termo, Pagina* pagina);

/**
 * Funcao que libera Termo
 * @param termo Termo
 */
void liberaTermo(Termo* termo);

/**
 * Funcao que compara 2 Termos
 * @param a Termo1
 * @param b Termo2
 * @return Retorno da funcao strcasecmp entre a e b
 */
int comparaTermos(const void* a, const void* b);