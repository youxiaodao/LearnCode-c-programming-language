// 修改第五章的模式查找程序, 使它从一个命名文件的集合中读取输入(有文件名参数时),如果没有文件名参数, 则从标准输入中读取输入
// 当发现一个匹配行时, 是否应该将相应的文件名打印出来
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

//find : print lines that match pattern from 1st argument
int main(int argc, char const *argv[])
{
    char pattern[MAXLINE];
    int c, except = 0, number = 0;
    FILE *fp;
    void fpat(FILE *fp, char *fname, char *pattern, int except, int number);

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    break;
            }
        }
    }
    if (argc >= 1) {
        strcpy(pattern, *argv));
    } else {
        printf("Usage: find [-x] [-n] pattern [file ...]\n");
        exit(1);
    }
    if (argc == 1) {    // read standard input
        fpat(stdin, "", pattern, except, number);
    } else {
        while (argc > 0) {  // get a named file
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "find: can't open %s\n", *argv);
                exit(1);
            } else {        // named file has been opened
                fpat(fp, *argv, pattern, except, number);
                fclose(fp);
            }
        }
    }
    return 0;
}


// find pattern
void fpat(FILE *fp, char *fname, char *pattern, int except, int number) {
    char line[MAXLINE];
    long lineno = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {
        ++lineno;
        if ((strstr(line, pattern) != NULL) != except) {
            if (*fname) {
                printf("%s - ", fname);
            }
            if (number) {
                printf("%1d: ", lineno);
            }
            printf("%s", line);
        }
    }
}

/*
    主程序对参数的处理方法来源于第五章 
    然后它至少还需要一个参数,
    如果在模式后面灭有给出文件名, 它将使用系统的标准输入作为其输入源
    否则, 他就会打开一个指定文件, 无论怎样, 它都调用函数fpat

    fpat 和原始程序很像, 它每次读入一行, 直到fgets函数返回NULL为止
    fpat会根据有关参数在每一行中寻找有无给定的匹配模式
    下面时各种可能出现的情况
    (strstr(line, pattern) != NULL)     !=      except          结果
    0      (没有找到匹配模式)            !=         (未设定)    false
    1      (找到匹配模式)                !=         (未设定)    true
    0      (没有找到匹配模式)            !=         (设定)      false
    1      (找到匹配模式)                !=         (设定)      ture

    当这个表达式的结果时真, fpat将把文件名(如果不是标准输入的话)，行号（如果有命令行参数 -n) 以及这一行的内容依次打印出来
*/