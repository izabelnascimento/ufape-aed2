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

    if (isElementoRaiz(novo))
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
        // caso 1
        if (cor(tio(elemento)) == VERMELHO)
        {
            elemento->pai->cor = PRETO;
            tio(elemento)->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            elemento = elemento->pai->pai;
            continue;
        }
        // caso 2a: rotação simples direita
        if (isFilhoEsquerdo(elemento) && isFilhoEsquerdo(elemento->pai))
        {
            rotacaoSimplesDir(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;
            continue;
        }
        // caso 2b: rotação simples esquerda
        if (isFilhoDireito(elemento) && isFilhoDireito(elemento->pai))
        {
            rotacaoSimplesEsq(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;
            continue;
        }
        // caso 3: rotação dupla
        if (cor(tio(elemento)) == PRETO)
        {
            // caso 3a: rotação dupla direita
            if (isFilhoDireito(elemento) && isFilhoEsquerdo(elemento->pai))
            {
                rotacaoSimplesEsq(raiz, elemento->pai);
                rotacaoSimplesDir(raiz, elemento->pai);
                elemento->cor = PRETO;
                elemento->esq->cor = VERMELHO;
                elemento->dir->cor = VERMELHO;
            }
            // caso 3b: rotação dupla esquerda
            if (isFilhoEsquerdo(elemento) && isFilhoDireito(elemento->pai))
            {
                rotacaoSimplesDir(raiz, elemento->pai);
                rotacaoSimplesEsq(raiz, elemento->pai);
                elemento->cor = PRETO;
                elemento->esq->cor = VERMELHO;
                elemento->dir->cor = VERMELHO;
            }
        }
    }
    // caso 0
    (*raiz)->cor = PRETO;
}

void rotacaoSimplesDir(Arvore *raiz, Arvore pivo)
{
    Arvore u, t1, t2, t3;
    u = pivo->esq;
    t1 = u->esq;
    t2 = u->dir;
    t3 = pivo->dir;

    int pivoEsq = isFilhoEsquerdo(pivo);

    pivo->esq = t2;
    if (t2 != NULL)
        t2->pai = pivo;

    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    if (isElementoRaiz(u))
        *raiz = u;
    else
    {
        if (pivoEsq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
}

void rotacaoSimplesEsq(Arvore *raiz, Arvore pivo)
{
    Arvore u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;

    int pivoDir = isFilhoDireito(pivo);

    pivo->dir = t2;
    if (t2 != NULL)
        t2->pai = pivo;

    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    if (isElementoRaiz(u))
        *raiz = u;
    else
    {
        if (pivoDir)
            u->pai->dir = u;
        else
            u->pai->esq = u;
    }
}

// void rotacaoDuplaDir(Arvore *raiz, Arvore pivo)
// {
//     Arvore u, v, t1, t2, t3, t4;
//     u = pivo->esq;
//     v = u->dir;
//     t1 = u->esq;
//     t2 = v->esq;
//     t3 = v->dir;
//     t4 = pivo->dir;

//     int pivoEsq = isFilhoEsquerdo(pivo);

//     u->dir = t2;
//     if (t2 != NULL)
//         t2->pai = u;
//     v->esq = u;
//     v->pai = pivo;
//     u->pai = v;

//     pivo->esq = t3;
//     if (t3 != NULL)
//         t3->pai = pivo;
//     v->pai = pivo->pai;
//     pivo->pai = v;
//     v->dir = pivo;

//     if (isElementoRaiz(v))
//         *raiz = v;
//     else
//     {
//         if (pivoEsq)
//             v->pai->dir = v;
//         else
//             v->pai->esq = v;
//     }
// }

// Arvore rotacaoDuplaEsq(Arvore pivo)
// {
//     Arvore u, v, t1, t2, t3, t4;
//     u = pivo->dir;
//     v = u->esq;
//     t1 = pivo->esq;
//     t2 = v->esq;
//     t3 = v->dir;
//     t4 = u->dir;

//     switch (v->fb)
//     {
//     case -1:
//         pivo->fb = 0;
//         u->fb = 1;
//         break;
//     case 0:
//         pivo->fb = 0;
//         u->fb = 0;
//         break;
//     case 1:
//         pivo->fb = -1;
//         u->fb = 0;
//         break;
//     default:
//         break;
//     }
//     v->fb = 0;

//     u->esq = t3;
//     v->dir = u;
//     pivo->dir = t2;
//     v->esq = pivo;
//     return v;
// }

int isElementoRaiz(Arvore elemento)
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

Arvore tio(Arvore elemento)
{
    return irmao(elemento->pai);
}

Arvore irmao(Arvore elemento)
{
    if (isFilhoEsquerdo(elemento))
        return elemento->pai->dir;
    else
        return elemento->pai->esq;
}

int isFilhoEsquerdo(Arvore elemento)
{
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int isFilhoDireito(Arvore elemento)
{
    return (elemento->pai != NULL && elemento == elemento->pai->dir);
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