
#include <stdio.h>
#include <ctype.h>

#define NUMBER  '0'     // signal that a number was found

// get next operator or numeric operand
int getop(char s[]) {
    int c, rc;
    float f;

    while ((rc = scanf("%c", &c)) != EOF) {
        if ((s[0] = c) != ' ' && c != '\t') {
            break;
        }
    }
    s[1] = '\0';
    if (rc == EOF) {
        return EOF;
    } else if (!isdigit(c) && c != '.') {
        return c;
    }
    ungetc(c, stdin);
    scanf("%f", &f);
    sprintf(s, "%f", f);
    return NUMBER; 
}

/*
    我们先通过一个while循环以每次读一个字符地方法跳过空格和制表符。这个while循环再读到文件尾标记EOF时也终止
    如果读到地是一个数字字符或者是一个小数点
    我们就用库函数ungetc把它重新压回输入缓冲区, 然后再完整地读入整个数字
    因为getop返回地是一个浮点数值，所以我们还要用sprintf把此案两f中地浮点数值转换为变量s中地一个字符串
*/