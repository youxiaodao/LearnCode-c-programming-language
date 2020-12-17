
#include <stdio.h>
#include <ctype.h>

// get next word or character form input 
int getword(char *word, int lim) {
    int c, d, comment(void), getch(void);
    void ungetch(int);

    char *w = word;

    while (isspace(c = getch())) {
        ;
    }
    if (c != EOF) {
        *w++ = c;
    }

    if (isalpha(c) || c == '-' || c == '#') {
        for ( ; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '-') {
                ungetch(*w);
                break;
            }
        }
    } else if (c == '\'' || c == '"') {
        for ( ; --lim > 0; w++) {
            if ((*w = getch()) == '\\') {
                *++w = getch();
            } else if (*w == EOF) {
                break;
            } else if (*w == c) {
                w++;
                break;
            }
        }
    } else if (c == '/') {
        if ((d = getch()) == '*') {
            c = comment();
        } else {
            ungetch(d);
        }
    }
    *w = '\0';
    return c;
}

// skip over comment and return a character
int comment(void) {
    int c;
    while ((c = getch()) != EOF) {
        if (c == '*') {
            if ((c = getch()) == '/') {
                break;
            } else {
                ungetch(c);
            }
        }
    }
    return c;
}

// 为了处理下划线 和 预编译器指令, 我们把原来的
// if (!alpha(c))
// 修改为
// if (isalpha(c) || c == '_' || c == '#')
// 跟在 _ 和 # 后面的字母和数字字符将被看作是单词的一部分

// 
//    字符串常量可能出现在单引号或双引号中，一旦检测到左引号, 我们就将把该左引号
//    到与之右引号或标记之间的全部字符收集起来，
//    并把它们当作一个字符串常量来对待
//  如过遇到注释, 我们就跳过其内容并返回它的结尾斜线字符，
//  这部分代码类似于练习 1-24