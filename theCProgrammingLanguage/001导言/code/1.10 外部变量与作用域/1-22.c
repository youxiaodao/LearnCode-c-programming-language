// 把较长的输入行 “折” 成短一些的两行或者多行，
// 折行的位置在输入行的第n列之前的最后一个非空格之后
// 要保证程序能够智能地处理输入行很长以及在指定的列前
// 没有空格或者制表符的情况
#include <stdio.h>

#define MAXCOL 10       // maximum column of input
#define TABINC 8        // tab increment size

char line[MAXCOL];      // input line

int exptab(int pos);
int findblnk(int pos);
int newpos(int pos);
void printl(int pos);

void main() {
    int c, pos;
    while ((c=getchar()) != EOF) {
        line[pos] = c;
        if (c == '\t') {
            pos = exptab(pos);
        } else if (c == '\n'){
            printl(pos);
            pos = 0;
        } else if (++pos >= MAXCOL) {
            pos = findblnk(pos);
            printl(pos);
            pos = newpos(pos);
        }
    }
}

void printl(int pos) {
    int i;
    for (i=0; i<pos; ++i) {
        putchar(line[i]);
    }
    if (pos>0){
        putchar('\n');
    }
}

int exptab(int pos) {
    line[pos] = ' ';
    for (++pos; pos < MAXCOL && pos % TABINC != 0; ++pos) {
        line[pos] = ' ';
    }
}