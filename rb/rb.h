#ifndef RB_H
#define RB_H

enum Cor
{
    VERMELHO,
    PRETO,
    DUPLO_PRETO
};

typedef struct no
{
    int valor;
    enum Cor cor;
    struct no *esq, *dir, *pai;
} no;

typedef no *Arvore;

void inicializar(Arvore *raiz);

Arvore inserirRb(int valor, Arvore *raiz);
void ajustar(Arvore *raiz, Arvore elemento);

void rotacaoSimplesDir(Arvore *raiz, Arvore pivo);
void rotacaoSimplesEsq(Arvore *raiz, Arvore pivo);

int isElementoRaiz(Arvore elemento);
enum Cor cor(Arvore elemento);
Arvore tio(Arvore elemento);
Arvore irmao(Arvore elemento);
int isFilhoEsquerdo(Arvore elemento);
int isFilhoDireito(Arvore elemento);

void preOrderRb(Arvore raiz);

void removerRb(int valor, Arvore *raiz);
void reajustar(Arvore *raiz, Arvore elemento);
Arvore maiorElemento(Arvore raiz);
void retirDuploPreto(Arvore *raiz, Arvore elemento);

#endif
