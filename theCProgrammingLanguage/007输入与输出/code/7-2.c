// 编写程序, 以合理的方式打印任何输入。该程序至少能根据用户的习惯以八进制或十六进制打印非图形字符，并截断长文本行

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100 // max number of chars in one line
#define OCTLEN  6   // length of an octal value

// print arbitraty input in a sensible way
int main(int argc, char const *argv[]) {
    int c, pos;
    int inc(int pos, int n);

    pos = 0;        // position in the line
    while ((c = getchar()) != EOF) {
        if (iscntrl(c) || c == ' ') {       // non-graphic or blank
            pos = inc(pos, OCTLEN);
            printf(" \\%03o ", c);      // newline character
            if (c == '\n') {
                pos = 0;
                putchar('\n');
            }
        } else {
            pos = inc(pos, 1);
        }
    }
    return 0;
}

// increment position counter for output
int inc(int pos, int n) {
    if (pos + n < MAXLINE) {
        return pos + n;
    } else {
        putchar('\n');
        return n;
    }
}

/*
宏iscntrl来自头文件 <ctype.h>
它的用途是找非显示字符
    删除控制符 八进制 0177
    普通控制字符 小于八进制 040
        ../
非显示字符将打印为长度是OCTLEN个字符的八进制数字(数字前有一个空格和一个反斜杠\, 数字后又有一个空格)

在遇到换行符时， 变量pos重新设置为0

inc函数用来对输出行上的写位置 (pos + n) 进行计算, 如果输出行上的剩余空间不足n个字符， 就在当前位置插入一个换行符

*/