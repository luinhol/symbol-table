/** Define um tad Hash de Paginas.
 * @file hash.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "pagina.h"
#include "lista.h"

/**
 * Tad hash de paginas
 */
typedef struct hash Hash;

/**
 * Funcao que inicializa uma hash
 * @param tam Tamanho total da hash
 * @return Hash criada
 */
Hash* inicializaHash(int tam);

/**
 * Funcao retorna a lista de paginas de uma posicao index da hash
 * @param hashTable Hash
 * @param index Posicao da hash a ser retornada
 * @return Lista de paginas
 */
Lista* getListaHash(Hash* hashtable, int index);

/**
 * Funcao que retorna o tamanho da hash
 * @param hashTable Hash
 * @return Tamanho da hash
 */
int getTamanhoHash(Hash* hashTable);

/**
 * Funcao que exclui a hash
 * @param hashTable Hash
 * @param b Bool que representa se deve liberar as paginas (true == exluir paginas, false == nao excluir paginas)
 */
void liberaHash(Hash* hashTable, bool b);

/**
 * Funcao que retorna a chave de uma string
 * @param s String
 * @param len Tamanho da string
 * @param M Quociente do calculo da chave
 * @return Chave
 */
uint32_t funcaoHash(char* s, int len, uint32_t M);

/**
 * Funcao que insere uma pagina na hash
 * @param hashTable Hash
 * @param key Chave da hash
 * @param pagina Pagina a ser inserida
 */
void insereHash(Hash* hashTable, char* key, Pagina* pagina);

/**
 * Funcao procura uma chave na hash
 * @param hashTable Hash
 * @param key Chave a se procurada
 * @return Pagina quando encontrada, NULL quando nao encontrada
 */
Pagina* procuraHash(Hash* hashTable, char* key);

/**
 * Funcao que imprime a hash
 * @param hash Hash
 */
void imprimeHash(Hash* hash);

/**
 * Funcao que retorna uma lista de paginas comuns entre diferentes hashs
 * @param hashs Vetor de hashs
 * @param numHashs Numero de hashs no vetr
 * @return Lista de paginas comuns
 */
Lista* getPaginasComuns(Hash** hashs, int numHashs);

/**
 * Funcao que calcula o page rank de uma hash
 * @param hashTable Hash
 * @param numPags Numero de paginas na hash
 */
void calculaPageRank(Hash* hashTable, int numPags);

/**
 * Funcao que retorna uma lista com todas as paginas da hash
 * @param hashTable Hash
 * @return Lista com todas as paginas
 */
Lista* getListaTodaHash(Hash* hashTable);