#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	armazen *a_novo = malloc(sizeof(armazem));
	if(a_novo == NULL){
		free(a_novo);
		return NULL;
	}
	a_novo->comprimento = comprimento;
	a_novo->altura = altura;
	a_novo->contentores = fila_nova();
	return a_novo;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	/* devolve vazio */
	return 1;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	/* devolve nao cheio */
	return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	/* devolve nao ha' espaco */
	return 0;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	return NULL;
}
