// 扩展dcl程序的功能, 使它能够处理包含其它成分的申明，例如：带有函数参数类型的声明，带有类似于const限定符的声明
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
extern char name[];     // identifier name
extern char datatype[]; // data type = char, int, etc
extern char out[]; 
extern int prevtoken;  

// parse a declarator
void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ) {  //count *'s
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
    void parmdcl(void);

    if (tokentype == '(') {     // ( dcl )
        dcl();
        if (tokentype != ')') {
            errmsg("error: missing )\n");
        }
    } else if (tokentype == NAME) { // variable name
        if (name[0] == '\0') {
            strcpy(name, token);
        }
    } else {
        prevtoken = YES;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else if (type == '('){
            strcat(out, " function expecting");
            parmdcl();
            strcat(out, " and returning");
            strcat(out, token);
            strcat(out, " of");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

// errmsg: print error message and indicate avail. token
void errmsg(char *msg) {
    printf("%s", msg);
    prevtoken = YES;
}

// 下面是源文件parmdcl.c的内容
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN    100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void errmsg(char *);
void dclspec(void);
int typespec(void);
int typequal(void);
int compare(char **, char **);
int gettoken(void);

extern int tokentype;   // type of last token
extern char token[];    // last token string
extern char name[];     // identifier name
extern char datatype[]; // data type = char, int, etc
extern char out[]; 
extern int prevtoken;  

// parse a parameter declarator
void parmdcl(void) {
    do {
        dclspec();
    } while (tokentype == ',');
    if (tokentype != ')') {
        errmsg("missing ) in parameter declaration\n");
    }
}

// dclspec: declaration specification
void dclspec(void) {
    char temp[MAXTOKEN];
    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            prevtoken = YES;
            dcl();
        } else if (typespec() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else if (typequal() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            errmsg("unknown type in paramerter list\n");
        }
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',') {
        strcat(out, ",");
    }
}

// return YES if token is a type-qualifier
int typequal(void) {
    static char *typeq[] = {
        "const",
        "volatitle"
    };
    char *pt = token;
    if (bsearch(&pt, typeq, sizeof(typeq)/sizeof(char *), sizeof(char *), compare) == NULL) {
        return NO;
    } else {
        return YES;
    }
}

// compare: compare two strings for bsearch
int compare(char **s, char **t) {
    return strcmp(*s, *t);
}

// 我们对 《C程序设计语言(第二版-新版)》 106页上的语法进行了扩充，增加了对参数声明符的处理能力
/*
    dcl:            optional *'s  direct-dcl
    direct-dcl:     name
                    (dcl)
                    direct-dcl(option parm-dcl)
                    direct-dcl(option size]
    parm-dcl:       parm-dcl, dcl-spec dcl
    dcl-spec:       type-spec dcl-spec
                    type-equal dcl-spec
*/

// 这是C语言语法描述声明符部分的一个略缩版本
// 扩展后的dcl 能够把 K&G原著211页上介绍的一部分类型说明符识别出来
// 比如说：如果程序输入的是
    // void *(*comp)(int *, char *, int (*fnc)())
// 它将产生如下所示的输出结果
    // comp: pointer to function expecting pointer to int, pointer
    //          to char, pointer to function returning int and returning
    //          pointer to void
// 我们对dirdcl函数进行了修改，并增加了parmdcl和dclspec函数
// 这里我们使用了我们在解答练习 5-18 时采用的提前分析下一个记号的思路
// 有时候，我们需要根据下一个记号来决定执行哪些操作
// 有时候 我肯分析出了下一个记号，但是还用不上它
// 那就要把它重新压回输入缓冲区
// 然后, 等我们在此法分析器中的其它地方再次调用gettoken函数的时候，再把这个记号取出来并进行相应的处理
// 
// bsearch是一个用来完成折半查找的标准库函数