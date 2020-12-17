#include "syscalls.h"

// 从pos位置处读入n个字符
int get(int fd, long pos, char *buf, int n) {
    if (lseek(fd, pos, 0) >= 0) {
        return read(fd, buf, n);    // 移动到pos
    } else {
        return -1;
    }
}

