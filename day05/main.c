#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_INTERVALOS 10000
#define MAX_NUMEROS 100000

typedef struct {
    int inicio;
    int fim;
} Intervalo;

typedef struct {
    Intervalo intervalos[MAX_INTERVALOS];
    int qtdIntervalos;
    int numeros[MAX_NUMEROS];
    int qtdNumeros;
} Dados;

Dados parse(const char *conteudo) {
    Dados d;
    d.qtdIntervalos = 0;
    d.qtdNumeros = 0;

    char *copy = strdup(conteudo);
    char *line = strtok(copy, "\n");

    int lendoIntervalos = 1;

    while (line != NULL) {
        // remove \r
        line[strcspn(line, "\r")] = 0;

        if (strlen(line) == 0) {
            lendoIntervalos = 0;
            line = strtok(NULL, "\n");
            continue;
        }

        if (lendoIntervalos) {
            int ini, fim;
            sscanf(line, "%d-%d", &ini, &fim);
            d.intervalos[d.qtdIntervalos++] = (Intervalo){ini, fim};
        } else {
            d.numeros[d.qtdNumeros++] = atoi(line);
        }

        line = strtok(NULL, "\n");
    }

    free(copy);
    return d;
}

int part01(const char *conteudo) {
    Dados d = parse(conteudo);
    int soma = 0;

    for (int i = 0; i < d.qtdNumeros; i++) {
        int n = d.numeros[i];

        for (int j = 0; j < d.qtdIntervalos; j++) {
            if (n >= d.intervalos[j].inicio &&
                n <= d.intervalos[j].fim) {
                soma++;
                break;
            }
        }
    }

    return soma;
}

int cmpIntervalo(const void *a, const void *b) {
    Intervalo *i1 = (Intervalo *)a;
    Intervalo *i2 = (Intervalo *)b;
    return i1->inicio - i2->inicio;
}

long part02(const char *conteudo) {
    Dados d = parse(conteudo);

    qsort(d.intervalos, d.qtdIntervalos, sizeof(Intervalo), cmpIntervalo);

    long total = 0;
    int atualInicio = d.intervalos[0].inicio;
    int atualFim = d.intervalos[0].fim;

    for (int i = 1; i < d.qtdIntervalos; i++) {
        int inicio = d.intervalos[i].inicio;
        int fim = d.intervalos[i].fim;

        if (inicio <= atualFim + 1) {
            if (fim > atualFim)
                atualFim = fim;
        } else {
            total += (atualFim - atualInicio + 1);
            atualInicio = inicio;
            atualFim = fim;
        }
    }

    total += (atualFim - atualInicio + 1);
    return total;
}

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (!f) {
        perror("Erro ao abrir input.txt");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *conteudo = malloc(size + 1);
    fread(conteudo, 1, size, f);
    conteudo[size] = '\0';

    fclose(f);

    printf("Parte 1: %d\n", part01(conteudo));
    printf("Parte 2: %ld\n", part02(conteudo));

    free(conteudo);
    return 0;
}
