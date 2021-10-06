#include<stdio.h>
#include<stdlib.h>

void pegaChars(char arquivo[], int freq[], int tamanho) {
    int i;

    for (i = 0; i < tamanho; i++) {
        freq[i] = 0;
    }

    for (i = 0; i < tamanho; i++) {
        printf("%c: %d\n", arquivo[i], (int) arquivo[i]);
        freq[(int) arquivo[i]]++;
    }
}

int main(int argc, char const *argv[])
{
    char string[256] = "laidsbbfahlwierfioqwue4hbfawuiyhbgfaowiebfauioywegbfuawyebfiayuwsfuyiaoberfyiobaweyhfbawiuefbawsdhfvbasiuhaweufhaidnbaliosuhbgAIOWUBFAIWUEFB";
    int frequencia[256];
    pegaChars(string, frequencia, 256);

    int i;
    for (i = 0; i < 256; i++) {
        printf("%d\n", frequencia[i]);
    }

    scanf("%d");
    return 0;
}

