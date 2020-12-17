// 编写函数，它将从由lookup 和 install维护的表中删除一个变量名及其定义
#include <stdio.h>

#define HASHSIZE    101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s);

// remove a name and definition from the table
void undef(char *s) {
    int h;
    struct nlist *prev, *np;

    prev = NULL;
    h = hash(s);        // hash value of strings
    for (np = hashtab[h]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {         // 查找s, 找到之后就跳出
            break;
        }
        prev = np;      // remember previous entry
    }
    if (np != NULL) {       // found name
        if (prev == NULL) {         // first in the hash list?
            hashtab[h] = np->next;
        } else {                    // elsewhere in the hash list
            prev->next = np->next;
        }
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);          // free allocated structure
    }
}

// 如果s不在表中， np将变成NULL时终止
// 指针数组hashtab中的各个元素分别指向一个链表的开头
// 如果指针np不为NULL，就说明其所指向的那个表中存在一组符合清除要求的变量名和定义
// 此时，指针np指向将被清除的那个数据项
// 而指针prev则指向出现在np位置之前的那个数据项
// 如果prev是NULL，就说明np是以hashtab[h]开头的那个链表的第一个元素