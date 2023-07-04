#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Arvore arvore, auxArvore;
    int opcao, aux, qtd, num, fb, diminuiu;

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
            scanf("%d", &num);
            arvore = removerAvl(num, arvore, &diminuiu);
            break;
        case 4:
            inOrderAvl(arvore);
            printf("\n");
            break;
        case 5:
            posOrderAvl(arvore);
            printf("\n");
            break;
        case 6:
            auxArvore = maiorAvl(arvore);
            if (auxArvore != NULL)
                printf("%d\n", auxArvore->valor);
            else
                printf("-1\n");
            break;
        case 99:
            exit(0);
        }
    }
}
