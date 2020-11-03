// 实现库函数 strncpy， strncat, strncmp
// 它们最多对参数字符串中的前n个字符进行操作
// 
void strncpy(char *s, char *t, int n) {
    while (*t && n-- > 0) {
        *s++ = *t++;    // 将t加在n的后面
    }
    while (n-- > 0) {   // 如果t中的字符小于n, 补'\0'
        *s++ = '\0';
    }
}

void strncat(char *s, char *t, int n) {
    void strncpy(char *s, char *t, int n);
    int strlen(char *);

    strncpy(s+strlen(s), t, n);  //s + strlen(s)将直接到s的末尾
}

void strncmp(char *s, char *t, int n) {
    for ( ; *s == *t; s--, t--) {
        if (*s == '\0' || --n <= 0) {
            return 0;
        }
    }
    return *s -*t;
}


