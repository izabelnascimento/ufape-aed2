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

void removerRb(int valor, Arvore *raiz)
{
    Arvore posicao;
    posicao = *raiz;

    while (posicao != NULL)
    {
        if (valor == posicao->valor)
        {
            // 0 filho
            if (posicao->esq == NULL && posicao->dir == NULL)
            {
                // raiz 0 filho
                if (isElementoRaiz(posicao))
                {
                    *raiz = NULL;
                    free(posicao);
                    break;
                }
                // vermelho 0 filho
                if (posicao->cor == VERMELHO)
                {
                    if (isFilhoEsquerdo(posicao))
                        posicao->pai->esq = NULL;
                    else
                        posicao->pai->dir = NULL;
                    free(posicao);
                    break;
                }
                // preto 0 filho
                else
                {
                    noNull->cor = DUPLO_PRETO;
                    noNull->pai = posicao->pai;
                    if (isFilhoEsquerdo(posicao))
                        posicao->pai->esq = noNull;
                    else
                        posicao->pai->dir = noNull;
                    free(posicao);
                    reajustar(raiz, noNull);
                    break;
                }
                break;
            }
            // 1 filho esq
            if (posicao->esq != NULL && posicao->dir == NULL)
            {
                posicao->esq->cor = PRETO;
                posicao->esq->pai = posicao->pai;

                if (isElementoRaiz(posicao))
                    *raiz = posicao->esq;
                else
                {
                    if (isFilhoDireito(posicao))
                        posicao->pai->esq = posicao->dir;
                    else
                        posicao->pai->dir = posicao->dir;
                }
                free(posicao);
                break;
            }
            // 1 filho dir
            if (posicao->dir != NULL && posicao->esq == NULL)
            {
                posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

                if (isElementoRaiz(posicao))
                    *raiz = posicao->dir;
                else
                {
                    if (isFilhoEsquerdo(posicao))
                        posicao->pai->esq = posicao->dir;
                    else
                        posicao->pai->dir = posicao->dir;
                }
                free(posicao);
                break;
            }
            // caso 2 filhos
            int maiorValorEsq = maiorElemento(posicao->esq)->valor;
            posicao->valor = maiorValorEsq;
            removerRb(posicao->valor, &(posicao->esq));
            break;
        }
        if (valor > posicao->valor)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }
}

void reajustar(Arvore *raiz, Arvore elemento) {}

Arvore maiorElemento(Arvore raiz)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->dir == NULL)
        return raiz;
    else
        return maiorElemento(raiz->dir);
}