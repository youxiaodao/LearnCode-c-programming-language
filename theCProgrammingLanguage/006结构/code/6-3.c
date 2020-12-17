// 编写一个交叉引用程序
// 打印文档中所有单词的列表，并且每个单词还有一个列表，记录出现过该单词的行号
// 对the, end 等非实义单词不予考虑

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORD 100

struct linklist {           // linked list of line numbers
    int lnum;
    struct linklist *ptr;
};

struct tnode {
    char *word;     // points to the text
    struct linklist *lines;     // line numbers
    struct tnode *left;         // left child
    struct tnode *right;        // right child
};

struct tnode *addtreex(struct tnode *, char *, int);
int getword(char *, int);
int noiseword(char *);
void treexprint(struct tnode *);

int main(int argc, char const *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int linenum = 1;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && noiseword(word) == -1) {
            root = addtreex(root, word, linenum);
        } else if (word[0] == '\n') {
            linenum++;
        }
    }
    treexprint(root);
    return 0;
}

struct tnode *talloc(void);
struct linklist *ltalloc(void);
void addln(struct tnode *, int);

// add a node with w, at or below p
struct tnode *addtreex(struct tnode *p, char *w, int linenum) {
    int cond;

    if (p == NULL) {        // a new word has arrived
        p = talloc();       // make a new word
        p->word = strdup(w);
        p->lines = lalloc();
        p->lines->lnum = linenum;
        p->lines->ptr = NULL;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) ==0) {
        addln(p, linenum);
    } else if (cond < 0) {
        p->left = addtreex(p->left, w, linenum);
    } else {
        p->right = addtreex(p->right, w, linenum);
    }
    return p;
}

// add a line number to the linked list
void addln(struct tnode *p, int linenum) {
    struct linklist *temp;

    temp = p->lines;
    while (temp->ptr != NULL && temp->lnum != linenum) {
        temp = temp->ptr;
    }
    if (temp->lnum != linenum) {
        temp->ptr = lalloc();
        temp->ptr->lnum = linenum;
        temp->ptr->ptr = NULL;
    }
}

//in-order print of tree p
void treexprint(struct tnode *p) {
    struct linklist *temp;
    if (p != NULL) {
        treexprint(p->left);
        printf("%10s: ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->ptr) {
            printf("%4d ", temp->lnum);
        }
        printf("\n");
        treexprint(p->right);
    }
}

// make a linklist node
struct linklist *lalloc(void) {
    return (struct linklist *) malloc(sizeof(struct linklist));
}

// identify word as a noise word
int noiseword(char *w) {
    static char *nw[] = {
        "a",
        "an",
        "are",
        "in",
        "is",
        "of",
        "or",
        "that",
        "the",
        "this",
        "to"
    };
    int cond, mid;
    int low = 0;
    int high = sizeof(nw) / sizeof(char *) - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(w, nw[mid])) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
/*
    行号链表的每一个元素又是一个类型名为linklist的结构，每个结构包含一个行号和一个指针
    指针指向链表中的下一个元素(链表最后一个元素的这个指针将指向NULL)
    变量linenum 当前行号

    noiseword 用来提出文档中诸如 "the", "and" 之类不需要统计的单词

    为了记录行号，我们还修改了getword函数，使它能返回换行符
    
    while (isspace(c = getch()) && c != '\n') {
        ;
    }

*/



































