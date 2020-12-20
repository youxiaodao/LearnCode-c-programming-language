// 修改fsize程序，打印i节点项中包含的其它信息

#include <stdio.h>
#include <string.h>
#include <fcntl.h>          // flags for read and write
#include <sys/types.h>      // typedefs
#include <sys/stat.h>       // structure returned by stat
#include "dirent.h"

int stat(char *, struct stat *);
// print inode #, mode, links, size of file "name"
void fsize(char *name) {
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("%5u %6o %3u %8ld %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_size, name);
}

/*
    修改后的fsize程序将打印以下信息:
        i结点编号
        以八进制表示的文件模式
        文件的链接个数
        文件长度以及文件名
    你还可以选择打印更多的信息
    其中函数dirwalk是 K&R原著第182页上介绍的函数
*/
