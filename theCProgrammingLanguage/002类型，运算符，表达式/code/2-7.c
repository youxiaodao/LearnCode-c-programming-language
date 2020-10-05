/* 编写一个函数invert(x, p, n), 该函数返回对x执行下列操作后的结果值: 
    将x中从第p位开始的第n个(二进制)位求反(1-->0, 0-->1) 
    x的其余位保持不变。
*/

unsigned invert(insigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p+1-n));  // 异或   
}

/* 
1. 
2.
3.
4. 最后一步, 异或, 如果两个二进制取值相同, 他们的异或结果将是0,相同就是1。
