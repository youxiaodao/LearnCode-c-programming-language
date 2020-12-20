// 请设计并编写函数 _flushbuf / fflush /fclose
#include "syscalls.h"

// allocate and flush output buffer
int _flushbuf(int x, FILE *fp) {
    unsigned nc;        // # of chars to flush
    int bufsize;        // SIZE OF buffer alloc

    if (fp < _iob || fp >= _iob + OPEN_MAX) {
        return EOF;             
    }
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
        return EOF;             // error: incalid pointer
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {         // no buffer yet
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            fp->flag |= _ERR;
            return EOF;             // can't get buffer
        }
    } else {
        nc = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, nc) != nc) {
            fp->flag |= _ERR;
            return EOF;             // return EOF
        }
    }
    fp->ptr = fp->base;
    *fp-ptr++ = (char)x;
    fp->cnt = bufsize - 1;
    return x;
}

//close file
int fclose(FILE *fp) {
    int rc;             // return code
    if ((rc = fflush(fp)) != EOF) {     // anything to flush
        free(fp->base);
        fp->ptr = NULL;
        fp->cnt = 0;
        fp->base = NULL;
        FP->flag &= (_READ | _WRITE);
    }
    return rc
}

// flush buffer associated with file fp
int fflush(FLIE *fp) {
    int rc = 0;
    if (fp < _iob || fp >= _iob + OPEN_MAX)
        return EOF;     // error : invalid pointer
    if (fp->flag & _WRITER) {
        rc = _flushbuf(0, fp);
    }
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ
    return rc;
}

/*
    当文件不是为了写操作而打开的或者发生错误时, _flushbuf函数将返回一个EOF, 如下所示
        if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
            return EOF;             // error: incalid pointer
    如果此时还没有缓冲区，我们就将在_fillbuf函数里面那样(page 178)分配一个缓冲区:
        如果缓冲区已经存在, 我们就把它里面的字符全部清除(并写入相应文件)
    下一步是把输入参数保存到这个缓存区中
        *fp-ptr++ = (char)x;
    因为要给刚刚保存的字符(char)x留一个位置, 所以缓冲区能够容纳的字符个数(fp->cnt)将等于缓冲区的长度 - 1
    
    函数fclose需要调用fflush
    如果文件是为了写操作而打开的
    就需要把缓冲区的数据写入到有关文件中
    fclose将对_iobuf机构的各种成员变量进行重置,
        这是为了保证今后的fopen调用所分配到的_iobuf结构中不会有无意义的值
        如果操作成功, fclose的返回代码将是0

    fflush先检查文件指针是否合法。然后该文件是为了写操作而打开的, 就调用_flushbuf
        把缓冲区的数据全部写入文件，接下来，fflush重置ptr和cnt,再返回rc。
*/