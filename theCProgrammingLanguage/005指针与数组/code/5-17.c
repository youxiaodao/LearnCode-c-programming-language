/*
    增加字段处理功能， 以使得排序程序可以根据行内的不同字段进行排序
    每个字段按照一个单独的选项集合进行排序
    在对英文原书索引进行排序时，索引条目使用了 -df选项
    而对页码排序时使用了 -n选项
*/

#include <stdio.h>
#include <ctype.h>

#define NUMRIC  1       // numeric sort
#define DECR    2       // SORT In decreasing order
#define FOLD    4       // fold supper and lower cases
#define DIR     8       // directory order
#define LINES   100     // MAX # of lines to be sorted

int charcmp(char *, char *);
void error(char *);
int numcmp(char *, char *);
void readargs(int argc, char *argv[]);
int readlines(char *lineptr[], int mnaxlines);
void qsort(char *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int order);

char option = 0;
int pos1 = 0;       // firld beginning with pos1
int pos2 = 0;       // ending just before pos2

// sort input lines
int main(int argc, char const *argv[]) {

    char *lineptr[LINES];       // pointers to text lines
    int nlines;
    int rc = 0;

    readargs(argc, argv);
    if ((nlines = readlines(lineptr, LINES)) > 0) {
        if (option & NUMRIC) {
            qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
        } else {
            qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
        }
        writelines(lineptr, nlines, option & DECR);
    } else {
        ptintf("input too big go sort \n");
        rc = -1;
    }
    return rc;
}

// read program arguments
void readargs(int argc, char *argv[]) {
    int c;
    int atoi(char *);

    while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
        if (c == '-' && !isdigit(*(argv[0] + 1))) {
            while (c = *++argv[0]) {
                switch (c) {
                case 'd':       // DIRECTORY order
                    option |= DIR;
                    break;
                case 'f':       // fold upper and lower
                    option |= FOLD;
                    break;
                case 'n':       // numeric sort
                    option |= NUMRIC;
                    break;
                case 'r':       // sort in decr order
                    option |= DECR;   
                default:
                    printf("sort: illegal option %c\n", c);
                    error("Usage: sort -dfnr [+pos1] [-pos2]");
                    break;
                }
            }
        } else if (c == '-') {
            pos2 = atoi(argv[0] + 1);
        } else if ((pos1 = atoi(argv[0] + 1)) < 0) {
            error("Usage: sort -dfnr [+pos1] [-pos2]");
        }
    }
    if (argc || pos1 > pos2) {
        error("Usage: sort -dfnr [+pos1] [-pos2]");
    }
}


// 源文件numcmp.c

#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAXSTR  100

void substr_(char *s, char *t, int maxstr);

// compare s1 and s2 numerically
int numcmp(char *s1, char *s2) {
    double v1, v2;
    char str[MAXSTR];

    substr_(s1, str, MAXSTR);
    v1 = atof(str);
    substr_(s2, str, MAXSTR);
    v2 = atof(str);
    if (v1 < v2) {
        return -1;
    } else (v1 > v2){
        return 1;
    } else {
        return 0
    }
}



#define FOLD    4   // Fold upper and lower cases
#define DIR     8   // directory order

// return <0    if s<t, 0 if s==t, >0 if s>t
int charcmp(char *s, char *t) {
    char a, b;
    int i, j, endpos;
    extern char option;
    extern int pos1, pos2;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & DIR) ? 1 : 0;

    i = j = pos1;
    if (pos2 > 0) {
        endpos = pos2;
    } else if ((endpos = strlen(s)) > strlen(t)) {
        endpos = strlen(t);
    }
    do {
        if (dir) {
            while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0') {
                i++;
            }
            while (j < endpos && !isalnum(s[j]) && s[j] != ' ' && s[j] != '\0') {
                j++;
            }
        }
        if (i < endpos && j < endpos) {
            a = fold ? tolower(s[i]) : s[i];
            i++;
            b = fold ? tolower(t[j]) : s[j];
            j++;
            if (a == b && a == '\0') {
                return 0;
            }
        }
    } while (a == b && i < endpos && j < endpos);
    return a - b;
}

// 源文件 substr.c
#include <string.h>

void error(char *);

//get a substring of s and put in str
void substr(char *s, char *str) {
    int i, j ,len;
    extern int pos1, pos2;

    len = strlen(s);
    if (pos2 > 0 && len > pos2) {
        len = pos2;
    } else if (pos2 > 0 && len < pos2) {
        error("substr: string too short");
    }
    for (j = 0, i = pos1; i < len; i++, j++) {
        str[j] = s[i];
    }
    str[j] = '\0';
}

// 本题的解题思路来自 5-14 5-15 5-16
// 排序命令的语法是:
/*
    sort -dfnr [+pos1] [-pos2]
*/
// 如果你想按照文本行中的某个字段进行排序，就需要给出pos1 pos2
// 排序程序将根据pos1 和pos2 之间的字符内容进行排序。如果pos1 和pos2等于0，就表示以整个文本行作为排序码
// 函数 readargs 负责分析排序程序命令行选项 
    // 当命令行带有选项，且前带有减号, readargs函数中的while循环的条件表达式将一直为真
    // 当命令行参数是一个以减号开始的非数字字符时，第一个if 语句 将为真
        // if (c == '-' && !isdigit(*(argv[0] + 1))) {

// 只有用户给出了可选参数-pos2时, 紧随其后的else-if语句
    // else if (t == '-') 才会为真

// 最后的else - if 语句负责处理+pos1参数, 并检查它是否大于0
// 函数charcmp是前面练习中的同名函数的改进版本，我们给他增加了字段处理功能
// 函数numcmp对数字进行比较, 它与前面练习中的同名函数差不多，但使用了一个新的substr函数
    // 因为排序字段的起始位置和长度不能用atof的输入参数
    // 我们不想改变atof函数的调用接口
    // 因为修改一个像atof这样常用的函数的调用接口往往会带来很多问题
    // 而增加一个新函数substr要比修改接口更安全
    // 函数swap qsort readlines writelines 与我们在 5- 14 时使用的函数完全一样
    // error 取之5-13