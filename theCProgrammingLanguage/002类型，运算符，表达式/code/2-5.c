// 编写函数any(s1, s2)
// 将字符串s2中的任意字符再字符串s1中第一次出现的位置作为结果返回
// 如果s1 中不包含s2中的字符, 则返回 -1
// 标准库函数strpbrk 具有相同的功能，但它返回的是指向该位置的指针

int any(char s1[], char s2[]) {
    int i, j;

    for (i=0;s1[i] != '0';++i) {
        for (j=0;s2[j] != '0';++j) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}