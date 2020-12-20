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

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
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