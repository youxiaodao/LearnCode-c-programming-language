// 在有了基本框架后, 对计算器程序进行扩充就比较简单了, 在改程序中加入取模运算符, 并注意考虑负数得情况
#include <stdio.h>
#include <math.h>       // for atof

#define MAXOP 100       // max size of operand or oprator
#define NUMBER '0'      // signal that a number was found

int getop(char []);
void push(double);
double pop(void);

void main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(stof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if ( op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if ( op2 != 0.0) 
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
            case '\n':
                printf("\t%.9g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER  '0'

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int c, i;
    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[i] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.') {
            s[++i] = c;
        } else {
            if (c != EOF) {
                ungetch(c);
            }
            return '-';
        }
    }
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}


/*
 fmod 计算 取模
 如何判断负数
    - 号后面没有空格，直接跟数字
    


*/