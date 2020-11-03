/* 
    给计算器程序增加访问sin,exp,与pow等库函数的操作,
    有关这些库函数的详细信息,请参见附录B.4
*/
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXOP   100
#define NUMBER  '0'
#define NAME  'n'

int getop(char []);
void push(double);
double pop(void);
void mathfnc(char []);


int main(int argc, char const *argv[]) {
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type=getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case NAME:
                mathfnc(s);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0){
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '?':
                op2 = pop();
                printf("\t%.8g\n", op2);
                push(op2);
                break;
            case 'c':
                clear();
                break;
            case 'd':
                op2 = pop();
                push(op2);
                push(op2);
                break;
            case 's':
                op1 = pop();
                op2 = pop();
                push(op1);
                push(op2);
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

void mathfnc(char s[]) {
    double op2;
    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else
        printf("error: %s not suppored\n", s);
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define NUMBER  '0' // signal that a number was found
#define NAME    'n' // signal that a name was found

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int c, i;
    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    i = 0;
    if (islower(c)) {   // command or name
        while (islower(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);     // went one char too far 
        if(strlen(s) > 1)       // >1char it is NAME
            return NAME;        
        else
            return c;       // it may be a command
    }
    if (!isdigit(c) && c != '.')
        return c;       // not a number
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

