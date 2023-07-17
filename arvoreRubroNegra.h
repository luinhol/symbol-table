/** Define um tad ArvoreRubroNegra de Termos.
 * @file arvoreRubroNegra.h
 * @author Lucas Pereira Taborda
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "termo.h"

#define RED true
#define BLACK false

/**
 * Tad arvore rubro negra de termos
 */
typedef struct node RBT;

/**
 * Funcao que cria um no da arvore
 * @param key Chave utilizada para inserção e busca (string do termo)
 * @param color Cor do no
 * @param termo Termo a ser inserido
 * @return No criado
 */
RBT* create_node(char* key, bool color, Termo* termo);

/**
 * Funcao que procura uma chave na arvore
 * @param n Arvore
 * @param key Chave a ser procurada
 * @return Termo quando encontrado, NULL quando nao encontrado
 */
Termo* search(RBT *n, char* key);

/**
 * Funcao que verifica se um no e vermelho
 * @param x No a ser verificado
 * @return true quando e vermelho, false para o contrario
 */
bool is_red(RBT *x);

/**
 * Funcao que rotaciona a esquerda
 * @param h No a ser rotacionado
 * @return No retornado para o pai
 */
RBT* rotate_left(RBT *h);

/**
 * Funcao que rotaciona a direita
 * @param h No a ser rotacionado
 * @return No retornado para o pai
 */
RBT* rotate_right(RBT *h);

/**
 * Funcao que troca a cor dos nos
 * @param h No pai a ser trocado as cores
 */
void flip_colors(RBT *h);

/**
 * Funcao que insere um no na arvore
 * @param h Raiz da subarvore
 * @param key Chave do novo no
 * @param termo Termo a ser inserido
 * @return Ponteiro para o no
 */
RBT* RBT_insert(RBT *h, char* key, Termo* termo);

/**
 * Funcao que deleta uma arvore
 * @param rbt Arvore a ser deletada
 */
void deleteRBT(RBT* rbt);

/**
 * Funcao que compara duas chaves
 * @param key1 String 1
 * @param key2 String 2
 * @return Retorno da funcao strcasecmp
 */
int compare(char* key1, char* key2);

/**
 * Funcao que imprime uma arvore
 * @param rbt Arvore a ser impressa
 */
void printRBT(RBT* rbt);