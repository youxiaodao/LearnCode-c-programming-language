// 重新编写关键字统计程序, 这次采用指针，而不是数组下标
// 修改main 和binsearch

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
      "auto", 0,
      "break", 0,
      "case", 0,
      /*...*/
};

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);


// 统计输入中c语言关键字的出现次数
int main(int argc, char const *argv[])
{
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((p = binsearch(word, keytab, NKEYS)) != NULL) {
                p->count++;
            }
        }
    }
    // p 是key对象的指针， 数组名可以直接代表数组第一个元素的指针，所以可以这样写
    for (p = keytab; p < keytab + NKEYS; p++) {     // 如果p是指向结构的指针, 对p的的算术运算需要考虑结构的长度
        if (p->count > 0) {
            printf("%4d %s\n", p->count, p->word);
        }
    }
    return 0;
}

// binsearch 函数: 在tab[0] 到 tab[n-1]中查找单词
struct key *binsearch(char *word, struct key tab[], int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0) {
            high = mid;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;
}
