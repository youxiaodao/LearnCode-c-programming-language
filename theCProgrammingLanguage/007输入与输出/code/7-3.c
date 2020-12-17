// 改写minprintf， 使其能完成printf函数的更多功能

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT    100

// minimal printf with variable argument list
void minprintf(char *fmt, ...) {
    va_list ap;     // points to each unnamed arg
    char *p, *sval;
    char localfmt[LOCALFMT];
    int i, ival;
    unsigned uval;
    double dval;

    va_start(ap, fmt);  // make ap point to 1st unnamed arg
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        i = 0;
        localfmt[i++] == '%';   // start local fmt
        while (*(p + 1) && !isalpha(*(p + 1))) {
            localfmt[i++] = *++p;   //collect chars
        }
        localfmt[i++] = *(p + 1);   // format letter
        localfmt[i] = '\0';
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf(localfmt, ival);
            break;
        case 'x':
        case 'X':
        case 'u':
        case 'o':
            uval = va_arg(ap, unsigned);
            printf(localfmt, ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf(localfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            printf(localfmt, sval);
            break;
        default:
            printf(localfmt);
            break;
        }
    }
    va_end(ap);         // clean up
}

/*
    首先对自己的输入参数表加以分析, 然后调用printf来完成具体的打印输出功能

    为了更多的实现一些printf函数的功能,我们使用了一个字符数组localfmt来保存从minprintf函数的输入参数表中分析出来的 % 字符和其它字符,
    直到遇到一个字母字符 (即输出格式控制字符) 为止， 最终得到的localfmt将被用作printf的格式参数

*/