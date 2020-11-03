// 用指针的方式实现第2章的函数strcat
// 函数strcat(s,t)将t指向的字符串复制到s指向的字符串的尾部

void strcat(char *s, char *t) {
    // while (*s++ != '\0') {
    //     ;
    // }
    while (*s) {
        s++;    // 如果放在上面条件里面，在下面就要加上一行s--
    }
    while (*s++ = *t++) {
        ;
    }
}