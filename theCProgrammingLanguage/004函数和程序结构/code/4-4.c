// 在栈操作中添加几个命令, 分别用于
//  在不弹出元素的情况下打印栈顶元素;
//  复制栈顶元素
//  交换栈顶两个元素的值
//  另外增加一个命令用于清空栈

#include <stdio.h>
#include <math.h>

#define MAXOP   100
#define NUMBER  '0'

int getop(char []);
void push(double);
double pop(void);

void clear(void);  // 清空

int main(int argc, char const *argv[])
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type=getop(s)) != EOF) {
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


// 和push，pop放在一起
int sp = 0;
void clear(void) {
    sp = 0;
}


/*
? 弹出栈顶元素 打印 压入
d 复制栈顶元素 出栈 压入两次
s 交换栈顶元素 出栈 再以相反的顺序压入
c 清除堆栈 将sp设置为0
*/