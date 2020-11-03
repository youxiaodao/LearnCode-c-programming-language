// 对atof函数进行扩充, 使其可以处理形如 123.45e - 6
#include <ctype.h>
double atof(char s[]) {
    double val, power;
    int exp, i, sign;
    for (i = 0; isspace(s[i]); i++) {
        ;
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    val = sign * val / power;
    if (s[i] == 'e' || s[i] == 'E') {
        sign = (s[++i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            i++;
        }
        for (exp = 0; isdigit(s[i]); i++) {
            exp = 10 * exp + (s[i] - '0');
        }
        if (sign == 1) {
            while (exp-- > 0) {
                val *= 10;
            }
        } else {
            while (exp-- > 0) {
                val /= 10;
            }
        }
        return val;
    }
}
/* 
跳过多余的空白符
记录符号位
转换小数点左边
        eg:235.56
        10 * 0 + 2 = 2
        10 * 2 + 3 = 23
        10 * 23 + 5 = 235
    应该是 前面的值 * 进制 + 当前数
处理小数点
计算右边的数字
    记录右边有几位并乘以 power * 10
符号 * 结果除以 power 

处理科学计数 e
记录时正还是负 sign
处理值 exp
如果正值
    val * 10的exp次幂
是负值
    val / 10的exp次幂

为什么是除以10 而不是 乘以 0.1 
    因为0.1无法正确的用二进制表示, 在大多数的机器上, 0.1 的二进制表示法都要比0.1稍微小一点
*/

