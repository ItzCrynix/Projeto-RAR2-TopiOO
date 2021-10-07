#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define tamanho 1024

void pegaChars(unsigned char arquivo[], int freq[], int tam) {
    int i;

    for (i = 0; i < tam; i++) {
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

void zeravet(unsigned char vet[], int tam) {
    int i;
    for (i = 0; i < tam; i++)
        vet[i] = '\0';
}

int main(int argc, char const *argv[])
{
    unsigned char string[tamanho]; zeravet(string, tamanho); // cria um vetor para armazenar os dados e "zera" ele
    int frequencia[tamanho];
    char *filename = "testejs.js"; // caminho do arquivo texto
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // read one character at a time
    char ch;
    int i = 0;
    while ((ch = fgetc(fp)) != EOF) {
        string[i] = ch;
        i++;
    } pegaChars(string, frequencia, tamanho);

    for (i = 0; i < tamanho; i++)
        if (frequencia[i] != 0)
            printf("%d : %d\n", i, frequencia[i]);
    for (i = 0; i < tamanho; i++)
        if (string[i] != '\0')
            printf("%c", string[i]);

    // close the file
    fclose(fp);
    system("pause");
    return 0;
}


