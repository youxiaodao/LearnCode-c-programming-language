// 删除每个输入行末尾的空格及制表符，并删除完全是空格的行
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int remove(char s[]);

int main(int argc, char const *argv[])
{
    char line[MAXLINE];
    while (getline(line, MAXLINE) > 0) {
        if (remove(line) > 0) {
            printf("%s", line);
        }
    }
    
    return 0;
}

int remove(char s[]) {
    int i;
    i=0;

    while(s[i] != '\n') {
        ++i;
    }
    --i; // 回退到末尾
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
        --i;
    }
    if ( i >=0 ) {
        ++i;
        s[i] = '\n'; // 替换末尾的 空格和\t
        ++i;
        s[i] = '\0';
    }
    return i;
}