/* 修改打印最长文本的主程序main，使之可以打印任意长度的输入行的长度，并尽可能多的打印文本 */

#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
    int len;        // current line length
    int max;        // maximum length seen so far 
    char line[MAXLINE];     // current input line
    char longest[MAXLINE];  // longest line saved here

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        printf("%d, %s", len, line);
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {      // there was a line
        printf("MAXLENGTH: %d\nMAXCHAR: %s\n", max,longest);
    }
    return 0;
}

int getline(char s[], int lim) {
    int c,i,j;
    j = 0;
    for (i=0; (c=getchar())!=EOF && c != '\n';++i) {
        if (i < lim -2) {   // 数组的最后一个下标是lim-1 
            s[j] = c;       // line still in boundaries
            ++j;
        }
    }
    if (c == '\n') {    // lim-2 给换行符留了一个位置
        s[j] = c;
        ++j;
        ++i;
    }
    s[j] = '\0';    // lim-1 是字符串结束符
    return i;   // i 是字符个数  j是字符串长度 j比i大1 即 \0
}

void copy(char to[], char from[]) {
    int i;
    i=0;
    while((to[i] = from[i]) != '\0') {
        ++i;
    }
}