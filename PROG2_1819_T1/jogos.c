/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


vetor* jogos_load(const char *nomef){
    FILE *f;
    vetor *vet;
    jogo jogoatual;
    int valor;
    vet = vetor_novo();
    char totalstring[50], *token;
    f = fopen(nomef,"r");
    if(fp == NULL) {
    perror("Erro a abrir o ficheiro.\n");
        return-1;
    }
    while(fgets(totalstring, 50, f)!=NULL){
        token = strtok(totalstring," ");
        strcpy(jogoatual->epoca, token);
        token = strtok(NULL," ");
        strcpy(jogoatual->nome_casa, token);
        token = strtok(NULL," ");
        strcpy(jogoatual->nome_fora, token);
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual->golos_casa=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual->golos_fora=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual->vermelhos_casa=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual->vermelhos_fora=valor;
        vetor_insere(vet, jogo jogoatual, -1);
    }
    return vet;
}


int jogos_save(vetor *vec, const char *nomef){

    return -1;
}


vetor_equipas *stats_equipa(vetor *vec){

    return NULL;
}


int equipas_ordena(vetor_equipas *v, int criterio){

    return -1;
}


int corrige_jogo(vetor *vec, const char *nomef){

    return -1;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    return -1;
}






