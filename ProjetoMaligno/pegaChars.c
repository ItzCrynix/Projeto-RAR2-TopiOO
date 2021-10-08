#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define tamanho 2048

//Tipos, Literais, Classes, Objetos...
typedef char String[tamanho];
/*
typedef struct NoArvore
{
    Byte caracter;
    struct NoArvore esquerda;
    struct NoArvore direita;
} NoArvore;
*/


// Declaração de funções
void pegaChars(String arquivo, int freq[256], int tam);
void zeravet(String vet, int tam);

int main(int argc, char const *argv[])
{
    /* Algumas variaveis!!!!!!!!!! */
    String string; zeravet(string, tamanho); // cria um vetor para armazenar os dados e "zera" ele
    int frequencia[256];

    /* Parte que tenta pegar o arquivo!!!!!!!!!!!! */
    char *filename = "testejs.js"; // caminho do arquivo texto
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    /* Parte que lê os caracteres do arquivo!!!!!!!!!!!! */
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF) { // Lê um caracter por vez e coloca na string
        string[i] = ch;
        i++;
    } pegaChars(string, frequencia, tamanho); // adiciona ao vetor frequencia as frequencias dos caracteres

    for (i = 0; i < 256; i++)
        //if (frequencia[i] != 0) // descomente isso se você quer que apenas os caracteres que possuem frequencia apareçam
            printf("%d : %d\n", i, frequencia[i]);

    for (i = 0; i < tamanho; i++)
        if (string[i] != '\0')
            printf("%c", string[i]);
    printf("\n");

    // close the file
    fclose(fp);
    system("pause");
    return 0;
}

// Definição das funções
void pegaChars(String arquivo, int freq[256], int tam) { // basicamente, o resultado que isso retorna eh o vetor...contendo em cada casa um caracter ascii e sua frequencia.
    int i;

    for (i = 0; i < 256; i++) {
        freq[i] = 0;
    }

    for (i = 0; i < tam; i++) {
        int ascii = (int) arquivo[i];
        if (ascii != 0) {
            //printf("%d : %c\n", i, arquivo[i]);
            freq[ascii]++;
        }
    }
}

void zeravet(String vet, int tam) {
    int i;
    for (i = 0; i < tam; i++)
        vet[i] = '\0';
}