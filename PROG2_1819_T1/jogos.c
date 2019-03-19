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
   FILE *f = fopen(nomef,"r");

    vetor *vet=vetor_novo();
    jogo jogoatual;
    int i=0;

    
    if(f == NULL){
    perror("Erro a abrir o ficheiro.\n");
        return NULL;
    }
    while(fscanf(f,"%s %s %s %d %d %d %d",jogoatual.epoca,jogoatual.nome_casa,jogoatual.nome_fora,&(jogoatual.golos_casa),&(jogoatual.golos_fora),&(jogoatual.vermelhos_casa),&(jogoatual.vermelhos_fora))==7)
    {
        vetor_insere(vet,jogoatual,i);
        i++;
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
            eqnova.vermelhos[0]=vetor_elemento(vec,pos)->vermelhos_casa/38;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=0;
        }else if(strcmp(vetor_elemento(vec,pos)->epoca,"16/17") == 0){
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=vetor_elemento(vec,pos)->vermelhos_casa/38;
            eqnova.vermelhos[2]=0;
        }else{
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=vetor_elemento(vec,pos)->vermelhos_casa/38;
        }
    }else{
        if(strcmp(vetor_elemento(vec,pos)->epoca,"15/16") == 0){
            eqnova.vermelhos[0]=vetor_elemento(vec,pos)->vermelhos_fora/38;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=0;
        }else if(strcmp(vetor_elemento(vec,pos)->epoca,"16/17") == 0){
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=vetor_elemento(vec,pos)->vermelhos_fora/38;
            eqnova.vermelhos[2]=0;
        }else{
            eqnova.vermelhos[0]=0;
            eqnova.vermelhos[1]=0;
            eqnova.vermelhos[2]=vetor_elemento(vec,pos)->vermelhos_fora/38;
        }
    }
    return eqnova;
}

vetor_equipas *stats_equipa(vetor *vec){
    vetor_equipas *equipatotal;
    equipa eq;
    equipatotal = vetor_equipas_novo();
    int equipaigual[2]={0,0};
    vetor_equipas_insere(equipatotal,equipa_stats(vec,0,0,0),-1);
    vetor_equipas_insere(equipatotal,equipa_stats(vec,0,0,1),-1);
    printf("tamanho: %i\n", vetor_equipas_tamanho(equipatotal));
    for(int i=1; i<vetor_tamanho(vec); i++){

        for(int j=0; j<vetor_equipas_tamanho(equipatotal); j++){
            
            if(strcmp(vetor_elemento(vec,i)->nome_casa,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                eq = equipa_stats(vec,i,1,0);
                vetor_equipas_elemento(equipatotal,j)->vermelhos[0] += eq.vermelhos[0];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[1] += eq.vermelhos[1];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[2] += eq.vermelhos[2];
                equipaigual[0]++;
            }
            if(strcmp(vetor_elemento(vec,i)->nome_fora,vetor_equipas_elemento(equipatotal,j)->nome_equipa)==0){
                eq = equipa_stats(vec,i,1,1);
                vetor_equipas_elemento(equipatotal,j)->vermelhos[0] += eq.vermelhos[0];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[1] += eq.vermelhos[1];
                vetor_equipas_elemento(equipatotal,j)->vermelhos[2] += eq.vermelhos[2];
                equipaigual[1]++;
            }
        }
        if (equipaigual[0] == 0) {
            vetor_equipas_insere(equipatotal,equipa_stats(vec,i,0,0),-1);
        }
        if (equipaigual[1] == 0) {
            vetor_equipas_insere(equipatotal,equipa_stats(vec,i,0,1),-1);
        }
        equipaigual[0] = 0; equipaigual[1] = 0;
    }

    return equipatotal;
}

int equipas_ordena(vetor_equipas *v, int criterio) {

    return -1;
}


int corrige_jogo(vetor *vec, const char *nomef){


    vetor *vetorerrata;

    jogo *gamenumbers;


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
                gamenumbers=vetor_elemento(vetorerrata,i);
                vetor_atribui(vec,j,*gamenumbers);

            }
        }
    }

    return 0;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    int pontos=0;

    if(vec==NULL)
    {
        perror("O vetor introduzido nao pode ser lido\n");
        return -1;
    }

    for(int i=0;i<vetor_tamanho(vec);i++)
    {
        if(strcmp(vetor_elemento(vec,i)->nome_casa,nome_equipa)==0 && strcmp(vetor_elemento(vec,i)->epoca,epoca)==0)
        {
            
                if((vetor_elemento(vec,i)->golos_casa)>(vetor_elemento(vec,i)->golos_fora))
                {
                    pontos+=3;
                }

                if((vetor_elemento(vec,i)->golos_casa)==(vetor_elemento(vec,i)->golos_fora))
                {
                    pontos+=1;
                }
            
        }

         if(strcmp(vetor_elemento(vec,i)->nome_fora,nome_equipa)==0 && strcmp(vetor_elemento(vec,i)->epoca,epoca)==0)
        {
            
                if((vetor_elemento(vec,i)->golos_fora)>(vetor_elemento(vec,i)->golos_casa))
                {
                    pontos+=3;
                }

                if((vetor_elemento(vec,i)->golos_casa)==(vetor_elemento(vec,i)->golos_fora))
                {
                    pontos+=1;
                }
            
        }
    }   

    return pontos;
}











