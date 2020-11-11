/*
编写 tail, 将其输入中的最后n行打印出来
默认情况下, n的值为10, 但可以通过一个可选参数改变n的值,
因此， 命令 tail -n
将打印其输入的最后n行，无论输入或n的值是否合理，该程序都应该能正常运行，
编写的程序要充分利用存储空间，输入行的存储方式应该同5.6节中排序程序存储方式一样，而不采用固定长度的二维数组
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFLINES    10  // default # of lines to print
#define LINES       100 // max # of lines to print
#define MAXLEN      100 // MAX length of an input line


void error(char *);
int getline(char *, int);

//print last n lines of the input
int main(int argc, char const *argv[]) {
    char *p;
    char *buf;              // pointer to larger buffer
    char *bufend;           // end of the buffer
    char line[MAXLEN];      // current input line
    char *lineptr[LINES];   // pointers to lines read
    int first, i, last, len, n, nlines;

    if (argc == 1) {    //no argument present
        n = DEFLINES;
    } else if (argc == 2 && (*++argv)[0] == '-') {
        n = atoi(argv[0] + 1);
    } else {
        error ("usage: tail [-n]");
    }

    if (n < 1 || n > LINES){ // unreasonable value for n?
        n = LINES;
    }
    for (i = 0; i < LINES; i++) {
        lineptr[i] = NULL;
    }
    if ((p = buf = malloc(LINES * MAXLEN)) == NULL) {
        error("tail: cannot allocate buf");
    }
    bufend = buf + LINES * MAXLEN;
    last = 0;
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (p + len + 1 >= bufend) {
            p = buf;
        }
        lineptr[last] = p;
        strcpy(lineptr[last], line);
        if (++last >= LINES) {
            last = 0;
        }
        p += len + 1;
        nlines++;
    }
    if (n > nlines) {
        n = nlines;
    }
    first = last -n;
    if (first < 0) {
        first += LINES;
    }
    for (i = first; n-- > 0; i = (i + 1) % LINES) {
        printf("%s", lineptr[i]);
    }
    return 0;
}


// error: print error message and exit
void error(char *s) {
    printf("%s\n", s);
    exit(1);
}

/*
    这个程序将把其输入中的最后n行打印出来（但最多打印LINES行）。 如果argc等于1（即没有命令行参数），
    n将默认地取值为DEFLIINES;
    如果argc等于2（即有一个命令行参数），n地取值就将来自于那个命令行参数
    如果argc大于2，则程序出错

    循环
    while ((len = getline(line, MAXLEN)) > 0)

    每次读入一个输入行，直到函数getline(参见1-16)读到最后一个输入行为止。
    这个陈序将使用预先分配号地缓存区空间来存放每次读入地输入行

    当缓存区没有足够的空间来寻访当前输入行时， 语句
    if (p + len + 1 >= bufend)
        p = buf;
    将把指针p重新设置为指向缓冲区空间地开头

    指针数组lineptr中地各个元素将依次指向最后读入地LINES个输入行各自得第一个字符
    我们把这个数组得索引值保存在变量last中

    变量last得初值是0， 当last等于LINES（即已经读入了LINES个输入行）时，就需要将其重新设置为0.
    也就是说我们将开始循环使用数组lineptr得元素及其缓冲区

    变量nlines保存着当前已被读入得输入行总数。因此
    if (n > nlines)
        n = nlines;

    当输入行得总数超过了LINES, last将 被重新设置为0， 还需要调整起始索引
    if (first < 0)
        first += LINES;
    最后这个程序将通过以下语句把它得最后n个输入行打印出来
    for (i = first; n-- > 0; i = (i + 1) % LINES)
        printf("%s", lineptr[i]);
    因为i 从初值first 开始递增n次，那么，当i大于LINES时, 就会出现某些输入行被反复打印多次的情况
    为了避免出现这种这一局面，我们使用取模运算符(%) 来确保i的取值范围能够落在 0 到LINES - 1 之间， 如下所示：
        i = (i + 1) % LINES
    标准库函数exit(参见 《C程序设计语言(第二版.新版)》 143页) 将在tail程序执行出错时终止它的运行, 此时exit将返回1
*/
















