// 按照数值大小, 而非字典顺序来比较两个输入行

#include <stdio.h>
#include <string.h>

#define MAXLINES   5000     // 待排序的最大行数
char *lineptr[MAXLINES];    // 指向文本行的指针

int readlines(char *lineptr[], int nlines);
void weitelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));

int numcmp(char *, char *);

//对输入的文本行进行排序
int main(int argc, char const *argv[])
{
    int nlines;     // 读入的输入行数
    int numeric = 0;    // 若进行数值排序, 则numeric的值为1

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numeric = 1;
    }
    if ((nlines = realines(lineptr, MAXLINES)) >= 0) {
        qsort((void **) lineptr, 0, nlines - 1, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
    return 0;
}

// qsort函数, 以递增顺序对v[left]  ...  v[right] 进行排序
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {   // *comp的调用 圆括号是必须的, 这样才能保证去哦中的各个部分正确结合
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
}
// qsort 的第四个参数声明 int (*comp)(void *, void *)
// 它表明comp是一个执行函数的指针, 该函数具有两个void * 类型的参数, 其返回值类型为int
// line 45 如果没有括号 int *comp(void *, void *),
// 则表明comp是一个函数, 该函数返回一个执行int类型的指针, 这同我们的本意有很大的区别

// 下面的 numcmp 也是比较两个字符串, 但它是通过调用atof计算字符串对应的数值

#include <stdlib.h>

// numcmp函数：按数值顺序比较字符串s1 和s2
int numcmp(char *s1, char *s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}
// 交换两个指针的swap函数和本章前面所述的swap函数相同, 但它的函数声明为void
void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

