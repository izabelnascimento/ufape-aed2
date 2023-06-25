#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

Arvore inserirAvl(int valor, Arvore raiz, int *cresceu)
{
    if (raiz == NULL)
    {
        Arvore novo = (Arvore)malloc(sizeof(struct no));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    }
    else
    {
        if (valor > raiz->valor)
        {
            raiz->dir = inserirAvl(valor, raiz->dir, cresceu);
            if (*cresceu)
            {
                switch (raiz->fb)
                {
                case -1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    return raiz;
                    break;
                case 0:
                    raiz->fb = 1;
                    *cresceu = 1;
                    return raiz;
                    break;
                case 1:
                    // isso ocorreu raiz->fb = 2;
                    *cresceu = 0;
                    return rotacao(raiz);
                    break;
                default:
                    break;
                }
            }
        }
        else
            raiz->esq = inserirAvl(valor, raiz->esq, cresceu);
        if (*cresceu)
        {
            switch (raiz->fb)
            {
            case -1:
                raiz->fb = 0;
                *cresceu = 0;
                return rotacao(raiz);
                break;
            case 0:
                raiz->fb = -1;
                *cresceu = 1;
                return raiz;
                break;
            default:
                break;
            }
        }
        return raiz;
    }
}

Arvore rotacao(Arvore pivo)
{
    // caso +2
    if (pivo->fb > 0)
    {
        if (pivo->dir->fb >= 0)
        {
            return rotacaoSimplesEsq(pivo);
        }
        else
        {
            return rotacaoDuplaEsq(pivo);
        }
    }
    else
    {
        // caso -2
        if (pivo->esq->fb < 0)
        {
            return rotacaoSimplesDir(pivo);
        }
        else
        {
            return rotacaoDuplaDir(pivo);
        }
    }
}

Arvore rotacaoSimplesDir(Arvore pivo)
{
    Arvore u, t1, t2, t3;
    u = pivo->esq;
    t1 = u->esq;
    t2 = u->dir;
    t3 = pivo->dir;

    if (u->fb == -1)
    {
        pivo->fb = 0;
        u->fb = 0;
    }
    else
    {
        pivo->fb = -1;
        u->fb = 1;
    }

    pivo->esq = t2;
    u->dir = pivo;
    return u;
}

Arvore rotacaoDuplaDir(Arvore pivo)
{
    Arvore u, v, t1, t2, t3, t4;
    u = pivo->esq;
    v = u->dir;
    t1 = u->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = pivo->dir;

    switch (v->fb)
    {
    case -1:
        u->fb = 0;
        pivo->fb = 1;
        break;
    case 0:
        u->fb = 0;
        pivo->fb = 0;
        break;
    case 1:
        u->fb = -1;
        pivo->fb = 0;
        break;
    default:
        break;
    }
    v->fb = 0;

    u->dir = t2;
    v->esq = u;
    pivo->esq = t3;
    v->dir = pivo;
    return v;
}

Arvore rotacaoDuplaEsq(Arvore pivo)
{
    Arvore u, v, t1, t2, t3, t4;
    u = pivo->dir;
    v = u->esq;
    t1 = pivo->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = u->dir;

    switch (v->fb)
    {
    case -1:
        pivo->fb = 0;
        u->fb = 1;
        break;
    case 0:
        pivo->fb = 0;
        u->fb = 0;
        break;
    case 1:
        pivo->fb = -1;
        u->fb = 0;
        break;
    default:
        break;
    }
    v->fb = 0;

    u->esq = t3;
    v->dir = u;
    pivo->dir = t2;
    v->esq = pivo;
    return v;
}

Arvore rotacaoSimplesEsq(Arvore pivo)
{
    Arvore u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;

    if (u->fb == 1)
    {
        pivo->fb = 0;
        u->fb = 0;
    }
    else
    {
        pivo->fb = 1;
        u->fb = -1;
    }

    pivo->dir = t2;
    u->esq = pivo;
    return u;
}

void preOrderAvl(Arvore raiz)
{
    if (raiz != NULL)
    {
        printf("%d[%d] ", raiz->valor, raiz->fb);
        preOrderAvl(raiz->esq);
        preOrderAvl(raiz->dir);
    }
}

void inOrderBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        inOrderBst(raiz->esq);
        printf("[%d]", raiz->valor);
        inOrderBst(raiz->dir);
    }
}

void posOrderBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        posOrderBst(raiz->esq);
        posOrderBst(raiz->dir);
        printf("[%d]", raiz->valor);
    }
}