// 编写entab, 将空格替换为最少数量的制表符和空格，
// 但要保持单词之间的间隔不变，
// 假设制表符终止位的位置与练习1-20的detab的情况相同
// 当使用一个制表符或者一个空格都可以达到下一个制表符终止位时
// 选用哪种替换字符比较好？
#include <stdio.h>
#define TABINC 8  // TAB increment size


void main() {
    int c, nb, nt, pos;
    nb=0;    // number of blanks necessary
    nt=0;   // number of tabs necessary
    for (pos=1;(c=getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (pos % TABINC != 0) {
                ++nb;   // increment number of blanks
            } else {
                nb = 0;     // reset number of blanks
                ++nt;       // one more tab
            }
        } else {
            for ( ; nt>0;--nt) {
                putchar('\t');      // output tab(s)
            }
            if (c == '\t') {    //forget the blank(s)
                nb = 0;
            } else {        // output blank(s)
                for ( ; nb > 0; --nb) {
                    putchar(' ');
                }
            }
            putchar(c);
            if (c=='\n'){
                pos = 0;
            } else if ( c == '\n') {
                pos = pos + (TABINC - (pos - 1) % TABINC) - 1;
            }
        }
    }
}

/* 整型变量nb和nt分别用来替换空格和制表符的最少个数，变量pos是程序在文本行中的当前位置
    程序的主要想法是找出全部空格。变量pos每递增到TABINC的一个倍数的时候，我们就把空格替换为一个制表符
    当遇到非空格时，程序将先把遇到的这个字符之前累计的制表符和空格打印出来，
    再把这个字符打印出来，然后，程序将把变量nb和nt打印出来，然后将nb和nt重新设置为零，
    如果当前字符时一个换行符，还要把变量pos重新设置为输入行的开始

    当遇到一个制表符时，程序将只把此前积累的制表符和当前遇到的这个制表符打印出来。
    如果只需要一个空格就能到达下一个制表符终止位，我们选择时把它替换成一个制表符，因为这有助于避免特殊情况。
    */
