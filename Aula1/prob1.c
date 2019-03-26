#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>


int main(){
    int i;
    int somatorio = 0,j;
    float abc[26]={0};
    int caracter;
    FILE  *f;
    f = fopen("lusiadas.txt","r");
    do{
        caracter = getc(f);
        caracter=tolower(caracter);
        for(i = 97; i<123; i++){
            if (caracter == i){
                j=122-i;
                j = 25-j;
                abc[j]++;
            }
        }
        if ((caracter >= 192 && caracter <= 195) || (caracter >= 224 && caracter <= 227)){
            abc[0]++;
        }
        if ((caracter >= 211 && caracter <= 213) || (caracter >= 243 && caracter <= 245)){
            abc[14]++;
        }
        if (caracter == 205 || caracter == 237){
            abc[8]++;
        }
        if ((caracter >= 201 && caracter <= 202) || (caracter >= 233 && caracter <= 234)){
            abc[4]++;
        }
        if (caracter == 218 || caracter == 250){
            abc[20]++;
        }
        if (caracter == 218 || caracter == 250){
            abc[2]++;
        }
    }while(caracter != EOF);
    for(i=0;i<26; i++){
        somatorio += abc[i];
    }
    for(i=0;i<26; i++){
        abc[i]=(abc[i]/somatorio)*100;
    }
    printf("numero de letras n ficheiro: %i\n", somatorio);
    for(i=97;i<123; i++){
        printf("letra %c = %.2f\n", (char)i, abc[i-97]);
    
    }
}