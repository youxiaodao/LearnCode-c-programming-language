/*  编写程序，
    打印输入中单词长度的直方图，
    水平方向的直方图比较容易绘制，垂直方向的直方图则要困难些 */

/* 
1. 初始化 记录单词字符数的数组
2. 获取输入，记录单词的长度到指定索引
    2.1 如果字符是空
        2.1.1 在单词外，state = OUT
        2.1.2 如果单词字符数nc > 0
            2.1.2.1 单词字符数 小于 单个单词最大字符数
                2.1.2.1.1 nc是单词长度，长度为nc的索引处+1
            2.1.2.2
                超出长度 +1
        nc = 0
    2.2 不是空
        2.2.1 state 是 out ，说明上一个字符是空
            修改state 为In
            nc = 1
        2.2.2 state 不是out，说明已经在一个单词里面了
            nc ++
3. 长度的最大值 = 0
4. 遍历wl 获得maxvalue的值
5. 遍历wl 
    5.1 打印 各个长度 各个长度的数量
    5.2 如果该长度的数量 > 0
        5.2.1 计算len
        5.2.2 打印*
    5.3 打印超出长度MAXWORD的数量
*/      
#include <stdio.h>

#define MAXHIST 15       /* max length of histogram */
#define MAXWORD 11       /* max length of a word */
#define IN      1        /* inside a word */
#define OUT     0        /* outside a word */

/* print horizontal histogram */
void main () {
    int c, i, nc, state;
    int len;             /* length of each bar */
    int maxvalue;        /* maximum value for wl[] */
    int ovflow;          /* number of overflow words */
    int wl[MAXWORD];     /* word length counters */

    state = OUT;
    nc = 0;             /* number of chars in a word */
    ovflow = 0;         /* number of words >= MAXWORD*/

    for (i=0;i<MAXWORD;++i) {
        wl[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t' ) {
            state = OUT;
            if (nc > 0) {
                if (nc < MAXWORD) {
                    ++wl[nc];
                } else {
                    ++ovflow;
                }
            }
            nc = 0;
        } else if (state == OUT) {
            state = IN;
            nc = 1;    /* beginning of a new word  */
        } else {
            ++nc;      /*inside a word */
        }
    }
    maxvalue = 0;
    for (i=1;i<MAXWORD;++i) {
        if (wl[i] > maxvalue) {
            maxvalue = wl[i];
        }
    }
    for (i=1;i<MAXWORD;++i) {
        printf("%5d - %5d:", i, wl[i]);
        if (wl[i] > 0) {
            if ((len = wl[i] * MAXHIST/maxvalue) <= 0) {
                len = 1;
            }
        } else {
            len = 0;
        }
        //printf("len:%d", len);
        while (len > 0) {
            putchar('*');
            --len;
        }
        putchar('\n');
    }
    if (ovflow > 0 ) {
        printf("There are %d words >= %d\n", ovflow, MAXWORD);
    }
}
