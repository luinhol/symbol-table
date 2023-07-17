/** Define um tad Arquivo.
 * @file arquivo.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "lista.h"
#include "hash.h"
#include "arvoreRubroNegra.h"

/**
 * Estrutura que armazena dados da entrada
 */
typedef struct entrada Entrada;

Entrada* inicializaEntrada(int numPags, int numStopWords, Hash* index, RBT* stopWords, RBT* palavras);

/**
 * Função que adquire os dados de entrada de um arquivo
 * @param indexFile Arquivo de index
 * @param stopWordsFile Arquivo de stopWords
 * @param grafoFile Arquivo de grafo
 * @param nomeDirPages Nome do diretorio das páginas
 * @return Estrutura com os dados de entrada
 */
Entrada* setDados(FILE *indexFile, FILE *stopWordsFile, FILE *grafoFile, char* nomeDirPages);

/**
 * Funcao que retorna o numero de linhas de um arquivo
 * @param entrada Arquivo
 * @return Numero de linhas do arquivo
 */
int getNumLines(FILE *arquivo);

/**
 * Funcao que le o arquivo de index
 * @param indexFile Arquivo de index
 * @param numPags Numero de paginas do arquivo de index
 * @return Hash de todas as paginas
 */
Hash* getIndexFile(FILE *indexFile, int numPags);

/**
 * Funcao que le o arquivo de grafo
 * @param graphFile Arquivo de grafo
 * @param numPags Numero de paginas
 */
void getGraphFile(Hash* hash, FILE *graphFile, int numPags);

/**
 * Funcao que realiza a leitura de todos os arquivos dentro da pasta pages
 * @param stopWords Arvore de stopWords ja preenchida
 * @param numPags Numero de paginas
 * @param hash Hash das paginas
 * @param dir Diretorio de pages
 * @return Arvore de todos os termos de todas as paginas
 */
RBT* setTermos(RBT* stopWords, int numPags, Hash* hash, char* dir);

/**
 * Funcao que realiza a leitura de uma pagina especifica
 * @param rbt Arvore de termos
 * @param numPags Numero de paginas
 * @param arqPagina Arquivo de pagina
 * @param stopWords Arvore de stopWords
 * @param pagina Pagina do arquivo
 * @return Arvore de termos
 */
RBT* leituraPagina(RBT* rbt, int numPags, FILE* arqPagina, RBT* stopWords, Pagina* pagina);

/**
 * Funcao que realiza leitura do arquivo de stopWords
 * @param stopWordsFile Arquivo de stopWords
 * @param numStopWords Numero de stopWords
 * @return Arvore de stopWords
 */
RBT* getStopWordsFile(FILE *stopWordsFile, int numStopWords);

/**
 * Destrutor de entrada
 * @param entrada Estrutura de entrada
 */
void limpaDadosEntrada(Entrada *entrada);

/**
 * Funcao que realiza a pesquisa de um conjunto de palavras separadas por espaco
 * @param entrada Estrutura de entrada
 * @param palavras String contendo as palavras, separadas por espaço
 */
void realizaPesquisa(Entrada* entrada, char* palavras);