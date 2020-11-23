// 增加 -d 代表目录顺序, 该选项表明只对字母，数字，和空格进行比较，要保证该选项可以和 -f 组合在一起使用
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define     NUMERIC 1   // numeric sort
#define     DECR    2   // SORT IN decreasing order
#define     FOLD    4   // fold upper and lower cases
#define     DIR     8   // directory order
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
            case 'd':
                option |= DIR;  // directory order
                break;
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
        printf("Usage: sort -dfnr \n");
    } else {
        if((nlines = readlines(lineptr, LINES)) > 0) {
            if (option & NUMERIC) {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            //} else if (option & FOLD) {
                //qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
            } else {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
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
    char a,b;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DIR) ? 1 : 0;

    do {
        if (dir) {
            while (!isalnum(*s) && *s != ' ' && *s != '\0') {
                s++;
            }
            while (!isalnum(*t) && *t != ' ' && *t != '\0') {
                t++;
            }
        }
        a = fold ? tolower(*s) : *s;
        s++;
        b = fold ? tolower(*t) : *t;
        t++;
        if (a == b && a == '\0') {
            return 0;
        }
    } while (a == b);
    return a - b;
}

/*
解题思路来源于5-14 和 5-15
第3位      = 0 不按目录顺序排序
            = 1 按(-d)

如果用户在命令行上给出了 -f选项, 变量option的第2位讲讲被下面这条语句设置为1
    option |= FOLD
FOLD 十进制数字4    二进制 00000100 二进制从左到右顺序被遍为 第0， 1，2，3，4

我们对5-15的charcmp进行了修改，使他能够同时处理-f 和-d 选项
如果用户给了-d 程序就会执行到下面的while循环
while ()
函数charcmp和strcmp很相似, 它们都是用来对字符串进行比较的，但为了支持FOLD选项，charcmp会先把字符串转换为小写形式后再对它们进行比较
            while (!isalnum(*s) && *s != ' ' && *s != '\0') {
                s++;
            }
将依次检查字符串s的各个字符， 并跳过不是字母，数字 和 空格的字符，
宏isalnum是在头文件 <ctype.h>中定义的，它的作用是检查某个字符是不是一个字符(a - z A - Z) 或者 数字(0-9)
如果*s是一个字母或者数字
    isalnum(*s) 就是一个非负值
    否则, isalnum(*s) 将等于0
紧接着, 执行
            while (!isalnum(*t) && *t != ' ' && *t != '\0') {
                t++;
            }
将依次检查t的各个字符,并并跳过不是字母，数字 和 空格的字符，

接下来， charcmp函数将把 “在字符串s中找到的字母，数字或者空格” 与 “在字符串t中找到的字母，数字或者空格” 逐个进行比较

本题的另一个解题思路是用3个专门的函数来代替charcmp
这3个专用函数的执行速度要比这一个快，
我们的选择是逐步增加charcmp函数的复杂度 而不是编写那么多个专用的函数
*/
