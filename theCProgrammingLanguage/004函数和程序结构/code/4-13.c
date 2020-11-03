// 编写一个 递归版本的reverse(s) 函数, 以将字符串s倒置
#include <string.h>

void reverse(char s[]) {
    void reverser(char s[], int i, int len);
    reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int len) {
    int c, j;

    j = len - (i + 1);
    if (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverser(s, ++i, len);
    }
}


/*
    保持相同的reverse函数的用户接口
    因此, reverse(s) 函数的新版本仍将只有一个参数: 字符串s

    
*/