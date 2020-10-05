// 在数的二进制补码表示中,我们编写的itoa函数不能处理最大的负数,  即-(2 ^ (字长 - 1))的情况, 
// 请解释原因, 修改函数，使它在任何机器上运行时都能打印出正确的值

#define abs(x) ((x) < 0 ? -(x) : (x))

void itoa(int n, char s[]) {
    int i, sign;

    void reverse(char s[]);  // 1-19

    sign = n; // record sign
    i = 0;
    do {
        s[i++] = abs(n%10) + '0'; // get next digit  s[i] = AScii中该数字的值
    } while ((n /=10) != 0);
    if (sign<0){
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

// 首先 我们必须了解一个事实: -(2 ^ (字长 - 1))  
// 无法通过 n = -n 转换为一个正数
// 因为二进制补码所能表示的最大正数只能是(2 ^ (字长 - 1)) - 1

// 