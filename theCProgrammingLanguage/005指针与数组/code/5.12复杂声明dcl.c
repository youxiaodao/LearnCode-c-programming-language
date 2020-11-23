/*
第一个程序dcl复杂一些, 他将C语言的声明转换为文字描述
char **argv
    argv: pointer to pointer to char
int (*daytab)[13]
    daytab: pointer to array[13] of int
int *daytab[13]
    daytab: array[13] of pointer to int
void (*comp)()
    comp: pointer to function returning void
char (*(*x[3])())[5]
    x: array[3] of pointer to function returning
    pointer to array[5] of char

dcl 是基于声明符的语法编写的 附录A以及8.5节将详细讲解
    dcl:  前面带有可选的 * 的  direct-dcl
    direct-dcl: name
                (dcl)
                direct-dcl()
                direct-dcl[可选的长度]
简而言之: 申明符dcl就是前面可能带有多个*的direct-dcl
    direct-dcl 可以是name,由一对圆括号括起来的dcl,后面跟有一对圆括号的direct-dcl,后面跟有用方括号括起来的表示可选长度的direct-dcl

    该语法可用来对C语言的声明进行分析

*/

// 只能处理char int 这样的简单数据类型
// 全局变量和主程序

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100

enum {NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
int gettoken(void);         // 
int tokentype;              // 最后一个记号的类型
char token[MAXTOKEN];       // 最后一个记号字符串
char name[MAXTOKEN];        // 标识符名
char datatype[MAXTOKEN];    // 数据类型为char int 等
char out[1000];

int main(int argc, char const *argv[]) {    // 该行的第一个即耗是数据类型
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();              // 分析该行的其余部分
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
// 通过 gettoken 用来跳过空格与制表符，以查找输入中的下一个标记
// 记号(token)可以是一个名字, 一对圆括号， 可能包含一个一个数字的一对方括号， 也可以是其它任何单个字符

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';) {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}
// 有关getch和ungetch 见第4章
// 


// dcl 函数：对一个声明符进行语法分析
void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '+';)    // 统计字符*的个数
        ns++;
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

// dirdcl: 分析一个直接声明
void dirdcl(void) {
    int type;

    if (tokentype == '(') {                 // 形式为(dcl)
        dcl();
        if (tokentype != ')') {
            printf("error: missing ) \n");
        }
    } else if (tokentype == NAME) {     // 变量名
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl) \n");
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}


// undcl函数： 将文字描述转换为声明
int main(int argc, char const *argv[])
{
    int type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF) {
        strcpy(out, token);
        while((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcat(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

