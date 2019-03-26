#include <stdio.h>
#include <stdlib.h>

int *criavetor(int n){
    int *pi;
    pi = (int*)calloc(n,sizeof(int));
    return pi;
}
void sorter(int *v, int *par, int *impar, int n){
    int p=0, i=0;
    for(int r=0; r<n; r++){
        if(v[r]%2==0){
            par[p] = v[r];
            p++;
        }else{
            impar[i]= v[r];
            i++;
        }
    }
}
void imprimirvetor(int *v,int n){
    int r;
    for(r=0; r<n; r++){
        printf("%d ", v[r]);
    }
    printf("]\n");
}
int main() {
    int n,p=0,i=0, r;
    printf("Tamanho do vator: ");
    scanf("%d",&n);
    int *v,*par,*impar;
    v = criavetor(n);
    for(r=0; r<n; r++){
        printf("%dº elemento: ", r+1);
        scanf("%d", &(v[r]));
        if(v[r]%2==0){
            p++;
        }else{
            i++;
        }
    }
    printf("-%d\n", p);
    printf("--%d\n", i);
    par = criavetor(p);
    impar = criavetor(i);
    sorter(v, par, impar, n);
    printf("vetor original: [ ");
    imprimirvetor( v, n);
    printf("vetor pares: [ ");
    imprimirvetor( par, p);
    printf("vetor impares: [ ");
    imprimirvetor( impar, i);
}