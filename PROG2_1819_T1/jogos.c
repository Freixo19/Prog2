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

equipa equipa_stats(vetor *vec, int pos, int equipaigual, int casafora){
    //o casafora serve para ver se o estamos a adicionar informações sobre a equipa que jogou em casa ou fora, sendo casafora=0 equipa que jogou em casa e casafora=1 a equipa que jogou fora.
    equipa eqnova;
    //ver se isto nao da o berro ao nao guardar-mos o nome ¯\_(ツ)_/¯
    if(equipaigual == 0){
        if(casafora == 0){
            strcpy(eqnova.nome_equipa,vetor_elemento(vec,pos)->nome_casa);
        }else{
            strcpy(eqnova.nome_equipa,vetor_elemento(vec,pos)->nome_fora);
        }
    }
    if(casafora == 0){
        eqnova.diff_golos=(vetor_elemento(vec,pos)->golos_casa)-(vetor_elemento(vec,pos)->golos_fora);
    }else{
        eqnova.diff_golos=(vetor_elemento(vec,pos)->golos_fora)-(vetor_elemento(vec,pos)->golos_casa);
    }
    if(casafora == 0){
        if(strcmp(vetor_elemento(vec,pos)->epoca,"15/16") == 0){
            eqnova.vermelhos[0]=vetor_elemento(vec,pos)->vermelhos_casa;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=0;
        }else if(strcmp(vetor_elemento(vec,pos)->epoca,"16/17") == 0){
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=vetor_elemento(vec,pos)->vermelhos_casa;
            eqnova.vermelhos[2]=0;
        }else{
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=vetor_elemento(vec,pos)->vermelhos_casa;
        }
    }else{
        if(strcmp(vetor_elemento(vec,pos)->epoca,"15/16") == 0){
            eqnova.vermelhos[0]=vetor_elemento(vec,pos)->vermelhos_fora;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=0;
        }else if(strcmp(vetor_elemento(vec,pos)->epoca,"16/17") == 0){
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=vetor_elemento(vec,pos)->vermelhos_fora;
            eqnova.vermelhos[2]=0;
        }else{
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=vetor_elemento(vec,pos)->vermelhos_fora;
        }
    }
    return eqnova;
}

vetor_equipas *stats_equipa(vetor *vec){
    vetor_equipas *equipatotal;
    equipa eq;
    equipatotal = vetor_equipas_novo();
    int equipaigual=0;
    vetor_equipas_insere(equipatotal,equipa_stats(vec,0,0,0),-1);
    vetor_equipas_insere(equipatotal,equipa_stats(vec,0,0,1),-1);
    for(int i=1; i<vetor_tamanho(vec); i++){

        for(int j=0; j<vetor_equipas_tamanho(equipatotal); j++){
            
            if(strcmp(vetor_elemento(vec,i)->nome_casa,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                eq = equipa_stats(vec,i,1,0);
                vetor_equipas_elemento(equipatotal,j)->vermelhos[0] += eq.vermelhos[0];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[1] += eq.vermelhos[1];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[2] += eq.vermelhos[2];
                equipaigual++;
            }
            if (equipaigual == 0) {
                vetor_equipas_insere(equipatotal,equipa_stats(vec,i,0,0),-1);
            }
            equipaigual=0;
            if(strcmp(vetor_elemento(vec,i)->nome_fora,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                eq = equipa_stats(vec,i,1,1);
                vetor_equipas_elemento(equipatotal,j)->vermelhos[0] += eq.vermelhos[0];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[1] += eq.vermelhos[1];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[2] += eq.vermelhos[2];
                equipaigual++;
            }
            if (equipaigual == 0) {
                vetor_equipas_insere(equipatotal,equipa_stats(vec,i,0,1),-1);
            }
            equipaigual=0;
        }
    }
    for(int j=0; j<vetor_equipas_tamanho(equipatotal); j++){
        vetor_equipas_elemento(equipatotal,j)->vermelhos[0] /= 38;
        vetor_equipas_elemento(equipatotal,j)->vermelhos[1] /= 38;
        vetor_equipas_elemento(equipatotal,j)->vermelhos[2] /= 38;
    }
    return equipatotal;
}


int equipas_ordena(vetor_equipas *v, int criterio) {

    return -1;
}


int corrige_jogo(vetor *vec, const char *nomef){

    vetor *vetorerrata;

    vetorerrata=jogos_load(nomef);

    if(vetorerrata==NULL)
    {
        perror("impossivel ler vetor\n");

        return -1;
    }

    for(int i=0;i<vetor_tamanho(vetorerrata);i++)
    {
        for(int j=0;j<vetor_tamanho(vec);j++)
        {
            if(strcmp(vetor_elemento(vetorerrata,i)->epoca,vetor_elemento(vec,j)->epoca)==0 && strcmp(vetor_elemento(vetorerrata,i)->nome_casa,vetor_elemento(vec,j)->nome_casa)==0 && strcmp(vetor_elemento(vetorerrata,i)->nome_fora,vetor_elemento(vec,j)->nome_fora)==0 )
            {
                vetor_elemento(vec,j)->golos_casa=vetor_elemento(vetorerrata,i)->golos_casa;
                vetor_elemento(vec,j)->golos_fora=vetor_elemento(vetorerrata,i)->golos_fora;
                vetor_elemento(vec,j)->vermelhos_casa=vetor_elemento(vetorerrata,i)->vermelhos_casa;
                vetor_elemento(vec,j)->vermelhos_fora=vetor_elemento(vetorerrata,i)->vermelhos_fora;

            }
        }
    }

    return 0;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    return -1;
}











