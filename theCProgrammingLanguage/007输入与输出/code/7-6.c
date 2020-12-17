// 编写一个程序, 比较两个文件并打印它们第一个不相同的行

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

// compare two files,printing first different line
int main(int argc, char const *argv[])
{
    FILE *fp1, *fp2;
    void filecomp(FILE *fp1, FILE *fp2);

    if (argc != 3) {        // incorrect number of arguments?
        fprintf(stderr, "comp: need two file names\n");
        exit(1);
    } else {
        if ((fp1 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "comp: can't open %s\n", *argv);
            exit(1);
        } else if ((fp2 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "comp: can't open %s\n", *argv);
            exit(1);
        } else {
            filecomp(fp1, fp2);
            fclose(fp1);
            fclose(fp2);
            exit(0);
        }
    }
}

// compare two files - a line at a line
void filecomp(FILE *fp1, FILE *fp2) {
    char line1[MAXLINE], line2[MAXLINE];
    char *lp1, *lp2;

    do {
        lp1 = fgets(line1, MAXLINE, fp1);
        lp2 = fgets(line2, MAXLINE, fp2);
        if (lp1 == line1 && lp2 == line2) {
            if (strcmp(line1, line2) != 0) {
                printf("first difference line \n%s\n", line1);
                lp1 = lp2 = NULL;
            }
        } else if (lp1 != line1 && lp2 == line2) {
            printf("end of first file at line \n%s\n", line2);
        } else if (lp1 == line1 && lp2 != line2) {
            printf("end of second file at line \n%s\n", line1);
        }
    } while (lp1 == line1 && lp2 == line2);
}


