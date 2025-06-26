#ifndef EXPRESSAO_H
#define EXPRESSAO_H

void infixToPostfix(char *infix, char *postfix);
float evaluatePostfix(char *postfix);
void postfixToInfix(char *postfix, char *infix);

#endif

