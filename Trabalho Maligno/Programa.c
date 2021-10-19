#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
    false,
    true
} boolean;

typedef struct no{

    char byte;
    int frequencia;
    struct no *esq, *dir, *proximo;
    char codigo[20];

}No;

typedef struct {

    No *inicio;
    int tam;

}Lista;

void inserir_ordenado(Lista *lista, No *no){

     No *aux;

    if(lista->inicio == NULL)
    {
        lista->inicio = no;
    }
    else if(no->frequencia < lista->inicio->frequencia)
    {
        no->proximo = lista->inicio; 
        lista->inicio = no;
    }
    else
    {
        aux = lista->inicio;

        while (aux->proximo && aux->proximo->frequencia <= no->frequencia) 
            aux = aux->proximo;

        no->proximo = aux->proximo;  
        aux->proximo = no;
    }

    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
    int i;
    No *novo;

    for(i = 0; i < 256; i++){
        if(tab[i] > 0){ 

            novo = malloc(sizeof(No));

            if(novo){ 

                novo->byte = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo); 
            }
            else{
                printf("ERROR em preencher_lista");
                break;
            }
        }
    }
}

void remove_no_inicio(Lista *lista){
    No *aux;

    if(lista->inicio)
    {
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }
}

No* montar_arvore(Lista *lista)
{
    No *primeiro, *segundo, *novo;

    while(lista->tam > 1)
    {
        primeiro = lista->inicio;
        remove_no_inicio(lista);

        segundo = lista->inicio;
        remove_no_inicio(lista);

        novo = malloc(sizeof(No)); 
        
        if(novo){ 
                
                novo->byte = '+'; 

                novo->frequencia = primeiro->frequencia + segundo->frequencia; 

                novo->esq = primeiro;
                novo->dir = segundo;

                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
        }
        else{
            printf("ERROR");
            break;
        }
    }
    novo = lista->inicio;
    remove_no_inicio(lista);
    return novo;
}

void montar_dicionario(No *raiz, char cod[], Lista *dicionario)
{

    if(raiz->esq == NULL && raiz->dir == NULL)
    {
        No *aux = dicionario->inicio;

        if(aux->byte == raiz->byte)
        {
            strcpy(aux->codigo, cod);
        }
        else
        {
            for(;;)
            {
                aux = aux->proximo;

                if(aux->byte == raiz->byte)
                {
                    strcpy(aux->codigo, cod);

                    break;
                }
            }
            
        }
    }
    else{

        char esq[20] = "";
        char dir[20] = "";

        strcat(strcpy(esq, cod), "0");
        strcat(strcpy(dir, cod), "1");

        montar_dicionario(raiz->esq, esq, dicionario);
        montar_dicionario(raiz->dir, dir, dicionario);
    }
}
 

char* codifica(Lista *dicionario, char texto[])
{
    int i = 0;
    No *aux;
    char* temp[2];
    char *codificado = calloc(4000, sizeof(char));

    while(texto[i] != '\0') 
    {
        aux = dicionario->inicio; 

        while (aux)
        {
            if(aux->byte == texto[i]) 
            {
                temp[0] = aux->codigo;
                temp[1] = '\0';
                strcat(codificado, *temp);
            }

            aux = aux->proximo; 
        }

        i++;
    }

    return codificado;

}

char* decodifica(char texto[], No *raiz)
{
    int i = 0;
    No *aux = raiz;
    char temp[2];
    char *decodificado = calloc(2000, sizeof(char));

    while(texto[i] != '\0') 
    {
        if(texto[i] == '0') 
            aux = aux->esq;
        else
            aux = aux->dir;

        if(aux->esq == NULL && aux->dir == NULL)
        {
            temp[0] = aux->byte;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }

        i++;
    }

    return decodificado;
    
}

int digit_to_int(char d)
{
    char str[2];

    str[0] = d;
    str[1] = '\0';
    return (int) strtol(str, NULL, 10);
}


