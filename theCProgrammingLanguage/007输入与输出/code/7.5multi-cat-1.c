#include <stdio.h>

//链接多个文件-版本1
int main(int argc, char const *argv[])
{
    FILE *fp;
    void filecopy(FILE *,FILE *);

    if (argc == 1) {        // 如果没有命令行参数, 则复制标准输入
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, 'r')) == NULL) {
                printf("cat: can't open %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}
// 将文件ifp复制到ofp
void filecopy(FILE *ifp, FILE *ofp) {
    int c;
    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

