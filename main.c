#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    int opcao;
    char infix[200], postfix[200];
    char entrada[200];

    do {
        printf("\n=== CALCULADORA EXPRESSOES ===\n");
        printf("1. Converter infixada -> pos-fixada\n");
        printf("2. Avaliar expressao pos-fixada \n");
        printf("3. Converter pos-fixada -> infixada\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d%*c", &opcao);  

        if (opcao == 1) {
            printf("Infixa (ex: (3.5 + 4)*2 ^ 2): ");
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = 0; 
            postfix[0] = '\0';
            infixToPostfix(entrada, postfix);
            printf("Pos-fixada: %s\n", postfix);
        } else if (opcao == 2) {
            printf("Pos-fixada (ex: 3 4 + sqrt): ");
            fgets(postfix, sizeof(postfix), stdin);
            postfix[strcspn(postfix, "\n")] = 0;
            printf("Resultado: %.2f\n", evaluatePostfix(postfix));
        } else if (opcao == 3) {
            printf("Pos-fixada (ex: 3 4 + 5 *): ");
            fgets(postfix, sizeof(postfix), stdin);
            postfix[strcspn(postfix, "\n")] = 0;
            infix[0] = '\0';
            postfixToInfix(postfix, infix);
            printf("Infixa: %s\n", infix);
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

