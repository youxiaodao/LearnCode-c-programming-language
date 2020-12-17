// 修改undcl程序，使它在把文字描述转换为声明的过程中不会生成多余的圆括号

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int nexttoken(void);

int tokentype;      // type of last token
char token[MAXTOKEN];   // last token string
char out[1000];

// convert word description to declaration
int main(int argc, char const *argv[]) {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                strcat(out, token);
            } else if (type == '*') {
                if ((type = nexttoken()) == PARENS || type == BRACKETS) {
                    sprintf(temp, "(*%s)", out);
                } else {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
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


enum { NO, YES };

// get the next token and push it back
int nexttoken(void) {
    int type;
    extern int prevtoken;

    type = gettoken();
    prevtoken = YES;
    return type;
}

/*
    如果 "x是一个指向char的指针", undcl程序的输入将是: x * char
    改进前 的undcl的程序的输出结果是：
        char (*x)
    但这个输出结果中的括号是多余的
    事实上，只有当下一个记号是 （）或者 [] 时，undcl程序才有必要再自己的输出结果中使用括号。
    例如, "如果daytab是一个指针，它指向一个有[13]个int元素的数组", undcl程序的输入将是:
        daytab * [13] int
    改进前的undcl的输出结果是
        int (*daytab)[13]
    就是正确的。但是, “如果daytab是一个有[13]个元素的指针数组, 数组中的每个元素分别指向一个int", undcl程序的输入将是
        daytab [13] * int
    改进前的...
        int (*daytab[13])
    中就会有多余的圆括号

    我们对undcl进行了修改，让他检查下一个记号是不是 () 或 [] 
    如果是, undcl 程序就必须给他加上括号
    否则, 输出结果中的括号就是多余的
    也就是说, 我们必须根据undcl程序输入中的下一个记号来决定是否需要添加括号

    我们编写了一个简单的nexttoken函数, 它将调用gettoken，记录已经读入一个记号的事实并返回该记号的类型
    gettoken是我们再解答练习5-18时编写的一个函数
    它在读入下一个记号前会先检查是否已经有一个可用的记号了

    改进后的undcl程序将不再产生多余的括号。例如，如果它的输入是：
        x * char
    改进后的undcl程序的输出结果就将是
        char *x
    如果输入是
        daytab * [13] int
    改进后的undcl程序的输出结果将是 、
        int (*daytab)[13]
    而如果输入是
        daytab [13] * int
    改进后的输出
        int *daytab[13]
*/
