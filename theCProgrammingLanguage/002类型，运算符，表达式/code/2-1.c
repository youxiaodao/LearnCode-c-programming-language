/* 确定由signed unsigned限定的char，short int long 类型的变量的取值范围。 */
// 1. 标准文件中的值 在 limits.h 中
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // signed types
    printf("signed char min = %d/n", -(char)((unsigned char) ~0 >> 1));
    printf("signed char max = %d/n", (char)((unsigned char) ~0 >> 1));
    printf("signed short min = %d/n", -(short)((unsigned short) ~0 >> 1));


    // unsigned type
    printf("unsigned char max = %u/n", (unsigned char)~0);
    return 0;
}

/* 1. 二进制补码
        符号数的三种表示方法 原码 反码 补码
        三种 均有符号位和数值位两部分
        符号位是0 正 1 负
        
    2. 按位取反符号 ~
    3. 位移操作 >>
    */