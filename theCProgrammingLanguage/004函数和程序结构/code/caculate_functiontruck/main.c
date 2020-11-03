#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100

int main(int argc, char const *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        printf("type:: %c\n", type);
        switch (type) {
            case NUMBER:
                printf("case Number::<>\n");
                push(atof(s));
                break;
            case '+':
                printf("case +\n");
                push(pop() + pop());
                break;
            case '*':
                printf("case *\n");
                push(pop() * pop());
                break;
            case '-':
                printf("case -\n");
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                printf("case /\n");
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                }else{
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf("value:\t%.8g\n", pop());
                break;
            default:
                printf("case default");
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
