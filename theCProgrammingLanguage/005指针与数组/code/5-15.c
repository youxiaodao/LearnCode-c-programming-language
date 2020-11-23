// 增加选项f 使得排序过程不考虑字母大小写之间的区别
// 例如，比较a和A时认为它们相等

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define     NUMERIC 1   // numeric sort
#define     DECR    2   // SORT IN decreasing order
#define     FOLD    4   // fold upper and lower cases
#define     LINES   100 // MAX # of lines to be sorted

int charcmp(char *, char *);
int numcmp(char *, char *);

int readines(char *lineptr[], int malines);
void qsort(char *v[], int left, int right, int (*comp)(void *, void *));
void writerlines(char *lineptr[], int nlines, int order);
static char option = 0;

// sort input lines
int main(int argc, char const *argv[]) {
    char *lineptr[LINES];   // pointers to text lines
    int nlines;
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
            case 'f':
                option |= FOLD; //FOLD upper and lower cases
                break;
            case 'n':   // numeric sort
                option |= NUMERIC;  
                break;
            case 'r':   // // sort in decreasing order
                option |= DECR;  
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 1;
                rc = -1;
                break;
            }
        }
    }
    if (argc) {
        printf("Usage: sort -fnr \n");
    } else {
        if((nlines = readlines(lineptr, LINES)) > 0) {
            if (option & NUMERIC) {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            } else if (option & FOLD) {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
            } else {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) strcmp);
            }
            writerlines(lineptr, nlines, option & DECR);
        } else {
            printf("input too big to sort \n");
                rc = -1;
        }
    }

    return rc;
}
// charcmp return < 0 if s<t, 0 if s== t, >0 if s>t
int charcmp(char *s, char *t) {
    for ( ; tolower(*s) == tolower(*t); s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    return tolower(*s) - tolower(*t);
}
/*
解题思路来源于5-14
第二位      = 0 区分字母的大小写
            = 1 不区分(-f)

如果用户在命令行上给出了 -f选项, 变量option的第2位讲讲被下面这条语句设置为1
    option |= FOLD
FOLD 十进制数字4    二进制 00000100 二进制从左到右顺序被遍为 第0， 1，2，3，4

函数charcmp和strcmp很相似, 它们都是用来对字符串进行比较的，但为了支持FOLD选项，charcmp会先把字符串转换为小写形式后再对它们进行比较

*/
