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

/* fold long input lines into two or more shorter lines */
void main() {
    int c, pos;

    pos = 0;        // postition in the line
    while ((c=getchar()) != EOF) {
        line[pos] = c;      // store current character
        if (c == '\t') {    // expand tab character
            pos = exptab(pos);
        } else if (c == '\n'){
            printl(pos);        // print current input line
            pos = 0;
        } else if (++pos >= MAXCOL) {
            pos = findblnk(pos);
            printl(pos);
            pos = newpos(pos);
        }
    }
}

/* printl: print line until pos column */
void printl(int pos) {
    int i;
    for (i=0; i<pos; ++i) {
        putchar(line[i]);
    }
    if (pos>0){     // any chars printed?
        putchar('\n');
    }
}

/* exptab: find blank`s position */
int exptab(int pos) {
    line[pos] = ' ';        /* tab is at least one blank */
    for (++pos; pos < MAXCOL && pos % TABINC != 0; ++pos) {
        line[pos] = ' ';    
    }
    if (pos < MAXCOL) {     // room left in current line
        return pos;
    } else {            // current line is full
        printl(pos);
        return 0;       // reset current position
    }
}
/* findblnk: find blank`s position */
int findblnk(int pos) {
    while (pos > 0 && line[pos] != ' ') {
        --pos;
    }
    if (pos == 0) {         // no blanks in the line?
        return MAXCOL;      // 
    } else {                // at least one blank
        return pos + 1;     // position after the blank
    }
}

/* newpos: rearrange line with new position */
int newpos(int pos) {
    int i,j;
    if (pos <= 0 || pos>=MAXCOL) {
        return 0;       // nothing to rearrange
    } else {
        i = 0;
        for (j = pos; j < MAXCOL; ++j) {
            line[i] = line[j];
            ++i;
        }
        return i;       // new position in line
    }
}

/*  MAXCOL 是一个符号常量，它给出了输入行的折行位置，即输入行的第n列。
    整型变量pos是程序再文本行中的当前位置。

    程序将在输入行的每一处的第n列之前对该输入行折行.
    这个程序将把制表符扩展为空格；每遇到一个换行符就把此前输入的文本打印出来
    每当变量pos的值达到MAXCOL时，就会对输入行进行折叠
    函数findblnk从输入行的pos处开始倒退着寻找一个空格(目前时保持折行位置的单词的完整)。
    如果找到了一个空格符，它就返回紧跟在该空格符后面的那个位置的下标
    如果没有找到空格，他就返回MAXCOL
    函数printl打印输出从位置零到位置pos-1之间的字符
    函数newpos调整输入行，它将把从位置pos开始的字符复制到下一个输出行的开始，然后再返回变量pos的新值 */