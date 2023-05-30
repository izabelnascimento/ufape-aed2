#ifndef BST_H
#define BST_H

typedef struct no
{
    int valor;
    struct no *esq, *dir;
} no;

typedef no *Arvore;

Arvore inserirBst(int valor, Arvore raiz);
void preOrderBst(Arvore raiz);
void inOrderBst(Arvore raiz);
void posOrderBst(Arvore raiz);
void reversoBst(Arvore raiz);
int qtdPrimoBst(Arvore raiz);
void sucessorBst(int num, Arvore raiz);
void sucessorRecBst(int num, Arvore raiz, int ultimo);
void caminhoBst(int n, Arvore raiz);
Arvore removerBst(int num, Arvore raiz);
int somatorioBst(Arvore raiz);
Arvore podarBst(int num, Arvore raiz);
Arvore reajustaBst(int percent, Arvore raiz);
int exiteBst(int chave, Arvore raiz);
void descendentesBst(int num, Arvore raiz);
int alturaBst(Arvore raiz);
int alturaRecBst(Arvore raiz);
Arvore maiorBst(Arvore raiz);

#endif
