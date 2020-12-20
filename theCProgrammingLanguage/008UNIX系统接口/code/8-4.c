/* 
    标准库函数 int fseek(FILE *fp, long offset, int origin)
    类似于函数lseek, 所不同的是，该函数中的fp是一个文件指针, 而不是文件描述符
    且返回值是一个int类型的状态, 而非位置值
    编写fseek,并确保该函数与库中其它函数使用的缓冲能够协同工作
*/

#include "syscalls.h"
// seek with a file pointer
int fseek(FILE *fp, ling offset, int origin) {
    unsigned nc;        // # of chars to flush
    long rc = 0;        return code

    if (fp->flag & _READ) {
        if (origin == 1) {          // from current
            offset -= fp->cnt;      // remember chars in buffer
        }
        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0;                // no characters buffered
    } else if (fp->flag & _WRITE) {
        if ((nc = fp->ptr - fp->base) > 0) {
            if (write(fp->fd, fp->base, nc) != nc) {
                rc = -1;
            }
        }
        if (rc != -1) {         // no errors yet?
            rc = lseek(fp->fd, offset, origin);
        }
    }
    return (rc == -1) ? -1 : 0;
}

/*
    变量rc中保存着返回代码；如果执行出错，就把它设置为-1
    fseek需要对两种情况做出处理：
        一是文件为读操作而打开
        二是文件为写操作而打开
    如果文件时为读操作而打开且origin等于1，偏移量offset将从当前位置开始计算
        其它情况时： 如果origin == 0， 偏移量offset将从文件头位置开始计算；如果origin == 1, 偏移量offset将从文件尾开始计算
    为了计算出从当前位置算起的偏移量，fseek必须把自己已经被读入到缓冲区中的那些字符也考虑进去
        if (origin == 1) {
            offset -= fp->cnt;
        }
    然后，fseek调用lseek完成相应的功能，并丢弃缓冲区中的字符 ;
        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0
    如果文件时为写操作而打开的，fseek必须先把缓冲区中的字符全部写入文件：
        if ((nc = fp->ptr - fp->base) > 0) {
            if (write(fp->fd, fp->base, nc) != nc) {
                rc = -1
            }
        }
    如果直到现在还没有出错, fseek就调用lseek,如下所示
        if (rc != -1) {
            rc = lseek(fp->fd, offset, origin)
        }
    如果执行成功, 函数fseek将返回0
*/