void operacaoCompactar()
{
    // -------- PARTE 1: leitura do arquivo ---------

    char caminho[50];
    for(int e = 0; e < 50; e++)
        caminho[e] = '\0';

    printf("\n\n----------------------------------------------------");
    printf("\tCompactacao\n");
    printf("Por favor, digite o caminho (Ex: C:\\Users...) do arquivo que voce deseja compactar: ");
    scanf("%s", caminho);

    FILE *arquivo = fopen(caminho, "rb");

    if (arquivo == NULL) {
        printf("[ERRO] Caminho invalido: \"%s\"\n", caminho);
        return;
    }

    int c;
    char decodificado[2150] = "";
    char temp[2];

    while((c = fgetc(arquivo)) != EOF)
    {
        temp[0] = c;
        temp[1] = '\0';
        strcat(decodificado, temp);
    }

    if((c == EOF) && (feof(arquivo) == 0) && (ferror(arquivo) != 0))
        perror("Erro: fgetc");


    // --------- PARTE 2: tabela de frequencia ---------

    int tab[256];

    int i;

    for(i = 0; i < 256; i++)
        tab[i] = 0;

    i = 0;

    while(decodificado[i] != '\0') { 
        tab[decodificado[i]]++;
        i++;
    }
    

    // -------- PARTE 3: lista ordenada ---------

    Lista lista;

    lista.inicio = NULL;
    lista.tam = 0;

    preencher_lista(tab, &lista);


    // ----------- PARTE 4: arvore binaria -----------

    No *arvore;
    arvore = montar_arvore(&lista);


    // ----------- PARTE 5: dicionario ------------

    char codigo[20] = "";
    Lista dicionario;

    dicionario.inicio = NULL;
    dicionario.tam = 0;

    preencher_lista(tab, &dicionario);
    montar_dicionario(arvore, codigo, &dicionario);



    // ---------- PARTE 6: codifica ------------ 

    char *codificado = codifica(&dicionario, decodificado);

    // ---------- PARTE 7: cria e escreve num novo arquivo ----------

    int a;

    strcat(caminho, ".huff");


    FILE *arq;

    arq = fopen(caminho, "wb");

    i = 0;
    for(i = 0; i < 256; i++)
    {   
        fprintf(arq, "%d", tab[i]);
    }

    fputc('\n', arq);

    for(a=0; codificado[a]; a++) 
        fputc(codificado[a], arq);

    fclose(arq);
    
    printf("\nO arquivo foi criado com sucesso!\n");
    system("pause");
    
}

void operacaoDescompactar()
{
    // -------- PARTE 1: leitura do arquivo + tabela de frequencia ---------

    char caminho[50];
    for(int e = 0; e < 50; e++)
        caminho[e] = '\0';

    printf("\n\n----------------------------------------------------");
    printf("\tDescompactacao\n");
    printf("Por favor, digite o caminho (Ex: C:\\Users...) do arquivo que voce deseja compactar, ele deve ser .huff: ");
    scanf("%s", caminho);

    FILE *arquivo = fopen(caminho, "rb");

    if (arquivo == NULL) {
        printf("[ERRO] Caminho invalido: \"%s\"\n", caminho);
        return;
    }


    int c, i = 0;
    int tab[256];
    char codificado[2000] = "";
    char temp[2];

    while((c = fgetc(arquivo)) != '\n') 
    {
        tab[i] = digit_to_int(c);
        i = i + 1;
    }
    
    while((c = fgetc(arquivo)) != EOF)
    {
        temp[0] = c;
        temp[1] = '\0';
        strcat(codificado, temp);
    }
    
    if((c == EOF) && (feof(arquivo) == 0) && (ferror(arquivo) != 0))
        perror("Erro: fgetc");


    // ----------- PARTE 2: lista ordenada --------------
    
    Lista lista;

    // Inicializa a lista vazia
    lista.inicio = NULL;
    lista.tam = 0;

    // Preenche a lista   
    preencher_lista(tab, &lista);


    // ----------- PARTE 3: arvore binaria -----------

    No *arvore;
    arvore = montar_arvore(&lista);


    // ----------- PARTE 4: dicionario ------------

    char codigo[20] = "";
    Lista dicionario;

    dicionario.inicio = NULL;
    dicionario.tam = 0;

    preencher_lista(tab, &dicionario); 
    montar_dicionario(arvore, codigo, &dicionario);

    // ------------ PARTE 5: decodificar codigo ------------

    char *decodificado = decodifica(codificado, arvore);

    // ------------ PARTE 6: salvar em um arquivo ------------

    int tam = 0;
    while(caminho[tam] != '\0')
        tam++;

    for (int i = tam; i > 0; i--) {

        if (caminho[i] == '.') {

            for (int k = i; k < tam; k++) {
                caminho[k] = '\0';
            }

            break;
        }
    }

    int a;

    FILE *arq;

    arq = fopen(caminho, "wb");

    for(a=0; decodificado[a]; a++) 
        fputc(decodificado[a], arq);

    fclose(arq);
    
    printf("\nO arquivo foi criado com sucesso!\n");
    system("pause");
}   


void main() {

    printf("\nIntegrante\t\t\t\tRA\n");
    printf("Cainan Loyola Schiavolin\t\t20126\n");
    printf("Paulo Henrique Francisco Felipe\t\t20150\n");
    printf("Mateus de Sales Francisco\t\t20732\n");
    printf("Pedro Sakai do Santos\t\t\t20136\n");
    printf("----------------------------------------------------\n");
    printf("Bem vindo ao nosso programa compactador de arquivos!\n\n");

    boolean continuar = true;
    do {
        int operacao;

        printf("\n\nQue operacao voce deseja fazer?\n");
        printf("\t0-Encerrar o programa\n\t1-Compactar um arquivo\n\t2-Descompactar um arquivo\n");
        printf("Digite: ");
        scanf("%d", &operacao);

        switch (operacao) {
            case 0: continuar = false; break;
            case 1: operacaoCompactar(); break;
            case 2: operacaoDescompactar(); break;
            default: printf("[ERRO] Operacao nao reconhecida: %d\n", operacao); continuar = false; break;
        }
    } while (continuar);

}