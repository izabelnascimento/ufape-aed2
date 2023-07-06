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
int elementoRaiz(Arvore elemento);
enum Cor cor(Arvore elemento);

void preOrderRb(Arvore raiz);

// Arvore removerRb(int num, Arvore raiz);

#endif
