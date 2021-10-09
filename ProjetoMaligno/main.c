#include <stdio.h>
#include <stdlib.h>
typedef char String[1024];

int main()
{
    String frase = "Oi tudo bem krl?";
    int freq[256];

    pegaChars(frase, freq, 100);

    int i;
    for (i = 0; i < 256; i++)
        printf("Ascii %d: %d\n", i, freq[i]);

    return 0;
}
