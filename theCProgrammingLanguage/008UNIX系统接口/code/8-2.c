
#include <fcntl.h>
#include "syscalls.h"
#define PERMS   6666        // RW for owner, group, others

struct flag_filed {
    unsigned is_read    : 1;
    unsigned is_write   : 1;
    unsigned is_unbuf   : 1;
    unsigned is_buf     : 1;
    unsigned is_eof     : 1;
    unsigned is_err     : 1;
}
// open file, reutrn file ptr
FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r', && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flag.is_read == 0 && fp->flag.is_write == 0) {
            break;      // found free slot
        }
    }
    if (fp >= _iob + OPEN_MAX)
        return NULL;    // no free slots

    if (*mode == 'w') {     // create file
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.is_unbuf = 0;
    fp->flag.is_buf = 1;
    fp->flag.is_eof = 0;
    fp->flag.is_err = 0;
    if (*mode == 'r') {     // read
        fp->flag.is_read = 1;
        fp->flag.is_write = 0;
    } else {
        fp->flag.is_read = 0;
        fp->flag.is_write = 1;
    }
    return fp;
}
// allocate and fill input buffer
int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flag.is_read == 0 || fp->flag.is_eof == 1 || fp->flag.is_err == 1)
        return EOF;
    bufsize = (fp->flag.is_unfuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL)       // no buffer yet
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            return EOF;     //can't get buffer
        }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->vnt < 0) {
        if (fp->cnt == -1) {
            fp->flag.is_eof = 1;
        } else {
            fp ->flag.is_err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}


/*
结构struct _iobuf的类型定义(即typedef)见 原著page176, _iobuf有一个成员变量是int flag;
按照题目要求, 我们对变量flag按位字符的方式重新进行了定义, 如下所示
    struct flag_filed {
        写在上面
    }
在原来的fopen函数中, 有下面的if语句
    if ((fp->flag & (_RED | _WRITE)) == 0)
        break;
这条语句对 _READ 和 _WRITE标志进行了OR操作, 如下所示：
    (_READ   |    _WRITE)
        01   |      02      八进制
        01   |      10      二进制
            11              运算结果

    惑
*/