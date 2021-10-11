#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define tamanho 1024//sus

//-----------------No e lista--------------------------
typedef struct no{
    unsigned char caracter;
    int freq;
    struct  no *esquerda, *direita, *proximo;
}No;

typedef struct {
    No *inicio;
    int tam;
}Lista;

void criarLista (Lista *lista){
    lista -> inicio = NULL;
    lista ->tam = 0;
}

void inserirEmOrdem(Lista *lista, No *no){
    No *noAuxiliar;

    if(lista -> inicio == NULL)
    {
        lista -> inicio = no;
    }
    else if(no ->freq < lista -> inicio -> freq){
        no -> proximo = lista -> inicio;
        lista -> inicio = no;
    }
    else{
        noAuxiliar = lista -> inicio;
        while(noAuxiliar -> proximo && noAuxiliar -> proximo -> freq <= no -> freq)
           noAuxiliar = noAuxiliar -> proximo ;

           no -> proximo = noAuxiliar ->proximo;
           noAuxiliar -> proximo = no;
    }
    lista -> tam++;
}

void preencherLista (unsigned int frequencias[], Lista *lista)
{
    No *novoNo;
    int i;

    while (i < tamanho)
    {
        if(frequencias[i] > 0)
        {
            novoNo = malloc(sizeof (No));
            novoNo -> caracter = i;
            novoNo ->freq = frequencias[i]; // sus
            novoNo ->direita = NULL;
            novoNo -> esquerda = NULL;
            novoNo -> proximo = NULL;

            inserirEmOrdem(lista, novoNo);
        }

        i++;
    }

}
void imprime_lista(Lista *lista)
{
    No *noAuxiliar = lista -> inicio;

    while(noAuxiliar){
        printf("char: %c Freq: %d\n", noAuxiliar ->caracter, noAuxiliar->freq);
        noAuxiliar = noAuxiliar -> proximo;
    }
}
//----------------Fim No e lista---------------------

//----------------Frequencia dos caracteres----------
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
//-----------------Fim frequencia dos caracteres------------


//####################### MAIN ###############################
int main(int argc, char const *argv[])
{
    unsigned char string[tamanho]; zeravet(string, tamanho); // cria um vetor para armazenar os dados e "zera" ele
    int frequencia[tamanho];
    char *filename = "testejs.js"; // caminho do arquivo texto
    FILE *fp = fopen(filename, "r");
     Lista lista;

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



    criarLista(&lista);
    preencherLista(frequencia, &lista);
    imprime_lista(&lista);
    //No *noAuxiliar = lista -> inicio;
    printf("ainn nobru \n");
    /*
    for(int i = 0; i< lista ->tam; i++)
    {
        printf("Char: c% Freq: %d\n",noAuxiliar -> caracter, noAuxiliar ->freq);
        noAuxiliar = noAuxiliar ->proximo;
    }
    */
    // close the file
    fclose(fp);
    system("pause");
    return 0;
}


