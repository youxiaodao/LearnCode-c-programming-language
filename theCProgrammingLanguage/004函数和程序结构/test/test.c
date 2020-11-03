#include <stdio.h>
// #include "4-1.c"

int strrindex(char [], char []);

int main(int argc, char const *argv[]) {
    int c;
    char a[] = "asdffdasfd";
    char b[] = "daf";
    c = strrindex(a, b);
    printf("index:%d", c);
    return 0;
}


int strrindex(char s[], char t[]) {
    int i, j, k, pos;
    pos = -1;

    for(i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k];j++, k++) { //遍历 s 将 s中的每一个字符 与 t中(每次都使从头开始)对比 
            ;                                                       // 说是使字符串?    
        }
        if (k > 0 && t[k] == '\0') {   // t[k] == '\0' 保证 遍历完k 
            pos = i;
        }
    }
    return pos;
}