// 编写detab，将输入中的制表符替换成适当数目的空格，使空格充满到下一个制表符终止位的地方，
// 假设制表符终止位的位置是固定的，比如每隔n列就会出现一个制表符终止位。
// n应该作为变量还是符号常量呢？
#include <stdio.h>
#define TABINC 8  // TAB increment size

int main(int argc, char const *argv[])
{
    int c,nb,pos;
    nb = 0; // number of blanks necessry
    pos = 1; // position of character in line
    while((c = getchar()) != EOF) {
        if(c == '\t') {  //tab character
            nb = TABINC - (pos-1) % TABINC;
            while(nb > 0 ) {
                putchar(' ');
                ++pos;
                --nb;
            }
        } else if (c == '\n') {  // newline character
            putchar(c);
            pos = 1;
        } else {  // all other characters
            putchar(c);
            ++pos;
        }
    }
    return 0;
}
/* 假设每隔TABINC的位置都会出现一个制表符终止位， 在这个程序中，我们把TABINC定义为8
    变量pos是程序在文本行中当前的位置。
    当遇到制表符的时候，程序计算 要达到下一个制表符终止位需要的空格数nb。
    如果遇到的是一个换行符，陈序将把它打印出来，并把变量pos初始化为输入行的第一个位置(pos=1)。如果遇到的是其他字符，程序将把它打印出来并递增变量pos的值(++pos)。

    */
