typedef char String[1024];
typedef struct No {
    unsigned char caracter;
    struct No esquerda, direita;
} No;
typedef struct Arvore {
    No raiz, atual;
    int grau;
} Arvore;

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
