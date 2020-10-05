/* 在求二进制补码的时候, 表达式 x&(x - 1) 可以删除x中最右边值为1的一个二进制位。
请解释这样做的道理 */

int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x &= x - 1) {
        ++b;
        return b;
    }
}

