/*
    Integrantes:
        Alan Edward da Silva Oliveira - RA: 210184
        Gabriel Portillo dos Santos - RA: 210236
        Luis Felipe dos Dantos Gianoni - RA: 204115

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>

// começo Funções

void Logica(int qtd_termo);
void alocaFloat(float **p, int tam);
bool criterio_parada(int opc, float *precisao, float *f_m, float *a, float *b);
float valor_funcoes(float *x, float *f_x, int qtd_termo, float termos[2][10]);
void mostrarTabela(float *a, float *m, float *b, float *f_a, float *f_m, float *f_b, int iteracoes);
void novasIteracoes(float *a, float *m, float *b, float *f_a, float *f_m, float *f_b, int opc, float termos[2][10], int qtd_termos, float *precisao);

// fim Funções

// começo Main

int main()
{
    int qtd_termo;

    printf("Insira a quantidade de termos de sua funcao: ");
    scanf("%i", &qtd_termo);

    Logica(qtd_termo);

} 

// fim da main

void Logica(int qtd_termo)
{
    float termos[2][10], *a = NULL, *b = NULL, *m = NULL, *f_a = NULL, *f_m = NULL, *f_b = NULL, *precisao = NULL;
    int opc;

    // começo alocações

    // alocaFloatArray(&termos,3);
    alocaFloat(&a, 3);
    alocaFloat(&m, 3);
    alocaFloat(&b, 3);
    alocaFloat(&precisao, 3);
    alocaFloat(&f_a, 3);
    alocaFloat(&f_m, 3);
    alocaFloat(&f_b, 3);

    // fim alocações

    system("cls");

    // começo popular array

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < qtd_termo; j++)
        {
            printf("\nInsira o %i termo: ", j + 1);
            scanf("%f", &termos[i][j]);
            fflush(stdin);

            printf("E qual seu expoente?: ");
            scanf("%f", &termos[i + 1][j]);
            fflush(stdin);
        }
    }

    // fim popular array

    // começo definir intervalo

    printf("\nQual o intervalo? (valores entre espaco): ");
    scanf("%f %f", a, b);
    fflush(stdin);

    // fim definir intervalo

    // começo definir valor de m

    *m = (*a + *b) / 2;

    // fim definir valor de m

    // começo definir precisao

    printf("\nQual a precisao (utilizar ponto): ");
    scanf("%f", precisao);
    fflush(stdin);

    // fim definir precisao

    // começo definir criterio de parada

    printf("\nQual o criterio de parada?\n[1] |f(m)|<E\n[2] |bk-ak|<E\n");
    scanf("%i", &opc);
    fflush(stdin);

    // fim  definir criterio de parada

    // começo calculo

    novasIteracoes(a, m, b, f_a, f_m, f_b, opc, termos, qtd_termo, precisao);

    // fim calculo
}

bool criterio_parada(int opc, float *precisao, float *f_m, float *a, float *b)
{
    bool criterio_parada;

    switch (opc)
    {
        case 1:
            criterio_parada = fabs(*f_m) > *precisao ? true : false;
            break;

        case 2:
            criterio_parada = fabs(*b - *a) > *precisao ? true : false;
            break;
    }

    return criterio_parada;

}

float valor_funcoes(float *x, float *f_x, int qtd_termo, float termos[2][10])
{
    *f_x = 0;

    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < qtd_termo; j++)
        {

            *f_x = *f_x + (pow(*x, termos[i + 1][j]) * termos[i][j]);
            
        }
    }

    return *f_x;

}

void mostrarTabela(float *a, float *m, float *b, float *f_a, float *f_m, float *f_b, int iteracoes)
{

    printf("%i         %.3f   %.3f  %.3f  %.3f     %.3f     %.3f\n", iteracoes - 1, *a, *m, *b, *f_a, *f_m, *f_b);
}

void novasIteracoes(float *a, float *m, float *b, float *f_a, float *f_m, float *f_b, int opc, float termos[2][10], int qtd_termos, float *precisao)
{
    int iteracoes = 0;

    printf("\nIteracoes|  A  |  M  |  B  |  F(a)  |  F(m)  |  F(b)  |\n");

    do
    {
        *m = (*a + *b) / 2;
        iteracoes++;

        *f_a = valor_funcoes(a, f_a, qtd_termos, termos);

        *f_b = valor_funcoes(b, f_b, qtd_termos, termos);

        *f_m = valor_funcoes(m, f_m, qtd_termos, termos);

        mostrarTabela(a, m, b, f_a, f_m, f_b, iteracoes);

        if (*f_m * *f_a < 0)
        {
            *b = *m;
        }
        else if (*f_m * *f_b < 0)
        {
            *a = *m;
        }

    } while (criterio_parada(opc, precisao, f_m, a, b));

    printf("A Raiz da funcao e: %.3f com erro de %.3f(< %.3f)", *m, *f_m, *precisao);

}

void alocaFloat(float **p, int tam)
{
    if ((*p = (float *)realloc(*p, tam * sizeof(float))) == NULL)
    {
        printf("Erro na alocação!");
        exit(1);
    }

    printf("Espaco alocado com sucesso! End= %u\n", *p);

}
