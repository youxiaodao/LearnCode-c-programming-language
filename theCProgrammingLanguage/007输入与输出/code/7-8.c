// 编写一个程序, 以打印一个文件集合, 每个文件从新的一页开始打印, 并且打印每个文件相应的标题和页数
#include <stdio.h>
#include <stdlib.h>

#define MAXBOT  3   // maximum # lines at bottom page
#define MAXHDR  5   // maximum # lines head of page
#define MAXLINE 100 // maximum size of one line
#define MAXPAGE 66  // maximum # lines on one page

// print files - each new one on a new page
int main(int argc, char const *argv[])
{
    FILE *fp;
    void fileprint(FILE *fp, char *fname);
    if (argc == 1) // no args; print standard input
        fileprint(stdin, " ");
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "print: cant't open %s \n", *argv);
                exit(1);
            } else {
                fileprint(fp, *argv);
                fclose(fp);
            }
        }
    }
    return 0;
}

// print file fname
void fileprint(FILE *fp, char *fname) {
    int lineno, pageno = 1;
    char line[MAXLINE];
    int heading(char *fname, int pageno);
    lineno = heading(fname, pageno++);
    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno == 1) {
            fprintf(stdout, "\f");
            lineno = heading(fname, pageno++);
        }
        fputs(line, stdout);
        if (++lineno > MAXPAGE - MAXBOT) {
            lineno = 1;
        }
    }
    fprintf(stdout, "\f");  //page eject after the file
}

// heading: put heading and enough blank lines
int heading(char *fname, int pageno) {
    int ln = 3;
    fprinf(stdout, "\n\n");
    fprinf(stdout, "%s  page %d\n", fname, pageno);
    while (ln++ < MAXHDR) {
        fprintf(stdout, "\n");
    }
    return ln;
}

/*
    字符 \f 是一个换行符
    变量lineno记录着已经在某页纸上打印了多少行
    页面上最大长度时MAXPAGE行
    每当lineno变为1，fileprint就将输出一个换行符, 在新页面上打印标题，然后重置lineno
    此外, 在每个文件的最后一页, 也要输出一个换页符

    函数heading先打印文件名和页码, 然后用组后的换行符在每页的开头留出总共MAXHDR行
    MAXBOT是尾每页末尾保留的空白行数
    
*/