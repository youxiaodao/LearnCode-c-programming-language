// 改写 第四章中的后缀计算器程序, 用scanf函数或者sscanf函数实现输入以及数的转换

#include <stdio.h>
#include <ctype.h>

#define NUMBER  '0'     // signal that a number was found

// get next operator or numeric operand
int getop(char s[]) {
    int c, i, rc;
    static char lastc[] = " ";

    sscanf(lastc, "%c", &c);
    lastc[0] = ' ';

    while ((s[0] = c) == ' ' || c == '\t') {
        if (scanf("%c", &c) == EOF) {
            c = EOF;
        }
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        do {
            rc = scanf("%c", &c);
            if (!isdigit(s[++i] = c)) {
                break;
            }
        } while (rc != EOF);
    }
    if (c == '.') {    // collect fraction part
        do {
            rc = scanf("%c", &c);
            if (!isdigit(s[++i] = c)) {
                break;
            }
        } while (rc != EOF);
    }   
    s[i] = '\0';
    if (rc != EOF) {
        lastc[0] = c;
    }
    return NUMBER;
}

/*
    只需对getop做一些修改
    在调用getop函数时，字符总是跟在一个数字的后面出现。lastc是具有两个元素的静态数组, 用于记录最后读入的字符(sscanf 读入一个字符串)
    函数调用
        sscanf(lastc, "%c", &c)
    把 lastc[0]中的字符读到变量c中, 你可以用赋值语句
        c = lastc[0]
    来替代

    scanf的返回值是成功地取得匹配和赋值地输入项地个数，它在读到文件尾时将返回EOF
    此外，因为题目要求我们必须使用scanf来处理输入，所以，我们要把表达式
        isdigit(s[++i] = c = getch())
    替换为
        rc = scanf("%c", &c);
        if (!isdigit(s[++i] = c))
            break;
    即：调用scanf来读取字符，把字符赋值为字符串s，再测试它是不是一个数字
    注意：当scanf读到EOF时, 它将不会改变变量c地值，这正是我们增加下面这条测试地原因
        rc != EOF
    如果只是利用 scanf 来每次读入一个字符,  那么将不会给getop带来多大地性能改善
    
*/