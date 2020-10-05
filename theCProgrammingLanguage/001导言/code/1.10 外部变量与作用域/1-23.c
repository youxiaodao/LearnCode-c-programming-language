/* 删除C语言程序中所有的注释语句。 要正确处理带引号的字符串与字符常量 。
    在C语言中，注释不允许嵌套。 */

#include <stdio.h>

void rcoment(int c);
void in_comment(void);
void echo_quote(int c);

/* remove all comments from a valid C program */
int main() {
    int c, d;
    while ((c = getchar()) != EOF) {
        rcoment(c);
    }
    return 0;
    
}

/* rcomment: read each character, remove the comments */
void rcomment(int c) {
    int d;

    if (c == '/') {
        if ((d = getchar()) == '*') {
            in_comment();           // beginning comment
        } else if (d == '/') {
            putchar(c);             // another slash
            rcomment(d);
        } else {
            putchar(c);             // not a comment
            putchar(d);
        }
    } else if (c == '\'' || c == '"') {
        echo_quote(c);          // quote begins
    } else {
        putchar(c);         // not a comment 
    }
}

/* in_comment: inside of a valid comment */
void in_comment(void) {
    int c, d;
    c = getchar();  // prev character
    d = getchar();  // curr character 
    while (c!='*' || d !='/') { // search for end
        c = d;
        d = getchar();
    }
}

/* echo_quote: echo characters within quotes */
void echo_quote(int c) {
    int d;
    putchar(c);

    while ((d = getchar()) != c) {   // search for end
        putchar(d);
        if (d == '\\') {
            putchar(getchar());     // ignore escape seq 
        }
    }
    putchar(c);
}

/* 程序假设输入的是一个合法的c程序。 
函数rcomment搜索注释语句的额起始标志（/*） 
在找到这个标志时，它将调用另一个函数in_comment搜索注释语句的结束标志(*/
/* 从而确保C程序中的注释语句都能被删除。
函数rcomment还将搜索单引号和双引号，在找到他们时，它将调用另一个函数echo_quote.
函数echo_quote确保引号中的内同能够按照原样输出，不会被误认为时注释。
函数echo_quote不会把跟在一个反斜杠后面的引号看作结束引号() 
其他字符按照原样输出
程序在getchar返回文件结束符时结束运行
*/

