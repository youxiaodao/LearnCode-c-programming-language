/* 编写函数rightrot(x, n), 该函数返回将x循环右移(即从最右端移出的位将从最左端移入)n(二进制)位后所得到的值 */
unsigned rightrot(unsigned x, int n){
    int wordlength(void);
    int rbit;   // rightmost bit

    while(n--) {
        rbit = (x&1) << (wordlength() - 1);     // 保留最右端的数字 << 字长-1 eg： 000001  ===> 1000000000
        x = x >> 1;     // shift x 1 position right    冲掉了最右端的1
        x = x | rbit;   // complete one rotation        
    }
    return x;
}

/* 
1. 利用变量rbit把x最右端的位左移到最左端的位置(wordlength()-1)
2. 把x右移一位, 再对右移后的x与rbit进行OR操作, 这就完成了一次对x的循环右移操作。
*/

// 函数wordlength()的作用是计算出运行程序的计算机所使用的字长
// 字长是CPU的主要技术指标之一，指的是CPU一次能并行处理的二进制位数，字长总是8的整数倍，通常PC机的字长为16位（早期），32位，64位。 [4] 

int wordlengh(void) {
    int i;
    unsigned v = (unsigned) ~0;

    for (i=1; (v=v>>1) > 0; i++) {
        ;
    }
    return i;
}

// 另一种解法
unsigned rightrot_(unsigned x, int n) {
    int wordlength(void);
    unsigned rbits;

    if ((n = n%wordlength()) > 0) {
        rbits = ~(~0 << n) & x;  // n rightmost bits of x
                                    // n rightmost bits to left
        rbits = rbits << (wordlength() - n);
        x = x >> n;             // s shifted n positions right
        x = x | rbits;          // rotation completed
    }
    return x;
}

/*
1. 如果对x进行循环右移的总位数(n) 与一个无符号整数的二进制位数(即这台计算机的子长)相等, 完成这些次循环右移后的结果将与x完全一样, 因此我们就不必对x进行循环右移了
2. 如果n小于字长, 那我们就必须把x循环右移n位。
3. 如果n大于这台计算机的字长, 那么我们只需要先(利用取模运算符)求出n对这台计算机的子长的余数, 再把x循环右移这个余数代表的次数.
4. 综上, 我们得到不需要循环的解决方案
~0 << n     把一个全是1的屏蔽码左移n位, 在它的最右端制造出n位0
~(~0 << n)  把屏蔽码最右端的n位设置位1，其余则设置为0

当我们用这个屏蔽码和x进行AND运算时，x最右端的n位将被赋值给变量rbits
然后, 将rbits中的1左移到它的最左端, 把x右移n位, 再对右移后的x和rbits进行OR运算,
就完成了对无符号整数x循环右移n位
