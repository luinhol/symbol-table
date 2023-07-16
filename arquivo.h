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

Entrada* inicializaEntrada(int numPags, int numStopWords, Hash* index, char** stopWords, RBT* palavras);

/**
 * Função que adquire os dados de entrada de um arquivo
 * @param arquivo Arquivo de entrada
 * @return Estrutura com os dados de entrada
 */
Entrada* setDados(FILE *indexFile, FILE *stopWordsFile, FILE *grafoFile, char* nomeDirPages);

/**
 * Funcao que retorna a lista de adjacencia de um no (indice)
 * @param entrada Estrutura de entrada
 * @param indice indice de um No (id)
 * @return Lista de adjacencia do No Indice
 */
Lista* getLista(Entrada* entrada, int indice);

int getNumLines(FILE *arquivo);

Hash* getIndexFile(FILE *indexFile, int numPags);

void getGraphFile(Hash* hash, FILE *indexFile, int numPags);

RBT* setTermos(int numPags, Hash* hash, char* dir);

RBT* leituraPagina(RBT* rbt, int numPags, FILE* arqPagina, Pagina* pagina);

char** getStopWordsFile(FILE *stopWordsFile, int numStopWords);

/**
 * Destrutor de entrada
 * @param entrada Estrutura de entrada
 */
void limpaDadosEntrada(Entrada *entrada);

/**
 * Funcao que imprime o arquivo de saida
 * @param saida Arquivo de saida
 * @param tamCaminho tamanho do caminho percorrido
 * @param caminhoPercorrido trajeto percorrido
 * @param distanciaTotal distancia total percorrida
 * @param tempo tempo decorrido
 */
void escreveSaida(Entrada* entrada, FILE* saida);

void realizaPesquisa(Entrada* entrada, char* palavras);