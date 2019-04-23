#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

int main(){
    arvore_bst *bst = bst_nova();
    bst_insere(bst, "G");
    bst_insere(bst, "C");
    bst_insere(bst, "A");
    bst_insere(bst, "F");
    bst_insere(bst, "L");
    bst_insere(bst, "J");
    bst_insere(bst, "V");
    bst_insere(bst, "M");
    bst_insere(bst, "N");
    bst_insere(bst, "O");

    bst_imprime(bst);
    return 0;
}