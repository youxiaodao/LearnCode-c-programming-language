#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

int sp=0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, cant push %g\n", f);
    }
    printf("current_f:%f\n",f);
    printf("val::");
    for(int i = 0; i<MAXVAL;i++){
        printf("%g",val[i]);
    }
    printf("\n");
}


// pop函数: 弹出并返回栈顶的值
double pop(void) {
    printf("pop\n");
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
