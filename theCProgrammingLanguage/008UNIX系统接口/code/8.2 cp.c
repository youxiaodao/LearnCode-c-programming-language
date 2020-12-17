// 只能复制一个文件
// 不能用目录作为第二参数
// 目标文件的权限是重新定义的，不是通过复制获得的

#include <stdio.h>
#include <fcntl.h>
#include "syscalls.h"
#define PERMS   0666

void error(char *, ...);

// cp:将f1复制到f2
int main(int argc, char const *argv[])
{
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3) {
        error("Usage: cp from to");
    }
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1) {
        error("cp: can't open %s", argv[1]);
    }
    if ((f2 = creat(argv[2], PERMS)) == -1) {
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    }
    while ((n = read(f1, buf, BUFSIZ)) > 0) {
        if (write(f2, buf, n) != n) {
            error("cp: write error on file %s", argv[2]);
        }
    }
    return 0;
}

// 该程序创建的是固定权限的程序, 利用8.6节中的stat系统调用,可以获得一个已存在文件的模式，并将次模式赋值给它的副本
// 函数error类似于函数printf,在调用时可带变长参数表
// 通过error函数的实现说明如何使用printf函数家族函数的另一个长远vprintf
#include <stdio.h>
#include <stdarg.h>

// 打印一个出错信息，然后终止
void error(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
