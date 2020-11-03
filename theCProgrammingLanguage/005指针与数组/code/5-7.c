// 重写函数readlines, 将输入的文本行存储到有main函数提供的一个数组中, 
//  而不是存储到调用alloc分配的存储空间中。
// 该函数的运行速度比改写前快多少?
#include <string.h>
#define MAXLEN  1000    // maximum length of line
#define MAXSTOR 5000    // size of availavle storage space

int getline (char *, int);

int readlines(char *lineptr[], char *linestor, int maxlines) {
    int len, nlines;
    char line[MAXLEN];

    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestop) { 
            return -1;
        } else {
            line[len - 1] = '\0';   // delete new line
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}


// 输入行保存在 linestor中
// p+len>linestop 替代了原来的 p = alloc(len) == NULL
