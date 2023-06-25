#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Arvore arvore, auxArvore;
    int opcao, aux, qtd, num, fb;

    arvore = NULL;
    auxArvore = NULL;

    while (1)
    {
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            scanf("%d", &aux);
            arvore = inserirAvl(aux, arvore, &fb);
            break;
        case 2:
            preOrderAvl(arvore);
            printf("\n");
            break;
        case 3:
            inOrderBst(arvore);
            printf("\n");
            break;
        case 4:
            posOrderBst(arvore);
            printf("\n");
            break;
        case 99:
            exit(0);
        }
    }
}
