
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
这意味着：只有当flag的两个最低为全部为0(不读也不写)时，这条if语句才会真
这条语句将核实这样一个情况：_iob中的某个元素没有被用来完成读或者写操作
在采用位字段的方案中，我们必须明确地对这一情况加以测试，如下所示
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (fp->flag.is_read == 0 && fp->flag.is_write == 0) {
            break;      // found free slot
接下来地修改之处是对位字段进行初始化部分，如下所示

    fp->flag.is_unbuf = 0;
    fp->flag.is_buf = 1;
    fp->flag.is_eof = 0;
    fp->flag.is_err = 0;
再往后，原来地fopen函数中有下面地语句
    fp->flag = (*mode == 'r) ? _READ : _WRITE;
其作用是根据mode地情况来设置flag:
    如果mode -r 就将其设置为_READ  
                        _WRITE
在采用位置段地方案中：
    如果mode是r, 把is_read位设置为1
                  is_write设置为1
如下所示

    if (*mode == 'r') {     // read
        fp->flag.is_read = 1;
        fp->flag.is_write = 0;
    } else {
        fp->flag.is_read = 0;
        fp->flag.is_write = 1;
    }
                        
我们对_fillbuf函数也做了类似地修改
首先，_fillbuf函数在遇到以下几个情况时, 将返回EOF
    1. 文件不是为了进行读操作打开
    2. 已经到文件末尾
    3. 检测到一个执行错误
下面是原来地 _fillbuf函数中用于检查这些条件地if语句
    if((fp->flag & (_READ|_EOF|_ERR)) != _READ)
我们把它修改为条件判断语句

    if (fp->flag.is_read == 0 || fp->flag.is_eof == 1 || fp->flag.is_err == 1)
        return EOF;
接着， 我们还需要把原来地 _fillbuf函数中地语句

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
修改为
   
    bufsize = (fp->flag.is_unfuf == 1) ? 1 : BUFSIZ;
把原来地  _fillbuf函数中地语句
        fp->flag |= _EOF;
    else
        fp->flag |= _ERR;
修改为
        fp->flag.is_eof = 1;
    else
        fp->flag.is_err = 1;
新方案地代码规模增加了不少，函数地执行速度也变慢了
位字段操作不仅要依赖计算机硬件，还会降低执行速度
*/