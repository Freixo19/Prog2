#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

lista* ler_substring(lista *l,char substring){
    lista *tokenlista;
    for(int i=0;i<lista_tamanho(l); i++){
        if ((strstr((lista_elemento(l, i)->str), substring)) != NULL){
            lista_insere(tokenlista, lista_elemento(l, i)->str, NULL);
        }
    }
    return tokenlista;
}
lista* apagar_substring(lista *l,char *substring){ 
    lista *tokenlista;
    for(int i=0;i<lista_tamanho(l); i++){
        if ((strstr((lista_elemento(l, i)->str), substring)) != NULL){
            lista_insere(tokenlista, lista_elemento(l, i)->str, NULL);
        }
    }
    return tokenlista;
}

int main(){
    FILE *f;
    lista *listanova, *sublista;
    f = fopen("arquivo.txt","r");
    listanova = lista_nova();
    char token[100];
    while((fgets(token, 100, f))){
        lista_insere(listanova, token, NULL);
    }
    for(int i=0;i<lista_tamanho(listanova); i++){
        printf("Pos %d -> %s", i, lista_elemento( listanova, i)->str);
    }
    gets(token);
    sublista = ler_substring(listanova, token);
    printf("Jogos contendo %s\n", token);
    for(int i=0;i<lista_tamanho(sublista); i++){
        printf("Pos %d -> %s", i, lista_elemento( sublista, i)->str);
    }

}
