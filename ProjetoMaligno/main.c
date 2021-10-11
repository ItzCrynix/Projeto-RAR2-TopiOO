#include <stdio.h>
#include <stdlib.h>
typedef char String[1024];
typedef enum {
    false,
    true
} boolean;
void operacaoCompactar();
void operacaoDescompactar();

int main()
{
    printf("Integrante\t\t\t\tRA\n");
    printf("Cainan Loyola Schiavolin\t\t20126\n");
    printf("Paulo Henrique Francisco Felipe\t\t20150\n");
    printf("Mateus de Sales Francisco\t\t20732\n");
    printf("Pedro Sakai do Santos\t\t\t20136\n");
    printf("----------------------------------------------------\n");
    printf("Bem vindo ao nosso programa compactador de arquivos!\n\n");

    boolean continuar = true;
    do {
        int operacao;

        printf("Que operacao voce deseja fazer?\n");
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

    return 0;
}

void operacaoCompactar() {
    String caminho;

    printf("\n----------------------------------------------------");
    printf("\tCompactacao\n");
    printf("Por favor, digite o caminho (Ex: C:\\Users...) do arquivo que voce deseja compactar: ");
    scanf("%s", caminho);

    FILE *arquivo = fopen(caminho, "r+w");
    if (arquivo == NULL) {
        printf("[ERRO] Caminho invalido: \"%s\"\n", caminho);
        return;
    }

    unsigned int freq[256];
    String frase; zeravet(frase, 1024);

    char ch;
    int index = 0;
    while ((ch = getc(arquivo)) != EOF) {
        frase[index] = ch;
        index++;
    } pegaChars(frase, freq, 1024);

    printf("Conteudo:\n");
    for (index = 0; index < 1024; index++)
        if (frase[index] != '\0')
            printf("%c", frase[index]);
    printf("\n\n");

    printf("Frequencias:\n");
    for (index = 0; index < 256; index++)
        if (freq[index] > 0) {
            if (((char) index) == '\n')
                printf("\tCaracter: \\n --> %d\n", freq[index]);
            else if (((char) index) == '\t')
                printf("\tCaracter: \\t --> %d\n", freq[index]);
            else
                printf("\tCaracter: '%c' --> %d\n", index, freq[index]);
        }
    printf("\n\n");

    /*
    Conteúdo da descompactação
    */

    return;
}

void operacaoDescompactar() {
    String caminho;

    printf("\n----------------------------------------------------");
    printf("\tDescompactacao\n");
    printf("Por favor, digite o caminho (Ex: C:\\Users...) do arquivo que voce deseja descompactar: ");
    scanf("%s", caminho);

    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("[ERRO] Caminho invalido: \"%s\"\n", caminho);
        return;
    }

    unsigned int freq[256];
    String frase; zeravet(frase, 1024);

    char ch;
    int index = 0;
    while ((ch = getc(arquivo)) != EOF) {
        frase[index] = ch;
        index++;
    } pegaChars(frase, freq, 1024);

    printf("Conteudo:\n");
    for (index = 0; index < 1024; index++)
        if (frase[index] != '\0')
            printf("%c", frase[index]);
    printf("\n\n");

    printf("Frequencias:\n");
    for (index = 0; index < 256; index++)
        if (freq[index] > 0) {
            if (((char) index) == '\n')
                printf("\tCaracter: \\n --> %d\n", freq[index]);
            else if (((char) index) == '\t')
                printf("\tCaracter: \\t --> %d\n", freq[index]);
            else
                printf("\tCaracter: '%c' --> %d\n", index, freq[index]);
        }
    printf("\n\n");

    /*
    Conteúdo da descompactação
    */

    return;
}
