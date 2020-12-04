
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);     // 按顺序打印树
int getword(char *, int);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

// 单词出现频率的统计
int main(int argc, char const *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);   // 新节点的空间, 返回一个能容纳一个树节点的空闲空间
char *strup(char *);    // 将单词复制发哦某个隐藏位置

// 在p的位置或p的下方增加一个w节点
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {            // 该单词是一个新单词
        p = talloc();           // 创建一个新节点
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;             // 新单词与节点中的单词匹配
    } else if (cond < 0) {      // 如果小于该节点的单词, 则进入左子树
        p->left = addtree(p->left, w);
    } else {                    // 反之, 进入右子树
        p->right = addtree(p->right, w);
    }
    return p;
}
// 
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

// 如果单词不随机到达， 树将不平衡，这种情况下程序的运行时间将大大增加

// 关于存储分配程序， 一种合适的方法是将malloc 的返回值声明为一个指向void类型的指针, 再显式的将指针强制转换为所需类型
#include <stdlib.h>

//创建一个tnode
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}
// 通过其参数传入的字符串复制到某个安全的位置
char *strdup(char *s) { //复制s到某个位置
    char *p;

    p = (char *) malloc(strlen(s) + 1); //执行+1操作是为了在结尾加上字符 '\0'
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

// 在没有可用空间的时候, malloc会返回NULL，
// 同时, strdup函数也将返回NULL, 
// strdup 函数的调用者负责出错处理
// 调用malloc函数得到的存储空间可以通过调用free函数释放以重用, 详细见第7章和第八章




