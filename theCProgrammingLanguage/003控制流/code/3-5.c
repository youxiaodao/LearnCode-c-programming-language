// 编写函数 itob(n, s, b), 将整数n转换为以b为底的数, 并将转换结果以字符的形式保存到字符串中

// 思路:
// 因为我们要把整数n转换为一个b进制数, 所以我们要用 n % b
// 依次返回一个0 到 b-1 之间的值, 并把这个值转换为相应的字符保存到字符串s中
// 然后再利用n/=b调整n的值

// 先按照逆序生成b进制的每一位数字,再用函数reverse（1-19） 对字符串s中的字符做一次颠倒而得到最终的结果


void itob(int n, char s[], int b) {
    int i,j,sign;

    void reverse(char s[]);

    if((sign = n) < 0) {  // 给sign赋值n, 并判断正负
        n = -n;
    }
    i = 0;
    do {
        j = n % b;
        s[i++] = (j<=9)? j + '0' : j + 'a' - 10;
    }while((n /= b) > 0);
    if(sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}