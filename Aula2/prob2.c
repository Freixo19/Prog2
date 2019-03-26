#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    vetor *v;
    char token[100];
    int pos;
    v = vetor_novo();
    for(int i=0; i<5; i++){
        gets(token);
        vetor_insere(v, token, i);
    }
    for(int i=0; i<5; i++){
        puts(vetor_elemento(v,i));
    }
    gets(token);
    pos = vetor_pesquisa(v, token);
    if (pos != -1){
        vetor_remove(v,pos);
    }
    vetor_ordena(v);
    for(int i=0; i<5; i++){
        puts(vetor_elemento(v,i));
    }
}