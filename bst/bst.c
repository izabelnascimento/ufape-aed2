#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

Arvore inserirBst(int valor, Arvore raiz)
{
    // caso base - inserir em uma árvore vazia
    if (raiz == NULL)
    {
        Arvore novo = (Arvore)malloc(sizeof(struct no));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;
        // o retorno é a raiz da sub-árvore unitária que foi iniciada
        return novo;
    }
    // caso recursivo/indutivo
    else
    {
        if (valor > raiz->valor)
        {
            raiz->dir = inserirBst(valor, raiz->dir);
        }
        else
        {
            raiz->esq = inserirBst(valor, raiz->esq);
        }
        return raiz;
    }
}

void preOrderBst(Arvore raiz)
{
    if (raiz != NULL)
    {
        // processar a raiz relativa
        printf("[%d]", raiz->valor);

        // encadeamentos recursivos esq, dir
        preOrderBst(raiz->esq);
        preOrderBst(raiz->dir);

    } // else caso base implícito não faz nada
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
            {
                primo = 0;
            }
        }
        if (primo == 1)
        {
            qtd++;
        }

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
        {
            return raiz->valor;
        }
        else
        {
            return menor;
        }
    }
    else
    {
        return -1;
    }
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
                {
                    printf("-1\n");
                }
                else
                {
                    printf("%d\n", ultimo);
                }
            }
            else
            {
                printf("%d\n", suc);
            }
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
    {
        printf("-1\n");
    }
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
    // caso arvore vazia
    if (raiz != NULL)
    {
        // encontrou o elemento
        if (valor == raiz->valor)
        {
            // verificar 0, 1esq, 1dir ou 2 filhos
            // caso 0
            if (raiz->esq == NULL && raiz->dir == NULL)
            {
                free(raiz);
                return NULL;
            }
            // caso 1esq
            if (raiz->esq != NULL && raiz->dir == NULL)
            {
                Arvore aux = raiz->esq;
                free(raiz);
                return aux;
            }
            // caso 1dir
            if (raiz->dir != NULL && raiz->esq == NULL)
            {
                Arvore aux = raiz->dir;
                free(raiz);
                return aux;
            }
            // caso 2
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