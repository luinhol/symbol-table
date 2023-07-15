#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "termo.h"

#define RED true
#define BLACK false

typedef struct node RBT;

RBT* create_node(char* key, bool color, Termo* termo);

Termo* search(RBT *n, char* key);

bool is_red(RBT *x);

RBT* rotate_left(RBT *h);

RBT* rotate_right(RBT *h);

void flip_colors(RBT *h);

RBT* RBT_insert(RBT *h, char* key, Termo* val);

void deleteRBT(RBT* rbt);

int compare(char* key1, char* key2);

void printRBT(RBT* rbt);