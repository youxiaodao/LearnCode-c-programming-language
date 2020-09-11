/* 编写程序，查找C语言中的基本语法错误，如圆括号，方括号以及花括号不配对等
要正确处理引号(单双),转义字符序列与注释。
要编写成完全通用的程序，难度比较大 */

#include <stdio.h>

int brace, brack, paren;

void in_quote(int c);
void in_comment(void);
void search(int c);

void main() {
    int c;
    extern int brace, brack, paren;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            if ((c = getchar()) == '*') {
                in_comment();       // inside comment
            } else {
                search(c);
            }
        } else if (c == '\'' || c == '"') {
            in_quote(c);        // inside quote
        } else {
            search(c);
        }

        if (brace < 0) {        // output errors
            printf("Unbalanced braces\n");
            brace = 0;
        } else if (brack < 0) {
            printf("Unbalanced brackets\n");
            brack = 0;
        } else if (paren < 0) {
            printf("Unbalanced parentheses\n");
            paren = 0;
        }
    }
    if (brace>0) {      // output errors
        printf("Unbalanced braces\n");
    }
    if (brack>0) {
        printf("Unbalanced beack\n");
    }
    if (paren>0) {
        printf("Unbalanced parentheses\n");
    }
}

void search(int c) {
    extern int brace, brack, paren;
    if (c == '{') {
        ++ brace;
    } else if (c == '}') {
        --brace;
    } else if (c == '[') {
        ++brack;
    } else if (c == ']') {
        --brack;
    } else if (c == '(') {
        ++paren;
    } else if (c == ')') {
        --paren;
    }
}

void in_comment(void) {
    int c,d;

    c = getchar();      // prev character 
    d = getchar();      // curr character 
    while (c != '*' || d != '/') {      // search for end
        c = d;
        d = getchar();
    }
}

void in_quote(int c) {
    int d;
    while ((d = getchar()) != c) {      // search end quote
        if (d == '\\') {                // ignore escape seq 
            getchar();
        }
    }
}

/* 检测3种语法错误: 不配对的圆括号 方括号 花括号 */
