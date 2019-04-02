#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
vetor* contar_correspondencia(vetor *vcp_dest)
{
	int k=0;
	vetor *v_novo = vetor_novo();
	vetor_insere(v_novo,vetor_elemento(vcp_dest,0),0);
	for(int i=0; i<vetor_tamanho(vcp_dest); i++){
		for(int j=0; j<vetor_tamanho(v_novo); j++){
			if(strcmp(vetor_elemento(vcp_dest,i),vetor_elemento(v_novo,j))==0){
				k++;
			}
		}
		if(k == 0){
			vetor_insere(v_novo,vetor_elemento(vcp_dest,i),-1);
		}
		k=0;
	}
	for(int i=0; i<vetor_tamanho(v_novo); i++){
		for(int j=0; j<vetor_tamanho(vcp_dest); j++){
			if(strcmp(vetor_elemento(v_novo,i),vetor_elemento(vcp_dest,j))==0){
				k++;
			}
		}
		printf("%s: %i cartas\n",vetor_elemento(v_novo,i), k);
		k=0;
	}
	return v_novo;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[BUFFER], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, BUFFER, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}

int main()
{
	FILE *fin;
	char linha[BUFFER];
	vetor* vrem;
	vetor* vdest;
	vetor *vcp_dest;
	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);

	vetor *cp = contar_correspondencia(vcp_dest);

	if (cp == NULL)
		printf("\nFuncao retornou erro.\n");
	else if(vetor_tamanho(cp) != 11)
		printf("\nERRO.. Numero de codigos postais distinto(%d; esperado: 11)\n", vetor_tamanho(cp));
	else {
		printf("\nNumero de codigos postais distintos: %d\n", vetor_tamanho(cp));
	}

	vetor_apaga(cp);
	vetor_apaga(vrem);
	vetor_apaga(vdest);
	vetor_apaga(vcp_dest);

	return 0;
}
