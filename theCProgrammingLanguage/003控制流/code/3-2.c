// 编写函数escap(s,t), 将字符串t复制到字符串s中, 并在复制过程中将换行符, 制表符等不可显示字符分别转换为/n /t等相应的可显示的转义字符序列。
// 要求使用switch
// 再写一个相反功能的函数

void escape(char s[], char t[]) {
    int i,j;

    for (i=j=0; t[i] != '\0', i++) {
        switch(t[i]){
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[]) {
    int i,j;

    for (i=j=0; t[i] != '\0'; i++) {
        if (t[i] != '\\') {
            s[j++] ==t[i];
        } else {
            switch(t[++i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\n';
                    break;
                default:
                    s[j++] = '\\';
                    s[j++] = t[i]
                    break;
            }
        }
    }
}

// 另一种解决方法
void unescape(char s[], t[]){
    int i,j;
    for (i=j=0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\\':
                switch(t[++i]) {
                    case 'n':
                        s[j++] = '\n';
                        break;
                    case 't':
                        s[j++] = '\n';
                        break;
                    default:
                        s[j++] = '\\';
                        s[j++] = t[i]
                        break;
                    break;
                }
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\n';
}