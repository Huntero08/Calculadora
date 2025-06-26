#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "expressao.h"

#define MAX 100

int precedencia(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int associatividadeEsquerda(char op) {
    if (op == '^') return 0;
    return 1; 
}

void infixToPostfix(char *infix, char *postfix) {
    char stack[MAX][MAX];
    int top = -1, j = 0;
    char token[MAX];
    int i = 0, k = 0;

    while (infix[i]) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        if (isalnum(infix[i]) || infix[i] == '.') {
            k = 0;
            while (isalnum(infix[i]) || infix[i] == '.') {
                token[k++] = infix[i++];
            }
            token[k] = '\0';
            strcat(postfix, token);
            strcat(postfix, " ");
            continue;
        }

        if (infix[i] == '(') {
            strcpy(stack[++top], "(");
        } else if (infix[i] == ')') {
            while (top >= 0 && strcmp(stack[top], "(") != 0) {
                strcat(postfix, stack[top--]);
                strcat(postfix, " ");
            }
            if (top >= 0) top--; 
        } else {
            char op[2] = {infix[i], '\0'};
            while (top >= 0 &&
                   ((associatividadeEsquerda(infix[i]) && precedencia(stack[top][0]) >= precedencia(infix[i])) ||
                   (!associatividadeEsquerda(infix[i]) && precedencia(stack[top][0]) > precedencia(infix[i])))) {
                strcat(postfix, stack[top--]);
                strcat(postfix, " ");
            }
            strcpy(stack[++top], op);
        }
        i++;
    }

    while (top >= 0) {
        strcat(postfix, stack[top--]);
        strcat(postfix, " ");
    }
}

float evaluatePostfix(char *postfix) {
    float stack[MAX];
    int top = -1;

    char *token = strtok(postfix, " ");
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack[++top] = strtof(token, NULL);
        } else if (strcmp(token, "+") == 0) {
            float b = stack[top--], a = stack[top--];
            stack[++top] = a + b;
        } else if (strcmp(token, "-") == 0) {
            float b = stack[top--], a = stack[top--];
            stack[++top] = a - b;
        } else if (strcmp(token, "*") == 0) {
            float b = stack[top--], a = stack[top--];
            stack[++top] = a * b;
        } else if (strcmp(token, "/") == 0) {
            float b = stack[top--], a = stack[top--];
            stack[++top] = a / b;
        } else if (strcmp(token, "^") == 0) {
            float b = stack[top--], a = stack[top--];
            stack[++top] = powf(a, b);
        } else if (strcmp(token, "sqrt") == 0) {
            float a = stack[top--];
            stack[++top] = sqrtf(a);
        } else if (strcmp(token, "sin") == 0) {
            float a = stack[top--];
            stack[++top] = sinf(a);
        } else if (strcmp(token, "cos") == 0) {
            float a = stack[top--];
            stack[++top] = cosf(a);
        }
        token = strtok(NULL, " ");
    }

    return stack[top];
}

void postfixToInfix(char *postfix, char *infix) {
    char stack[MAX][MAX];
    int top = -1;

    char *token = strtok(postfix, " ");
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])) || strchr(token, '.')) {
            strcpy(stack[++top], token);
        } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                   strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
                   strcmp(token, "^") == 0) {
            if (top < 1) {
                strcpy(infix, "Erro: expressao invalida");
                return;
            }
            char b[MAX], a[MAX], expr[MAX];
            strcpy(b, stack[top--]);
            strcpy(a, stack[top--]);
            snprintf(expr, MAX, "(%s %s %s)", a, token, b);
            strcpy(stack[++top], expr);
        } else if (strcmp(token, "sqrt") == 0 || strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0) {
            if (top < 0) {
                strcpy(infix, "Erro: expressao invalida");
                return;
            }
            char a[MAX], expr[MAX];
            strcpy(a, stack[top--]);
            snprintf(expr, MAX, "%s(%s)", token, a);
            strcpy(stack[++top], expr);
        }
        token = strtok(NULL, " ");
    }

    if (top == 0)
        strcpy(infix, stack[top]);
    else
        strcpy(infix, "Erro: expressao invalida");
}

