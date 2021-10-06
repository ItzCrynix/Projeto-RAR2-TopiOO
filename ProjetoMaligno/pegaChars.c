#include<stdio.h>
#include<stdlib.h>|

int pegaChars(char arquivo[]) {
    int freq[256];

    int i;
    for (i = 0; i < sizeof(arquivo); i++) {
        freq[(int) arquivo[i]]++;
    }

    return freq;
}

int main(int argc, char const *argv[])
{
    char string[256];

    scanf("%s", &string);
    fflush(stdin);

    int freq[256] = pegaChars(string);

    int i;
    for (i = 0; i < 256; i++) {
        printf("%d", freq[i]);
    }

    system("pause");
    return 0;
}

