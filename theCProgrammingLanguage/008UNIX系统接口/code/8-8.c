// 编写函数 bfree(p, n), 释放一个包含n个字符的任意块p
// 并将它放入由malloc和free维护的空间块链表中.
// 通过使用bfree，用户可以在任意时刻向空闲块链表中添加一个静态或外部数组
#include "syscalls.h"

// free an arbitrary block p of n chars
unsigned bfree(char *p, unsigned n) {
    Header *hp;
    if (n < sizeof(Header)) {
        return 0;       // too small to be useful
    }
    hp = (Header *) p;
    hp->s.size = n / sizeof(Header);
    free((void *)(hp + 1));         // hp是一个指针，为什么要 + 1
    return hp->s.size;
}

/*
    bree 函数由两个参数, 一个指向起始位置的指针p, 和一个给出字符个数的数值n
    如果想调用bfree把某个内存块释放到空闲区列表，则这个内存块的长度至少要等于sizeof(Header), 否则，返回值为0

    先把指针p转换为Header类型，再把它赋值给hp
        hp = (Header *) p;
    以sizeof(Header)为单位计算的内存块长度值是：
        hp->s.size = n/sizeof(Header);
    最后， 调用函数free来释放那个内存块，free函数的输入参数是一个指针，
    而它指向的位置要求刚好越过内存块的头部区域--就像练习8-7中的morecore函数中做的那样，并且还要把它转换为void * 类型

    如果内存块的长度太小， bfree函数将返回0
    否则, 它返回一个以sizeof(Header)为单位计算的内存块的长度值
*/
