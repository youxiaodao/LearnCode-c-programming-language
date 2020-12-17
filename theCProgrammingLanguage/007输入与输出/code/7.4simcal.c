#include <stdio.h>

main () {   // 简单计算器程序
    double sum, v;

    sum = 0;
    while (scanf("%1f", &v) == 1) {
        printf("\t%.2f\n", sum += v);
    }
    return 0;
}