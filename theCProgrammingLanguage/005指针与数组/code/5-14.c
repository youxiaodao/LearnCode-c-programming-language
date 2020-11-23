// 修改排序程序， 使它能处理 -r 标记。该标记表明，以逆序(递增) 方式排序。
// 要保证 -r 和 -n 能够组合在一起使用

#include <stdio.h>
#include <string.h>

#define NUMERIC 1   // numeric sort
#define DECR    2   // sort in decreasing order
#define LINES   100 // max # of lines to be sorted

int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void qsort(char *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int decr);

static char option = 0;

// sort input lines
int main(int argc, char const *argv[]) {
    char *lineptr[LINES];   // pointers to text lines
    int nlines;             // number of input lines read
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':   // numeric sort
                    option |= NUMERIC;
                    break;
                case 'r':
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
        printf("Usage: sort -nr /n");
    } else {
        if ((nlines = readlines(lineptr, LINES)) > 0) {
            if (option & NUMERIC) {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            } else {
                qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
            }
            writelines(lineptr, nlines, option & DECR);
        } else {
            printf("input too big to sort \n");
            rc = -1;
        }
    }
    return 0;
}

// writerlines: write output lines
void weitelines(char *lineptr[], int nlines, int decr) {
    int i;
    if (decr) {
        for (i = nlines - 1; i >=0; i--) {
            printf("%s\n", lineptr[i]);
        }
    } else {
        for (i = 0; i < nlines; i++) {
            printf("%s\n", lineptr[i]);
        }
    }
}

/*

排序程序的具体功能有静态字符变量option的二进制位取值决定
第0位   = 0     对字符串排序
        = 1     对数字排序(-n)
第一位  = 0     按升序排序
        = 1     按降序(-r)

如果用户给了某个命令行选项, 按OR运算符(|) 将把变量option中与之对应的位设置为1
    option |= DECR
    等价于 option = option | DECR

we know 十进制数字2的二进制表示形式是   00000010
因为 1 or 0 和 1 or 1 的运算结果都是 1
所以上面这条C语句将把字符变量option的第一位设置为1 (二进制位按从左到右的顺序被编号为 第0, 1, 2, 3 ...位)

为了判断用户是否给出了某个命令行选项, 我们使用了按位AND(&)运算符
    option & DECR
如果用户给出了命令行选项 -r, 表达式将被求值为“真”;   如果用户没有给出命令行选项-r, 这个表达式就将被求值为“假”

我们对函数writelines 进行了修改, 使它能够对新增加的decr参数进行处理，
变量decr使表达式option&DECR的求值结果, 排序程序将根据这个变量来决定有关数据在排序后是按升序输出还是按降序输出


*/