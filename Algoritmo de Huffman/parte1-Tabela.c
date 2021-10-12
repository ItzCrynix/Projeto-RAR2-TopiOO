#include<stdio.h>
#include<stdlib.h>

void main() {

    // Cria um vetor de char, uma frase que vai ser compactada
    unsigned char texto[] = "Vamos aprender a programa";

    // Cria um vetor de int com 256 de tamanho (o mesmo da tabela ASCII completa)
    unsigned int tab[256];

    // Inicializa int para os for's
    int i;

    // Preencher tabela com 0
    for(i = 0; i < 256; i++)
        tab[i] = 0;

    // Reutiliza a variavel i para o proximo while
    i = 0;

    // 
    while(texto[i] != '\0') { // o '\0' é para identificar o final de uma string
        tab[texto[i]]++;
        i++;
    }

    // Reutiliza a variavel i para o proximo for
    i = 0;

    // Printar a tabela
    printf("ASCII - FREQUENCIA - SIMBOLO\n");

    for(i = 0; i < 256; i++)
        if(tab[i] > 0)
            printf("\t%d = %u = %c\n", i, tab[i], i);

    // PARTE 2
    
}