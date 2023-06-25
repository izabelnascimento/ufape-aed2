#ifndef AVL_H
#define AVL_H

typedef struct no
{
    int valor;
    int fb;
    struct no *esq, *dir;
} no;

typedef no *Arvore;

Arvore inserirAvl(int valor, Arvore raiz, int *cresceu);
Arvore rotacao(Arvore pivo);
Arvore rotacaoSimplesDir(Arvore pivo);
Arvore rotacaoSimplesEsq(Arvore pivo);
Arvore rotacaoDuplaEsq(Arvore pivo);
Arvore rotacaoDuplaDir(Arvore pivo);
Arvore removerAvl(int num, Arvore raiz, int *diminuiu);
Arvore maiorAvl(Arvore raiz);
void preOrderAvl(Arvore raiz);

void inOrderAvl(Arvore raiz);
void posOrderAvl(Arvore raiz);

#endif
