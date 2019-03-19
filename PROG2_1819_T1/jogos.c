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
    if(f == NULL) {
    perror("Erro a abrir o ficheiro.\n");
        return NULL;
    }
    while(fgets(totalstring, 50, f)!=NULL){
        token = strtok(totalstring," ");
        strcpy(jogoatual.epoca, token);
        token = strtok(NULL," ");
        strcpy(jogoatual.nome_casa, token);
        token = strtok(NULL," ");
        strcpy(jogoatual.nome_fora, token);
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual.golos_casa=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual.golos_fora=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual.vermelhos_casa=valor;
        token = strtok(NULL," ");
        valor=atoi(token);
        jogoatual.vermelhos_fora=valor;
        vetor_insere(vet, jogoatual, -1);
    }
    fclose(f);
    return vet;
}


int jogos_save(vetor *vec, const char *nomef){
    int i;
    FILE *f;
    f = fopen(nomef,"w");
    if(f == NULL){
        perror("Erro a criar/editar o ficheiro.\n");
        return -1;
    }
    for(i=0; i<vetor_tamanho(vec); i++){
        fprintf(f,"%s %s %s %i %i %i %i\n",vetor_elemento(vec, i)->epoca,vetor_elemento(vec, i)->nome_casa,vetor_elemento(vec, i)->nome_fora,vetor_elemento(vec, i)->golos_casa,vetor_elemento(vec, i)->golos_fora,vetor_elemento(vec, i)->vermelhos_casa,vetor_elemento(vec, i)->vermelhos_fora);
    }
    fclose(f);
    return i;
}


vetor_equipas *stats_equipa(vetor *vec){
    vetor_equipas *equipatotal;
    equipa equipanova;
    equipatotal = vetor_equipas_novo();
    int equipaigual=0;
    for(int i=0; i<vetor_tamanho(vec); i++){
        strcpy(equipanova.nome_equipa,vetor_elemento(vec,i)->nome_casa);
        equipanova.diff_golos=(vetor_elemento(vec,i)->golos_casa)-(vetor_elemento(vec,i)->golos_fora);
        if(strcmp(vetor_elemento(vec,i)->epoca,"15/16") == 0){
            equipanova.vermelhos[0]+=vetor_elemento(vec,i)->vermelhos_casa;
        }else if(strcmp(vetor_elemento(vec,i)->epoca,"16/17") == 0){
            equipanova.vermelhos[1]+=vetor_elemento(vec,i)->vermelhos_casa;
        }else{
            equipanova.vermelhos[2]+=vetor_elemento(vec,i)->vermelhos_casa;
        }
        vetor_equipas_insere(equipatotal,equipanova,-1);
        for(int j=0; j<vetor_equipas_tamanho(equipatotal); j++){
            printf("contador 2: %i\n", j);
            if(strcmp(vetor_elemento(vec,i)->nome_casa,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                vetor_equipas_elemento(equipatotal,j)->diff_golos=(vetor_elemento(vec,i)->golos_casa)-(vetor_elemento(vec,i)->golos_fora);
                if(strcmp(vetor_elemento(vec,i)->epoca,"15/16") == 0){
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[0]+=vetor_elemento(vec,i)->vermelhos_casa;
                }else if(strcmp(vetor_elemento(vec,i)->epoca,"16/17") == 0){
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[1]+=vetor_elemento(vec,i)->vermelhos_casa;
                }else{
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[2]+=vetor_elemento(vec,i)->vermelhos_casa;
                }
                equipaigual++;
            }
            printf("tamanho: %i\n", equipaigual);
            printf("tamanho: %i\n", i);
            if(equipaigual==0){
                strcpy(equipanova.nome_equipa,vetor_elemento(vec,i)->nome_casa);
                equipanova.diff_golos=(vetor_elemento(vec,i)->golos_casa)-(vetor_elemento(vec,i)->golos_fora);
                if(strcmp(vetor_elemento(vec,i)->epoca,"15/16") == 0){
                    equipanova.vermelhos[0]+=vetor_elemento(vec,i)->vermelhos_casa;
                }else if(strcmp(vetor_elemento(vec,i)->epoca,"16/17") == 0){
                    equipanova.vermelhos[1]+=vetor_elemento(vec,i)->vermelhos_casa;
                }else{
                    equipanova.vermelhos[2]+=vetor_elemento(vec,i)->vermelhos_casa;
                }
            vetor_equipas_insere(equipatotal,equipanova,-1);
        }
        equipaigual=0;
        if(strcmp(vetor_elemento(vec,i)->nome_fora,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                vetor_equipas_elemento(equipatotal,j)->diff_golos=(vetor_elemento(vec,i)->golos_fora)-(vetor_elemento(vec,i)->golos_casa);
                if(strcmp(vetor_elemento(vec,i)->epoca,"15/16") == 0){
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[0]+=vetor_elemento(vec,i)->vermelhos_fora;
                }else if(strcmp(vetor_elemento(vec,i)->epoca,"16/17") == 0){
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[1]+=vetor_elemento(vec,i)->vermelhos_fora;
                }else{
                    vetor_equipas_elemento(equipatotal,j)->vermelhos[2]+=vetor_elemento(vec,i)->vermelhos_fora;
                }
                equipaigual++;
        }
        if(equipaigual==0){
            strcpy(equipanova.nome_equipa,vetor_elemento(vec,i)->nome_fora);
            equipanova.diff_golos=(vetor_elemento(vec,i)->golos_fora)-(vetor_elemento(vec,i)->golos_casa);
            if(strcmp(vetor_elemento(vec,i)->epoca,"15/16") == 0){
                    equipanova.vermelhos[0]+=vetor_elemento(vec,i)->vermelhos_fora;
                }else if(strcmp(vetor_elemento(vec,i)->epoca,"16/17") == 0){
                    equipanova.vermelhos[1]+=vetor_elemento(vec,i)->vermelhos_fora;
                }else{
                    equipanova.vermelhos[2]+=vetor_elemento(vec,i)->vermelhos_fora;
                }
            vetor_equipas_insere(equipatotal,equipanova,-1);
            equipaigual=0;
        }}
    }
    printf("tamanho: %i\n", equipatotal->tamanho);
    return equipatotal;
}


int equipas_ordena(vetor_equipas *v, int criterio) {

    return -1;
}


int corrige_jogo(vetor *vec, const char *nomef){

    return -1;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    return -1;
}











