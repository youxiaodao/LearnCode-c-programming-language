#define ALLOCSIZE   10000   // 可用空间大小

static char allocbuf[ALLOCSIZE];    // alloc 使用的存储区
static char *allocp = allocbuf;     // 下一个空闲位置

char *alloc(int n) {    // 返回指向n个字符的指针
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return alloc - n;   // 分配前的指针p
    } else {
        return 0;   // 空闲空间不够, 返回0
    }
} 

void afree(char *p) {   // 释放p指向的存储区
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}