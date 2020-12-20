// 标准库函数calloc(n, size) 返回一个指针，它指向n个长度为size的对象
// 且所有分配的存储空间都被初始化为0
// 通过调用或修改malloc函数来实现calloc函数
#include "syscalls.h"
// allocate n objects of size size
void *calloc(unsigned n, unsigned size) {
    unsigned i, nb;
    char *p, *q;

    nb = n * size;
    if ((p = q = malloc(nb)) != NULL) {
        for (i = 0; i < nb; i++) {
            *p++ = 0;
        }
    }
    return q;
}

/*
    函数calloc为长度使size的n个对象分配存储空间, 
    我们把需要分配的字节总数计算并保存在变量nb中
        nb = n * size
    malloc 将返回一个指针， 该指针指向一个长度为nb个字节的内存块，这个内存块的起始位置将被保存在指针p和q中, 
    如果内存分配操作执行成功，我们就用下面的语句把分配到的nb个字节全部初始化为0

   calloc函数将返回一个指针, 指针指向它申请到的内存块的起始位置
   同时把这块内存区域全部初始化为0

   
*/