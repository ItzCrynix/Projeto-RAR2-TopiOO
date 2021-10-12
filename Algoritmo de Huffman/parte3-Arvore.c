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

// Remove no da lista no inicio (pois é ordenada)
void remove_no_inicio(Lista *lista){
    No *aux; // cria um no auxiliar

    if(lista->inicio){ // verifica se alista é vazia

        // Remove o primeiro no da lista
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
}

// monta a arvore
No* montar_arvore(Lista *lista){
    
    No *primeiro, *segundo, *novo;

    while(lista->tam > 1){ // Enquanto a lista não tiver só um no (a raiz)

        // Pega os dois primeiros nos e os remove
        primeiro = lista->inicio;
        remove_no_inicio(lista);

        segundo = lista->inicio;
        remove_no_inicio(lista);

        // Adiciona um novo no:
        novo = malloc(sizeof(No)); // aloca um espaço na memoria para o novo no 
        
        if(novo){ // Verifica se a alocação deu certo
                
                novo->caracter = '+'; //tanto faz

                // A frequencia do novo é a soma das frequencias dos que o formam
                novo->frequencia = primeiro->frequencia + segundo->frequencia; 

                // O primeiro vai para a esquerda e o segundo para direita
                novo->esq = primeiro;
                novo->dir = segundo;

                novo->proximo = NULL;

                inserir_ordenado(lista, novo); // insere na lista
        }
        else{
            printf("ERROR");
            break;
        }
    }

    return lista->inicio;
}

// vai ser apagado, é só pra ver se montou a arvore certo
void imprime(No *raiz, int tam){
    
    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    else{
        imprime(raiz->esq, tam + 1);
        imprime(raiz->dir, tam + 1);
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

    // 
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


    // PARTE 3 - Arvore de Huffman

    printf("\t      Arvore de Huffman\n");

    No *raiz;
    raiz = montar_arvore(&lista);
  
    imprime(raiz, 0);
    
}