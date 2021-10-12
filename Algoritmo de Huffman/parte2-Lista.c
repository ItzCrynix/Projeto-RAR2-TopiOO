#include<stdio.h>
#include<stdlib.h>

// Cria a estrutura do No
typedef struct no{

    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;

}No;

// Cria a estrutura da Lista
typedef struct {

    No *inicio;
    int tam;

}Lista;

// Insere na lista de forma ordenada
void inserir_ordenado(Lista *lista, No *no){

    No *aux; // No auxiliar

    // a lista está vazia?
    if(lista->inicio == NULL){

        // Se sim, o no passado no parametro se torna o inicio da lista
        lista->inicio = no;
    }
    // a frequencia do no passado é menor da que do inicio?
    else if(no->frequencia < lista->inicio->frequencia){

        //Esse if serve para ordenar a lista, já que sempre que a frequencia for menor ela se torna o inicio
        no->proximo = lista->inicio; // o no que será inserido recebe o antigo inicio como proximo
        lista->inicio = no; // o no passado se torna o primeiro da lista
    }
    // Se a frequencia do no passado for maior da que do inicio
    else{

        // o auxiliar recebe o primeiro no da lista para ele não se perder
        aux = lista->inicio;

        // vai tornando o auxiliar o proximo da lista até que o proximo seja NULL (o ultimo)
        // ou a frequencia do prox seja menor/igual a frequencia do passado (ele ficara no meio da lista)
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia) 
            aux = aux->proximo;

        // o proximo do no recebe o proximo do aux (ele ficara na frente do aux e atras do proximo)
        no->proximo = aux->proximo;  
        // o proximo do aux se torna o no
        aux->proximo = no;
    }

    lista->tam++; // o tamanho da lista aumenta em 1
}

// Preenche a lista com a tabela de frequencia
void preencher_lista(unsigned int tab[], Lista *lista){
    int i; // inteiro para o for
    No *novo; // ponteiro que sera usado para alocar os nos

    for(i = 0; i < 256; i++){ // percorre a tabela
        if(tab[i] > 0){ // verifica se o caracter aparece pelo menos uma vez

            novo = malloc(sizeof(No)); //aloca um espaço na memoria

            if(novo){ // confere se a alocação deu certo

                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo); // insere na lista
            }
            else{
                printf("ERROR em preencher_lista");
                break;
            }
        }
    }
}

// Imprime a lista passada - vai ser apagado
void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\tLista ordenada: Tamanho: %d\n", lista->tam);
    while (aux)
    {
        printf("\tCaracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
    
}

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

    while(texto[i] != '\0') { // o '\0' é para identificar o final de uma string
        tab[texto[i]]++;
        i++;
    }

    // PARTE 2 - Cria, inicializa, preenche e imprime a lista

    printf("\n\n");

    Lista lista;

    // Inicializa a lista vazia
    lista.inicio = NULL;
    lista.tam = 0;

    // Preenche a lista   
    preencher_lista(tab, &lista);

    // Imprime a lista
    imprimir_lista(&lista);
    
}