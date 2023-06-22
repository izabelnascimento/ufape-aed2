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
            // return rotacaoDuplaDir(pivo);
            // rotacao dupla pode ser duas chamadas de rot simples
            // caso use isso não pode atualizar o fb dentro da rotacao
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

    pivo->fb = 0;
    u->fb = 0;
    // if (u->fb == 1)
    // {
    //     pivo->fb = 0;
    //     u->fb = 0;
    // }
    // else
    // {
    //     //
    // }

    pivo->esq = t2;
    u->dir = pivo;
    return u;
}

// Arvore rotacaoDuplaDir(Arvore pivo)
// {
//     Arvore u, v, t1, t2, t3, t4;
//     u = pivo->esq;
//     v = u->esq;
//     t1 = pivo->esq;
//     t2 = v->esq;
//     t3 = v->dir;
//     t4 = u->dir;

//     switch (v->fb)
//     {
//     case -1:
//         // pivo->fb = ? ;
//         // u->fb =    ? ;
//         // v->fb =    ? ;
//         break;
//     case 0:
//         break;
//     case 1:
//         break;
//     default:
//         break;
//     }
// }

Arvore rotacaoDuplaEsq(Arvore pivo)
{
    Arvore u, v, t1, t2, t3, t4;
    u = pivo->dir;
    v = u->esq;
    t1 = pivo->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = u->dir;

    // switch (v->fb)
    // {
    // case -1:
    //     // pivo->fb = ? ;
    //     // u->fb =    ? ;
    //     // v->fb =    ? ;
    //     break;
    // case 0:
    //     break;
    // case 1:
    //     break;
    // default:
    //     break;
    // }
    pivo->dir = rotacaoSimplesDir(u);
    return rotacaoSimplesEsq(pivo);
}

Arvore rotacaoSimplesEsq(Arvore pivo)
{
    Arvore u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;

    pivo->fb = 0;
    u->fb = 0;
    // if (u->fb == 1)
    // {
    //     pivo->fb = 0;
    //     u->fb = 0;
    // }
    // else
    // {
    //     //
    // }

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

void reversoBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        reversoBst(raiz->dir);
        printf("[%d]", raiz->valor);
        reversoBst(raiz->esq);
    }
}

int qtdPrimoBst(Arvore raiz)
{
    int qtd = 0, i, primo = 1;
    if (raiz != NULL)
    {
        for (i = 2; i < raiz->valor; i++)
        {
            if (raiz->valor % i == 0)
                primo = 0;
        }
        if (primo == 1)
            qtd++;
        qtd = qtd + qtdPrimoBst(raiz->dir);
        qtd = qtd + qtdPrimoBst(raiz->esq);
    }
    return qtd;
}

int buscarMenorBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        int menor = buscarMenorBst(raiz->esq);
        if (menor == -1)
            return raiz->valor;
        else
            return menor;
    }
    else
        return -1;
}

void sucessorBst(int num, Arvore raiz)
{
    sucessorRecBst(num, raiz, num);
}

void sucessorRecBst(int num, Arvore raiz, int ultimo)
{
    if (raiz != NULL)
    {
        int suc;
        if (num == raiz->valor)
        {
            suc = buscarMenorBst(raiz->dir);
            if (suc == -1)
            {
                if (ultimo <= num)
                    printf("-1\n");
                else
                    printf("%d\n", ultimo);
            }
            else
                printf("%d\n", suc);
        }
        else if (num < raiz->valor)
        {
            sucessorRecBst(num, raiz->esq, raiz->valor);
            return;
        }
        else if (num > raiz->valor)
        {
            sucessorRecBst(num, raiz->dir, ultimo);
            return;
        }
    }
    else
        printf("-1\n");
}

void caminhoBst(int num, Arvore raiz)
{
    if (raiz != NULL)
    {
        if (num == raiz->valor)
        {
            printf("[%d]", raiz->valor);
        }
        else if (num < raiz->valor)
        {
            printf("[%d]", raiz->valor);
            caminhoBst(num, raiz->esq);
        }
        else if (num > raiz->valor)
        {
            printf("[%d]", raiz->valor);
            caminhoBst(num, raiz->dir);
        }
    }
    else
    {
        printf("-1");
    }
}

