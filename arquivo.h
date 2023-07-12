/** Define um tad Arquivo.
 * @file arquivo.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "hash.h"
#include <sys/types.h>

/**
 * Estrutura que armazena dados da entrada
 */
typedef struct entrada Entrada;

/**
 * Função que adquire os dados de entrada de um arquivo
 * @param arquivo Arquivo de entrada
 * @return Estrutura com os dados de entrada
 */
Entrada* setDados(FILE *index, FILE *stopWords);

/**
 * Funcao que retorna a lista de adjacencia de um no (indice)
 * @param entrada Estrutura de entrada
 * @param indice indice de um No (id)
 * @return Lista de adjacencia do No Indice
 */
Lista* getLista(Entrada* entrada, int indice);

int getNumLines(FILE *arquivo);

Hash* getIndexFile(FILE *indexFile, int numPags);

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
void escreveSaida(FILE* saida);