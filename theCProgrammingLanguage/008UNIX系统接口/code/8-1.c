// 用read, write, open, close 系统调用代替标准库中功能等价的函数，重写第7章的cat程序，并通过实验比较两个版本的相对执行速度

#include <stdio.h>
#include <fcntl.h>
#include "syscalls.h"

void error(char *fmt, ...);

// concatenate files -read / write / open / close
int main(int argc, char const *argv[])
{
    int fd;
    void filecopy(int ifd, int ofd);

    if (argc == 1) {        // no args ;copy standard inpur
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                error("cat: cant't open %s", *argv);
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    return 0;
}

// copy file ifd to  file ofd
void filecopy(int ifd, int ofd) {
    int n;
    char buf[BUFSIZ];

    while ((n = read(ifd, buf, BUFSIZ)) > 0) {
        if (write(ofd, buf, n) != n) {
            error("cat: write error");
        }
    }
}

