#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

Arvore noNull;

void inicializar(Arvore *raiz)
{
    *raiz = NULL;
    noNull = (Arvore)malloc(sizeof(struct no));
    noNull->cor = DUPLO_PRETO;
    noNull->valor = 0;
    noNull->esq = NULL;
    noNull->dir = NULL;
}

Arvore inserirRb(int valor, Arvore *raiz)
{
    Arvore posicao, pai, novo;
    posicao = *raiz;
    pai = NULL;

    while (posicao != NULL)
    {
        pai = posicao;
        if (valor > posicao->valor)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }
    novo = (Arvore)malloc(sizeof(struct no));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if (elementoRaiz(novo))
        *raiz = novo;
    else
    {
        if (valor > pai->valor)
            pai->dir = novo;
        else
            pai->esq = novo;
    }

    ajustar(raiz, novo);
}

void ajustar(Arvore *raiz, Arvore elemento)
{
    while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO)
    {
        /* code */
    }
    (*raiz)->cor = PRETO;
}

int elementoRaiz(Arvore elemento)
{
    return (elemento->pai == NULL);
}

enum Cor cor(Arvore elemento)
{
    if (elemento == NULL)
        return PRETO;
    else
        return elemento->cor;
}

const char *cores[] = {
    "VERMELHO",
    "PRETO",
    "DUPLO PRETO"};

void preOrderRb(Arvore raiz)
{
    if (raiz != NULL)
    {
        printf("[%d %s]", raiz->valor, cores[raiz->cor]);
        preOrderRb(raiz->esq);
        preOrderRb(raiz->dir);
    }
}

// Arvore removerBst(int valor, Arvore raiz)
// {
//     if (raiz != NULL)
//     {
//         if (valor == raiz->valor)
//         {
//             if (raiz->esq == NULL && raiz->dir == NULL)
//             {
//                 free(raiz);
//                 return NULL;
//             }
//             if (raiz->esq != NULL && raiz->dir == NULL)
//             {
//                 Arvore aux = raiz->esq;
//                 free(raiz);
//                 return aux;
//             }
//             if (raiz->dir != NULL && raiz->esq == NULL)
//             {
//                 Arvore aux = raiz->dir;
//                 free(raiz);
//                 return aux;
//             }
//             int maiorValorEsq = maiorBst(raiz->esq)->valor;
//             raiz->valor = maiorValorEsq;
//             raiz->esq = removerBst(maiorValorEsq, raiz->esq);
//         }
//         if (valor > raiz->valor)
//             raiz->dir = removerBst(valor, raiz->dir);
//         else
//             raiz->esq = removerBst(valor, raiz->esq);
//     }
//     return raiz;
// }