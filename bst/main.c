#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // declarar uma árvore
    Arvore arvore;
    int opcao, aux, qtd, num;

    // inicializar a árvore como uma árvore vazia
    arvore = NULL;

    while (1)
    {
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            scanf("%d", &aux);
            arvore = inserirBst(aux, arvore);
            break;
        case 2:
            preOrderBst(arvore);
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
        case 5:
            reversoBst(arvore);
            printf("\n");
            break;
        case 6:
            qtd = qtdPrimoBst(arvore);
            printf("%d\n", qtd);
            break;
        case 7:
            scanf("%d", &num);
            sucessorBst(num, arvore);
            break;
        case 8:
            scanf("%d", &num);
            caminhoBst(num, arvore);
            printf("\n");
            break;
        case 9:
            // TODO
            scanf("%d\n", &num);
            arvore = removerBst(num, arvore);
            break;
        case 10:
            num = somatorioBst(arvore);
            printf("%d\n", num);
            break;
        case 11:
            // TODO
            scanf("%d", &num);
            arvore = podarBst(num, arvore);
            break;
        case 12:
            scanf("%d", &num);
            arvore = reajustaBst(num, arvore);
            break;
        case 13:
            scanf("%d", &num);
            printf("%d\n", exiteBst(num, arvore));
            break;
        case 14:
            scanf("%d", &num);
            descendentesBst(num, arvore);
            printf("\n");
            break;
        case 15:
            printf("%d\n", alturaBst(arvore));
            break;
        case 99:
            exit(0);
        }
    }
}
