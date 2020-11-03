/* while(下一个运算符或者操作数不是文件结束指示符)
        if(是数)
            将该数压入栈中
        else if (是运算符)
            弹出所需数目的操作数
            执行运算
            将结果压入栈中
        else if (是换行符)
            弹出并打印栈顶的值
        else
            出错
*/

#include <stdio.h>
#include <stdlib.h>     // 为了使用 atof()

#define MAXOP   100     // 操作数或运算符的最大长度
#define NUMBER '0'      // 标识找到一个数

int getop(char []);
void push(double);
double pop(void);

// 逆波兰计算器
void main() {
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
    // return 0;
}

#define MAXVAL 100      // 找val的最大深度

int sp = 0;             // 下一个空闲栈位置
double val[MAXVAL];     // 值栈

// push函数: 把f压入值栈中
void push(double f) {
    if (sp < MAXOP) {
        val[sp++] = f;
    } else {
        printf("error: stack full, cant push %g\n", f);
    }
    printf("current_f:%f\n",f);
    printf("val::");
    for(int i = 0; i<MAXVAL;i++){
        printf("%g",val[i]);
    }
    printf("\n");
}


// pop函数: 弹出并返回栈顶的值
double pop(void) {
    printf("pop\n");
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


// getop函数: 获取下一个运算符或者数值操作数
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
    //printf("s[] ::%s\n", s);
    // s[] main 中定义的栈
    int i, c;
    // 检查第一位
    while ((s[0] = c = getch())  == ' ' || c == '\t')
        printf("getop::::check the first<%c>\n", c);
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {          
        printf("getop::::no digit<%c>\n", c);
        return c;       //不是数
    }
    i = 0;

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
    printf("getop::::has number\n");
    return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE]; // 用于ungetch函数的缓冲区
int bufp = 0;       // buf中下一个空闲位置

int getch(void) {
    printf("gettch::\n");
    return (bufp > 0) ? buf[--bufp] : getchar();  // 如果bufp是1 取得就是0,  下一个空闲位置这个解释真棒
}

void ungetch(int c) {  // 把字符压回到输入中
    printf("ungetch\n");
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
    printf("buf::<%s>", buf);
}
