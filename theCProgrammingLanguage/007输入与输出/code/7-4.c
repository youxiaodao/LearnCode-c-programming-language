// 类似于上一节中的函数minprintf，编写scanf函数的一个简化版本

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT    100

// minimal scanf with variable argument
void minscanf(char *fmt, ...) {
    va_list ap;     //points to each unnamed arg
    char *p, *sval;
    char localfmt[LOCALFMT];

    int c, i, *ival;
    unsigned *uval;
    double *dval;

    i = 0;      // index for localfmt array
    va_start(ap, fmt);   // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            localfmt[i++] = *p; // collect chars
            continue;
        }
        localfmt[i++] = '%';    // start format
        while (*(p+1) && !isalpha(*(p+1))) {
            localfmt[i++] = *++p;   //collect chars
        }
        localfmt[i++] = *(p + 1); //collect chars
        localfmt[i] = '\0';
        switch(*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int *);
                scanf(localfmt, ival);
                break;
            case 'x':
            case 'X':
            case 'u':
            case 'o':
                uval = va_arg(ap, unsigned *);
                scanf(localfmt, uval);
                break;
            case 'f':
                dval = va_arg(ap, double *);
                scanf(localfmt, dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf(localfmt, sval);
            default:
                scanf(localfmt);
                break;
        }
        i = 0;
    }
    va_end(ap);
}

// 在输入的格式字符串进行收集直到 在%找到一个字母字符, 然后再把字符数组localfmt 和有关指针传递给scanf函数
// scanf函数的所有参数必须是指针
    // 一个指向格式字符串
    // 另一个指针则指向用于接收scanf输入值的变量
    // 我们先通过va_arg函数得到指针的值, 再把它复制为一个局部指针，
    // 最后通过调用scanf把输入值读到用户指定的变量中去
    