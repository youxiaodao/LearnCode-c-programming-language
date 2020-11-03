// 给计算机程序增加处理变量的命令, (提供26个具有单个英文字母变量名的变量很容易)
#include <stdio.h>
#include <math.h>

#define MAXOP   100     // MAX size of operand or operator
#define NUMBER  '0'     // singnal that a number was found

int getop(char []);
void push(double);
double pop(void);

int main(int argc, char const *argv[])
{
    int i, type, var = 0;
    double op2, v;
    char s[MAXOP];
    double variable[26];
    for (i = 0;i<26;i++) {
        variable[i] = 0.0;
    }
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
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
            if (op2 != 0.0) {
                push(pop() / op2);
            }else{
                printf("error: zero divisor\n");
            }
            break;
        case '=':
            pop();
            if (var >= 'A' && var <= 'Z')
                variable[var - 'A'] = pop();
            else
                printf("error: no variable name\n");
            break;
        case '\n':
            v = pop();
            printf("value:\t%.8g\n", v);
            break;
        default:
            if(type >= 'A' && type <= 'Z') {
                push(variable[type - 'A']);
            } else if (type == 'v') {
                push(v);
            } else {
                printf("error: unknown command %s\n", s);
            }
            break;
        }
        var = type;
    }
    
    return 0;
}



