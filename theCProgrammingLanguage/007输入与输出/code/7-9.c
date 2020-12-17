// 类似于isupper这样的函数, 可以通过某种方式实现以达到节省空间或时间的目的
// 考虑节省空间或时间的实现方式

// return 1(true) if c is an upper case letter
int isupper(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 1;
    } else {
        return 0;
    }
}

// 函数空间利用率较高

#define isupper(c)  ((c) >= 'A' && (c) <= 'Z') ? 1 : 0
// 这个版本时间效率较高, 但是使用较多的空间
    // 节约时间： 因为没有函数调用的开销
    // 空间开销：是一个宏, 每次执行都要进行展开

// 使用宏带来潜在的问题
    // eg
/*
    char *p = "This is a string";

    if (isupper(*p++))
    ...
*/
    // 根据*p的情况, 这个表达式会对p做两次递增操作
    // 下面是一种值得参考的解决方案
/*
    char *p = "This is a string";

    if (isupper(*p))
        ...
    p++;
    
*/
// 对那些有可能对参数进行多次求值的宏, 一定要提高警惕
// 头文件 <ctype.h>中两个宏toupper 和 tolower是两个很好的学习例子