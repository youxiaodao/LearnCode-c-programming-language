// 编写reverse(s), 将字符串s中的字符顺序颠倒过来。 使用该函数编写一个程序，每次颠倒一个输入行中的字符顺序。
#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[]);

int main(int argc, char const *argv[])
{
    char line[MAXLINE];     // current input line
    while (getline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

void reverse(char s[]){
    int i,j;
    char temp;

    i=0;
    while (s[i] != '\0') {      // find the end of tring
        ++i;
    }
    --i;        // back off from '\0
    if (s[i] =='\n') {
        --i;
    }
    j = 0; // beginning of new strings
    while (j<i) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;        // swap the characters
        --i;
        ++j;
    }
}