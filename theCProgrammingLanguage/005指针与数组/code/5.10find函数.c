// 通过命令行的第一个参数指定待匹配的模式
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

// find函数: 打印与第一个参数指定的模式匹配的行
int main(int argc, char const *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc != 2) {
        printf("Usage: find pattern\n");
    } else {
        while (getline(line, MAXLINE) > 0) {
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}
/*
    strstr(s, t) 返回一个指针, 该指针执行字符串s中第一次出现的位置, 如果字符t没有出现在s中 ， 返回Null(空指针)

*/