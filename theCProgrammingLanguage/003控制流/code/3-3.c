// 编写expand(s1, s2)
// 将字符串中的类似于a-z一类的速记符号再字符串s2中扩展
// 并可以处理a-b-c a-z0-9类似的情况

void expend(char s1[], s2[]) {
    char c;
    int i,j;
    
    i = j = 0;
    while (c = s1[i++] != '\0') {//fetch a char from s1[]  先获取再自增
        if (s1[i] == '-' && s1[i+1] >= c) {
            i++;
            while (c < s1[i]) {
                s2[j++] = c++;
            }
        } else {
            s2[j++] =c;
        }
    }  
    s2[j] = '\0';
}