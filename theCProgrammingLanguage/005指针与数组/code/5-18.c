// 修改 dcl 使它能够处理输入中的错误

#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
void errmsg(char *);
int gettoken(void);

extern int tokentype;   // type of last token
extern char token[];    // last token string
extern char name[];     // 
extern int prevtoken;    // identifier name

// parse a devlarator
void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; ) {     // count *'s"
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

// parse a direct declaration
void dirdcl(void) {
    int type;
    if (tokentype == '(') {     // ( dcl )
        dcl();
        if (tokentype != ')') {
            errmsg("error: missing )\n");
        }
    } else if (tokentype == NAME) { // variable name
        strcpy(name, token);
    } else {
        errmsg("error: expexted name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

// print error message and indicate avail. token
void errmsg(char *msg) {
    printf("%s", msg);
    prevtoken = YES;
}

// 源文件 gettoken 的内容
#include <ctype.h>
#include <string.h>

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

extern int tokentype;   // type of last token
extern char token[];    // last token string
extern int prevtoken = NO;    // identifier name

// return next token
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);

    char *p = token;
    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) {
            ;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* 
    我们对函数dirdcl做了一些修改， 它现在能够分析出两种记号 -- 跟在dcl调用后的一个右括号 ( ")" )或者一个变量名
    如果不是这两种记号，我们将调用函数errmsg而不是printf
    errmsg会先打印一个出错信息，然后把变量prevtoken设置为YES以通知gettoken已经读入了一个记号
    gettoken开头部分有一个新的if语句，如下所示：
    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }
    这条语句的意思是：如果已经有了一个记号, 就不要再读入一个新记号了
        此版本并不是十全十美, 但是它已经具备一定的出错处理能力了
*/