Arvore maiorBst(Arvore raiz)
{
    if (raiz == NULL)
        return NULL;
    if (raiz->dir == NULL)
        return raiz;
    else
        return maiorBst(raiz->dir);
}

Arvore removerBst(int valor, Arvore raiz)
{
    if (raiz != NULL)
    {
        if (valor == raiz->valor)
        {
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                return NULL;
            }
            if (raiz->esq != NULL && raiz->dir == NULL)
            {
                Arvore aux = raiz->esq;
                free(raiz);
                return aux;
            }
            if (raiz->dir != NULL && raiz->esq == NULL)
            {
                Arvore aux = raiz->dir;
                free(raiz);
                return aux;
            }
            int maiorValorEsq = maiorBst(raiz->esq)->valor;
            raiz->valor = maiorValorEsq;
            raiz->esq = removerBst(maiorValorEsq, raiz->esq);
        }
        if (valor > raiz->valor)
            raiz->dir = removerBst(valor, raiz->dir);
        else
            raiz->esq = removerBst(valor, raiz->esq);
    }
    return raiz;
}

int somatorioBst(Arvore raiz)
{
    int soma = 0;
    if (raiz != NULL)
    {
        soma = soma + raiz->valor;
        soma = soma + somatorioBst(raiz->esq);
        soma = soma + somatorioBst(raiz->dir);
    }
    return soma;
}

Arvore freeBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        if (raiz->dir == NULL && raiz->esq == NULL)
        {
            free(raiz);
            return NULL;
        }
        if (raiz->dir != NULL || raiz->esq != NULL)
        {
            raiz->esq = freeBst(raiz->esq);
            raiz->dir = freeBst(raiz->dir);
        }
        free(raiz);
    }
    return raiz;
}

Arvore podarBst(int valor, Arvore raiz)
{
    if (raiz != NULL)
    {
        if (valor == raiz->valor)
        {
            freeBst(raiz);
            return NULL;
        }
        else if (valor > raiz->valor)
            raiz->dir = podarBst(valor, raiz->dir);
        else
            raiz->esq = podarBst(valor, raiz->esq);
    }
    return raiz;
}

Arvore reajustaBst(int percent, Arvore raiz)
{
    if (raiz != NULL)
    {
        raiz->valor = raiz->valor + raiz->valor * percent / 100;
        raiz->dir = reajustaBst(percent, raiz->dir);
        raiz->esq = reajustaBst(percent, raiz->esq);
        return raiz;
    }
    return NULL;
}

int exiteBst(int chave, Arvore raiz)
{
    if (raiz != NULL)
    {
        if (chave == raiz->valor)
        {
            return 1;
        }
        else if (chave < raiz->valor)
        {
            exiteBst(chave, raiz->esq);
        }
        else if (chave > raiz->valor)
        {
            exiteBst(chave, raiz->dir);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

void descendentesBst(int num, Arvore raiz)
{
    if (raiz != NULL)
    {
        if (num == raiz->valor)
        {
            inOrderBst(raiz->esq);
            inOrderBst(raiz->dir);
        }
        else if (num < raiz->valor)
        {
            descendentesBst(num, raiz->esq);
        }
        else if (num > raiz->valor)
        {
            descendentesBst(num, raiz->dir);
        }
    }
}

int alturaBst(Arvore raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    return alturaRecBst(raiz) + 1;
}
int alturaRecBst(Arvore raiz)
{
    int altura = 0, alturaEsq = 0, alturaDir = 0;
    if (raiz != NULL)
    {
        if (raiz->dir != NULL)
        {
            alturaDir++;
            alturaDir = alturaDir + alturaRecBst(raiz->dir);
        }
        if (raiz->esq != NULL)
        {
            alturaEsq++;
            alturaEsq = alturaEsq + alturaRecBst(raiz->esq);
        }
        if (alturaDir >= alturaEsq)
        {
            return alturaDir;
        }
        else
        {
            return alturaEsq;
        }
    }
    return altura;
}