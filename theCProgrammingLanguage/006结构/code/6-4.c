// 编写一个程序，根据单词的出现频率按降序打印输入的各个不同的单词
// 并且在每个单词的前面标上它的出现次数


#include <stdio.h>
#include <ctype.h>

#define MAXWORD     100
#define NDISTINCT   1000

struct tnode {
    char *word;     // points to the text
    int count;      // number of occurrences
    struct tnode *left;         // left child
    struct tnode *right;        // right child
};

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void sortlist(void);
void treestore(struct tnode *);

struct tnode *list[NDISTINCT];  // pointers to tree nodes
int ntn = 0;                    // number of tree nodes

//print distinct words sorted in decreasing order of freq
int main(int argc, char const *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int i;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treestore(root);
    sortlist();
    for (i = 0; i < ntn; i++) {
        printf("%2d:%20s\n", list[i]->count, list[i]->word);
    }
    return 0;
}

// store in list[] pointers to tree nodes
void treestore(struct tnode *p) {
    if (p != NULL) {
        treestore(p->left);
        if (ntn < NDISTINCT) {
            list[ntn++] = p;
        }
        treestore(p->right);
    }
}

// sort list of pointers to tree nodes
void sortlist() {
    int gap, i, j;
    struct tnode *temp;

    for (gap = ntn/2; gap > 0; gap /= 2) {
        for (i = gap; i < ntn; i++) {
            for (j = i - gap; j >= 0; j -= gap) {
                if ((list[j]->count) >= (list[j+gap]->count)) {
                    break;
                }
                temp = list[j];
                list[j] = list[j + gap];
                list[j + gap] = temp;
            }
        }
    }
}

/*
常数NDISTINCT对不同单词的最大数目设置了限制
list十一个指针数组， 其中每个指针都指向一个tnode类型的结构
变量ntn中保存着树节点的个数

程序读入每个单词并把它放到树中， 函数treestore把那些指向tnode结构的指针保存到数组list中
函数sortlist是shellsort函数的改进版本
它按照单词出现次数由高到低对数组list进行排序
*/