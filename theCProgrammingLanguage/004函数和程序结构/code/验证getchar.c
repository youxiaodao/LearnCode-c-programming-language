#include <stdio.h>
#include <stdlib.h>

#define MAXOP   100     // 操作数或运算符的最大长度
#define NUMBER '0'      // 标识找到一个数

// getchar 一次只返回一个字符

void main() {
    int type;
    double op2;
    char s[MAXOP];

    while((type = getchar()) != EOF) {
        printf("type:: %c\n", type);
        switch (type) {
            case NUMBER:
                printf("case Number\n");
                break;
            case '+':
                printf("case +\n");
                break;
            case '*':
                printf("case *\n");
                break;
            case '-':
                printf("case -\n");
                break;
            case '/':
                printf("case /\n");
                break;
            case '\n':
                printf("case kongge \n");
                break;
            default:
                printf("case %c\n",type);
                break;
        }
    }
}
