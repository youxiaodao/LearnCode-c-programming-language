// 编写函数 ungets(s) ,将整个字符串s压回到输入中, ungets函数需要使用buf和bufp吗? 他能否仅使用ungetch函数?
#include <string.h>
void ungets(char s[]) {
    int len = strlen(s);
    void ungetch(int);
    while (len > 0) {       // 长度迭代中将多个字符存入
        ungetch(s[--len]);
    }
}