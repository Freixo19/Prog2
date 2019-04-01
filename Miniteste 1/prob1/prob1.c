#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "pilha.h"


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

void quicksort(lista *lst,int inicio,int fim){
	int i=inicio, j=fim, pivot= (fim+inicio)/2;
	char *aux;
	aux = (char*)malloc(sizeof(char)*50); 
	while(i<=j){
		while(strcmp(lista_elemento(lst,i)->str,lista_elemento(lst,pivot)->str)<0){
			i++;
		}
		while(strcmp(lista_elemento(lst,j)->str,lista_elemento(lst,pivot)->str)>0){
			j--;
		}
		if(i<=j){
			strcpy(aux,lista_elemento(lst,i)->str);
			lista_atribui(lst,lista_elemento(lst,i), lista_elemento(lst,j)->str);
			lista_atribui(lst,lista_elemento(lst,j), aux);
			i++;
			j--;
		}
	}
	if(inicio < j){
		quicksort(lst,inicio,j);
	}
	if(i < fim){
		quicksort(lst,i,fim);
	}
}


/*** problema 1.1 ***/
lista* junta_ordenada(lista *lst1, lista *lst2)
{
	/* complexidade do algoritmo: O(n*ln(n)) */
	lista *lstn = lista_nova();
	for(int i=0; i<lista_tamanho(lst1); i++){
		lista_insere(lstn, lista_elemento(lst1,i)->str, NULL);
	}
	for(int j=0; j<lista_tamanho(lst2); j++){
		lista_insere(lstn, lista_elemento(lst2,j)->str, NULL);
	}
	quicksort(lstn,0,lista_tamanho(lstn)-1);
	return lstn;
}

/*** problema 1.2 ***/
int move_para_inicio(lista *lst, char *str1)
{
	int i=0;
	for(int j=0; j<lista_tamanho(lst); j++){
		if (strstr(lista_elemento(lst,j)->str,str1) != NULL){
			lista_insere(lst, lista_elemento(lst,j)->str,lst->inicio);
			lista_remove(lst,lista_elemento(lst,j+1));
			i++;
		}
	}
	return i;
}

/*** problema 1.3 ***/
int retira_de_pilha(pilha *p, char *titulo)
{
	pilha *pilhaux = pilha_nova();
	int i=0;
	while(pilha_tamanho(p) != 0){
		if(strcmp(pilha_top(p)->elemento, titulo)==0){
			i++;
			break;
		} else{
			pilha_push(pilhaux,pilha_top(p)->elemento);
			pilha_top()
		}
	}
	return i;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

lista* lerParaLista(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	lista* l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}

	return l;
}

pilha* lerParaPilha(FILE* ficheiro)
{
	char buffer[256], *nlptr;
	pilha* p;

	if (ficheiro == NULL)
		return NULL;

	p = pilha_nova();

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		pilha_push(p,buffer);
	}
	return p;
}

void imprimeLista(lista *l, unsigned int n) {
	if (l->tamanho<n)
		printf("ERRO... Lista possui menos de %d elementos\n",n);
	unsigned int i;
	l_elemento *aux = l->inicio;
	for (i=0; i<n; i++) {
		printf("elemento %d: %s\n", i,aux->str);
		aux = aux->proximo;
	}
}

int main()
{
	FILE *f;
	lista *l1=NULL, *l2=NULL, *l=NULL;
	pilha *p;
	int nmov, res;
	char *tit1 = "Mau Tempo no Canal";
	char *tit2 = "A Criacao do Tempo, do Bem e do Mal";


	/* testes */
	f = fopen("livros1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l1 = lerParaLista(f);
	fclose(f);

	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lerParaLista(f);
	fclose(f);

	/* inicio teste prob1.1 */
	l = junta_ordenada(l1, l2);
	if(l) {
		printf("\nLista resultante contem %d livros.\n", lista_tamanho(l));
		if(lista_tamanho(l) != 60)
			printf("ERRO.. Tamanho da lista incorreto(tamanho: %d; esperado: 60)\n", lista_tamanho(l));
		else {
			printf("Primeiros 6 livros:\n");
			imprimeLista(l,6);
		}
	}
	else
		printf("\nERRO.. junta_ordenadas retornou NULL\n");
	/* fim teste prob1.1 */


	/* inicio teste prob1.2 */
	f = fopen("livros.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	lista_apaga(l);
	l = lerParaLista(f);
	fclose(f);

	nmov = move_para_inicio(l,"dia");
	printf("\nForam movidos %d livros\n", nmov);
	printf("A lista contem %d livros\n", lista_tamanho(l));
	if (nmov!=8)
		printf("ERRO.. Numero de livros movidos incorreto (movidos: %d; esperado: 8\n",nmov);
	else if(lista_tamanho(l) != 535)
		printf("ERRO.. Lista incorreta (tamanho: %d; esperado: 535)\n", lista_tamanho(l));
	else
		printf("9o livro da lista: %s\n", lista_elemento(l,8)->str);
	/* fim teste prob1.2 */


	/* inicio teste prob1.3 */
	f = fopen("livros2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	p = lerParaPilha(f);
	fclose(f);

	res = retira_de_pilha(p, tit1);
	if (res==1)
		printf("\nERRO.. '%s' nao existe na pilha\n", tit1);
	else if (pilha_tamanho(p)!=32)
		printf("\nERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 32)\n",pilha_tamanho(p));
	else
		printf("\n'%s' nao existe na pilha, pilha inalterada\n", tit1);
	
	res = retira_de_pilha(p, tit2);
	if (res==0)
		printf("ERRO.. '%s' existe na pilha\n", tit2);
	else if (pilha_tamanho(p)!=31)
		printf("ERRO.. Numero de elementos na pilha incorreto (existentes: %d; esperado: 31)\n",pilha_tamanho(p));
	else {
		tit2="Um Deus Passeando pela Brisa da Tarde";
		if (strcmp(pilha_top(p),tit2)!=0)
			printf("ERRO.. Topo da pilha incorreto (existente: '%s'; esperado: '%s')\n",pilha_top(p), tit1);
		else {
			printf("'%s' retirado da pilha\n", tit2);
			printf("Numero de elementos da pilha: %d\n", pilha_tamanho(p));
		}
	}
	puts("");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	pilha_apaga(p);

	return 0;
}
