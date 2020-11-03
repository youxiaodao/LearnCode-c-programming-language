
#include <stdio.h>
#include <string.h>

#define MAXLINES    5000    // 进行排序的最大文本行数

char *lineptr[MAXLINES];    // 指向文本行的指针数组

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main(int argc, char const *argv[])
{
    int nlines;  // 读取的输入行数目

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: intput too big to sort\n");
        return 1;
    }
    return 0;
}

#define MAXLEN  1000    // 每个输入文本行的最大长度
int getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';   // 删除换行符
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i<nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

//another writelines 
void anotherwritelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

// 第四章的快排左改动
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);  // 交换 第一个和中间的值
    last = left;
    for (i = left + 1; i <= right; i++) {   // 从第二个开始比较, 和原中间的值比较
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char  *temp;

    temp = v[i];
    v[j] = v[i];
    v[j] = temp;
}