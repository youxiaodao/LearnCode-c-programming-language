// 打印长度大于80个字符的所有输入行
#include <stdio.h>
#define MAXLINE 1000
#define LONGLINE 80

int getline(char line[], int maxline);

int main(int argc, char const *argv[])
{
    int len;
    char line[MAXLINE];
    while ((len= getline(line, MAXLINE)) > 0) {
        if (len > LONGLINE) {
            printf("%s", line);
        }
    }
    return 0;
}
