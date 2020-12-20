// malloc 接收对存储空间的请求时, 并不检查请求长度的合理性, 
// 而free则认为被释放的块包含一个有效的长度字段，改进这些函数，使它们具有错误检查的功能
#include "syscalls.h"
#define MAXBYTES (unsigned) 10240

static unsigned maxlloc;    // max number of units allocated
static Header base;         // empty list to get started
static Header *freep = NULL //start of free list

// general-purpose storage allocator
void *malloc(unsigned nbytes) {
    Header *p, *prevp;
    static Header *morecore(unsigned);
    unsigned nunits;

    if (nbytes > MAXBYTES) {        // not nore than MAXBYTES
        fprintf(stderr, "alloc: can't allocate more than %u bytes\n", MAXBYTES);
        return NULL;
    }
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    /* ... */  // page 187 K&R
}

#define NALLOC  1024        // minumum  #units to request
// ask system for more memory
static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) - 1) {       // no space at all
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;
    maxalloc = (up->s.size > maxalloc) ? up->s.size : maxalloc;
    free((void *)(up + 1));
    return freep;
}

// put block ap in free list
void free(void *ap) {
    Header *bp, *p;
    bp = (Header *)ap - 1;   // point to block header

    if (bp->s.size == 0 || bp->s.size > maxalloc) {
        fprintf(stderr, "free: can't free %u units \n", bp->s.size);
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p=p->s.ptr)

        /* ... page 188 K&R */
}

/*
    malloc先检查用户申请分配的字节数是否大于常数MAXBYTES, 
    请根据系统的具体情况预先为MABYTES设置一个最合适的值
    函数morecore每分配一个新的内存块， 都会把截止到当时最大内存块的长度记录再静态变量maxalloc里面
    这样，free函数就能对释放的内存块的长度进行验证:
        这个长度值既不能等于0, 也不能大于当时已经分配的最大内存块的长度(maxalloc)

*/