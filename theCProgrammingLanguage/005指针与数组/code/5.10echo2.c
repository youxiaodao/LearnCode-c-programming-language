#include <stdio.h>

// 回显版本2
int main(int argc, char const *argv[])
{
    while (--argc > 0) {
        printf("%s%s", *++argv, (argc > 1) ? " ":"");  // ++argv使得它最开始指向argv[1], 而非argv[0]
        printf((argc > 1) ? "%s " : "%s", *++argv);     //也可以将它写成这样
    }
    printf("\n");
    return 0;
}

