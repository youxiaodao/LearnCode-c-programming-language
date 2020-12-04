
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
// #define NKEYS 1000

// NKEYS 代表keytab中关键字的个数
    // 尽管可以手工计算，但由机器实现回更简单，更安全
    // 当列表可能变更时， 尤其如此
    // 一种解决办法是, 在初值结尾处加上一个空指针, 然后遍历keytab， 
    // 实际上, 我们不需要这样做, 因为数组的长度在编译时已经完全确定，它等于数组项的长度乘以项数
        // 可以得出项数为 keytab的长度 / struct key的长度 

// # define NKEYS (sizeof keytab / sizeof(struct key))

// 使用下面的， 即使类型改变了, 也不用改动程序。 使用数组的长度 除以 一个指定元素的长度
# define NKEYS (sizeof keytab / sizeof keytab[0])

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
int binsearch(char *, struct key *, int);


// 统计输入中c语言关键字的出现次数
int main(int argc, char const *argv[])
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

// binsearch 函数: 在tab[0] 到 tab[n-1]中查找单词
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if ( cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

// 一个更通用的getword：从输入中读取下一个单词或者字符
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}


