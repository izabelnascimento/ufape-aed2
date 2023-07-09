#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Arvore arvore;
    int opcao, aux, num;

    inicializar(&arvore);

    while (1)
    {
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            scanf("%d", &aux);
            inserirRb(aux, &arvore);
            break;
        case 2:
            preOrderRb(arvore);
            printf("\n");
            break;
        case 3:
            scanf("%d\n", &num);
            removerRb(num, &arvore);
            break;
        case 4:
            printf("------------------------------------------------------------------------------------------------\n");
            break;
        case 99:
            exit(0);
        }
    }
}
