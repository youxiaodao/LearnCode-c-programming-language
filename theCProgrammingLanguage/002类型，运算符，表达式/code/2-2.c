// 不使用&&和||编写一个与上面的for循环语句等价的循环语句

int main(int argc, char const *argv[])
{
    int i,lim;
    for(i=0; i<lim-1 && (c=getchar())!= '\n' && c != EOF; ++i){}

    enum loop { NO, YES};
    enum loop okloop = YES;

    i = 0;
    while (okloop == YES) {
        if (i > lim -1) {
            okloop = NO;
        }else if ((c=getchar()) == '\n') {
            okloop = NO;
        }else if (c == EOF){
            okloop = NO;
        }else {
            s[i] = c;
            ++i;
        }
        
    }
    return 0;
}
// 在不适用 && || 的情况下，我们只能把原来for循环分解为一系列if语句。一旦条件中的某一个满足，循环就结束了
