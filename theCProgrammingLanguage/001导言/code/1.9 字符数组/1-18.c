// 删除每个输入行末尾的空格及制表符，并删除完全是空格的行
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int remove(char s[]);

int main(int argc, char const *argv[])
{
    char line[MAXLINE];     // current input line 
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

    while(s[i] != '\n') {       // find newline character
        ++i;
    }
    --i; // 回退到末尾      back off from '\n'
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
        --i;
    }
    if ( i >=0 ) {      // is it a nonblank line?
        ++i;
        s[i] = '\n'; // put newline character back 
        ++i;
        s[i] = '\0';    // terminate the string
    }
    return i;
}

int getline(char s[], int lim) {
    int c, i, j;
    j = 0;
    for (i=0;(c = getchar())!= EOF && c != '\n'; ++i) {
        if (i < lim -2) {
            s[j] = c;
            ++j;
        }
    } 
    if (c == '\n') {
        s[j] = c;
        ++j;
        ++i;
    }
    s[j] = '\0';
    return i;
}