// 编写一个函数strindex(s, t) 它将返回字符串t在s中最右边出现得位置, 如果s中不包含t, 则返回-1

int strrindex(char s[], char t[]) {
    int i, j, k, pos;
    pos = -1;

    for(i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k];j++, k++) { //遍历 s 将 s中的每一个字符 与 t中(每次都使从头开始)对比 
            ;                                                       // 说的使字符串?    
        }
        if (k > 0 && t[k] == '\0') {
            pos = i;
        }
    }
    return pos;
}

// #include <string.h>
// int strrindex_a(char s[], char t[]) {
//     int i, j, k;
//     for (i = strlen(s) - strlen(t); i >=0; i--) {       // 求两个字符串长度的差值, 从符合长度的最右端开始遍历  8 - 2 = 6 , 就从 6开始倒数
//         for (j = i, k=0; t[k] != '0' && s[j] == t[k]; j++, k++) {       // 
//             ;
//         }
//         if (k > 0 && t[k] == '\0') {
//             return i;
//         }
//     }
//     return -1;
// }

