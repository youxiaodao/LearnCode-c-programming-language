#include <stdio.h>

// 连接多个文件 版本2
int main(int argc, char const *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);

    char *prog = argv[0];       // 记下程序名，供错误处理用

    if (argc == 1)  // 如果命令行不带参数, 则复制标准输入
        filecopy(stdin, stdout);
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, 'r')) == NULL) {
                fprintf(stderr, "%s: cant't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/*
    该程序通过两种方式发出错误信息，首先，将fprintf函数产生的诊断信息输出到stderr上
    因此，诊断信息将会显示在屏幕上, 而不是仅仅输出到管道或输出文件中
    诊断信息中包含argv[0]中的程序名, 因此，当该程序和其他程序一起运行时，可以识别错误的来源

    其次, 程序使用了标准库函数exit， 然和调用该程序的进程都可以获取exit的参数值
        惯例：0表示正常

    如果流fp中出现错误, ferror返回一个非0值

    函数feof(FILE *) 与 ferror 类似
*/
