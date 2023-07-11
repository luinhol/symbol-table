/** Define um tad Arquivo.
 * @file arquivo.h
 * @author Lucas Pereira Taborda
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atualizacao.h"
#include "lista.h"
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
Entrada* setDados(FILE *index, FILE *stopWords, FILE *graph);

/**
 * Funcao conta a quantidade de atualizacoes do arquivo de entrada
 * @param arquivo Arquivo de entrada
 * @param numAresta numero de arestas do arquivo de entrada
 * @return numero de atualizacoes
 */
int contaAtualizacoes(FILE* arquivo, int numArestas);

/**
 * Funcao que retorna o numero de vertices da entrada
 * @param entrada Estrutura de entrada
 * @return numero de vertices
 */
int getNumVertices(Entrada* entrada);

/**
 * Funcao que retorna o numero de arestas da entrada
 * @param entrada Estrutura de entrada
 * @return numero de arestas
 */
int getNumArestas(Entrada* entrada);

/**
 * Funcao que retorna o numero de atualizacoes da entrada
 * @param entrada Estrutura de entrada
 * @return numero de atualizacoes
 */
int getNumAtualizacoes(Entrada* entrada);

/**
 * Funcao que retorna o No de Origem informado pela entrada
 * @param entrada Estrutura de entrada
 * @return No de Origem
 */
int getS(Entrada* entrada);

/**
 * Funcao que retorna o No de Destino informado pela entrada
 * @param entrada Estrutura de entrada
 * @return No de Destino
 */
int getT(Entrada* entrada);

/**
 * Funcao que retorna a lista de adjacencia de um no (indice)
 * @param entrada Estrutura de entrada
 * @param indice indice de um No (id)
 * @return Lista de adjacencia do No Indice
 */
Lista* getLista(Entrada* entrada, int indice);

/**
 * Funcao que retorna uma atualizacao do vetor de atualizacoes
 * @param entrada Estrutura de entrada
 * @param indice indice da atualizacao no vetor de atualizacoes
 * @return Atualizacao
 */
Atualizacao* getAtualizacao(Entrada* entrada, int indice);

/**
 * Funcao que retorna a velocidade media inicial
 * @param entrada Estrutura de entrada
 * @return velocidade media inicial
 */
double getVelMedia(Entrada* entrada);

/**
 * Destrutor de entrada
 * @param entrada Estrutura de entrada
 */
void limpaDadosEntrada(Entrada *entrada);

/**
 * Funcao que executa uma atualizacao de dados da entrada
 * @param entrada Estrutura de entrada
 * @param j indice da atualizacao a ser realizada
 */
void atualiza(Entrada* entrada, int j);

/**
 * Funcao que verifica se ainda existe alguma atualizacao que ainda nao foi executada
 * @param entrada Estrutura de entrada
 * @param indice indice de uma atualizacao
 * @param tempo tempo atual
 * @return True para quando ainda ha atualizacao e False para o contrario
 */
bool aindaTemAtt(Entrada* entrada, int indice, double tempo);

/**
 * Funcao que imprime o arquivo de saida
 * @param saida Arquivo de saida
 * @param tamCaminho tamanho do caminho percorrido
 * @param caminhoPercorrido trajeto percorrido
 * @param distanciaTotal distancia total percorrida
 * @param tempo tempo decorrido
 */
void escreveSaida(FILE* saida, int tamCaminho, int* caminhoPercorrido, double distanciaTotal, double tempo);