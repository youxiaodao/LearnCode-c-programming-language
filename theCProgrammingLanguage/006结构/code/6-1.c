// 写更完善的getword，使其能够处理下划线, 字符串常量， 注释以及预处理器控制指令
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

char buf[BUFSIZE];
int bufp = 0;

struct key {
    char *word;
    int count;
};

int binsearch(char *, struct key *, int);
int getword(char *, int);

int main(int argc, char const *argv[]) {
    char word[MAXWORD];
    int n;
    struct key keytab[] = {
        {"break", 0},
        {"contine", 0},
        {"else", 0},
        {"if", 0},
        {"struct", 0}
    };
    
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

int binsearch(char *word, struct key tab[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        int temp = strcmp(word, tab[mid].word);
        if (temp < 0) {
            high = mid - 1;
        } else if (temp > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int getword(char *word, int lim) {
    int c, prev, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspce(c = getch())) {
        ;
    }
    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c) && c != '_') {  // 排除下划线在前的情况
        if (c == '#') {
            while ((c = getch()) != '\n') {
                ;
            }
        } else if (c == '\\') {
            while ((c = getch()) != '\\') {
                ;
            }
        } else if (c == '/') {
            if ((c = getch()) == '*') {
                prev = ' ';
                while ((c = getch()) != EOF) {// 从遇到 /* 开始循环，直到EOF 或者 */ 退出
                    if (c == '/' && prev == '*') {
                        break;
                    }
                    prev = c;
                } 
            } else if (c == '/') {
                while ((c = getch()) != '\n') {
                    ;
                }
            } else {
                ungetch(c);
            }
        } else {
            *w = '\0';
        }
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') { //    排除下划线在后的情况
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("error: too many parameters\n");
    } else {
        buf[bufp++] = c;
    }
}
