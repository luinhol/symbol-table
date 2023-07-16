#include "arvoreRubroNegra.h"

typedef struct node RBT;

struct node {
    bool color;
    char* key;
    Termo* termo;
    RBT *l, *r;
};

RBT* create_node(char* key, bool color, Termo* termo){
    RBT* new = (RBT*)malloc(sizeof(RBT));

    new->key = key;
    new->termo = termo;
    new->color = color;
    new->l = NULL;
    new->r = NULL;

    return new;
}

Termo* search(RBT *n, char* key) {
    while (n != NULL) {
        int cmp;
        cmp = compare(key, n->key);
        if (cmp < 0){
            n = n->l;
        }
        else if (cmp > 0){
            n = n->r;
        }
        else{
            return n->termo;
        }
    }
    return NULL;
}

bool is_red(RBT *x) {
    if (x == NULL){
        return BLACK;
    }
    return x->color; //RED == true
}

RBT* rotate_left(RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT* rotate_right(RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

RBT* RBT_insert(RBT *h, char* key, Termo* termo) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_node(key, RED, termo);
    }

    int cmp = compare(key, h->key);

    if (cmp < 0) {
        h->l = RBT_insert(h->l, key, termo);
    }
    else if (cmp > 0) {
        h->r = RBT_insert(h->r, key, termo);
    }
    else /*cmp == 0*/ {
        h->termo = termo;
        // printf("termo repetido\n");
    }
    // Lean left.
    if (is_red(h->r) && !is_red(h->l)) {
        h = rotate_left(h);
    }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l)) {
        h = rotate_right(h);
    }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r)) {
        flip_colors(h);
    }
    return h;
}

void deleteRBT(RBT* rbt){
    if(rbt != NULL)
    {
        deleteRBT(rbt->l);
        deleteRBT(rbt->r);
        liberaTermo(rbt->termo);
        free(rbt);
    }
}

int compare(char* key1, char* key2){
    return strcasecmp(key1, key2);
}

void printRBT(RBT* rbt){
    if(rbt != NULL)
    {
        printRBT(rbt->l);
        printf("\nTermo: %s \nPaginas: ", getNomeTermo(rbt->termo));
        imprimeHash(getHash(rbt->termo));
        printRBT(rbt->r);
    }
}