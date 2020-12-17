/* 编写程序
    用以读入一个C语言程序
    并按字母表的顺序分组打印变量名
    要求每一组内各变量名的前6个字符相同，其余字符不同
    字符串和注释中的单词不予考虑
    请将6作为一个可在命令行中设定的参数
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct tnode {              // the tree node
    char *word;             // points to the text
    int match;              // match found
    struct tnode *left;     // left child
    struct tnode *right;    // right child
};

#define MAXWORD 100
#define YES 1
#define NO  0 

struct tnode *addtreex(struct tnode *, char *, int, int *);
void treexprint(struct tnode *);
int getword(char *, int);

// print in alphabetic order each group of variable names
// identical in the first num charcaters (default 6)
int main(int argc, char const *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int found = NO;     // YES if match was found
    int num;            // number of the first ident. chars

    num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0] + 1) : 6;
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= num) {
            root = addtreex(root, word, num, &found);
        }
        found = NO;
    }
    treexprint(root);
    return 0;
}

struct tnode *talloc(void);
int compare(char *, struct tnode *, int, int *);

// add a node with w, at or below p
struct tnode *addtreex(struct tnode *p, char *w, int num, int *found) {
    int cond;

    if (p == NULL) {    // A new word has arrived
        p = talloc();   // make a new node
        p->word = strdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    } else if ((cond = compare(w, p, num, found)) < 0) {
        p->left = addtreex(p->left, w, num, found);
    } else if (cond > 0) {
        p->right = addtreex(p->right, w, num, found);
    } 
    return p;
}

// compare words and update p->match
int compare(char *s, struct tnode *p, int num, int *found) {
    int i;
    char *t = p->word;

    for (i=0; *s == *t; i++, s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    if (i >= num) {     // identical in first num chars?
        *found = YES;
        p->match = YES;
    }
    return *s -*t;
}

// in-order print of tree p if p->match == YES
void treexprint(struct tnode *p) {
    if (p != NULL) {
        treexprint(p->left);
        if (p->match) {
            printf("%s\n", p->word);
        }
        treexprint(p->right);
    }
}
// 这个程序将把前num个字符相同的变量名打印出来
// 如果用户没有在命令行指定num的值, 就把num的值设为6

// 变量found 是一个布尔值，如果新识别出来的单词与变量名树上的某个单词前num个字符相同
// 我们就把变量found设置为YES；否则我们就把found设置为NO

// 如果某单词的第一个字符是一个字母且它的长度大于或等于num
// 这个程序就会把它添加到变量名中 函数getword来自练习6-1
// 函数addtreex是addtree函数(原著141页)的改进版，他负责把单词添加到变量名树中

// 函数compare把将被添加到变量名书中的单词与已经在变量树的单词进行比较
// 如果在前 num 个字符中找到了一个匹配，
// 那么与变量树中的单词相对应的*found以及匹配成员 (p->match) 都将被设置成YES
// 如下所示
    // if (i >= num) {
    //     *found = YES;
    //     p->match = YES;
    // }