// -x   --  代表"除...之外"
// -n   --  代表行号

// find -x -n  模式
// find -nx    模式

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

// find函数： 打印所有与第一个参数指定的模式匹配的行
int main(int argc, char const *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1) {
        printf("Usage: find -x -n pattern\n");
    } else {
        while (getline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineno);
                }
                printf("%s", line);
                found++;
            }
        }
    }

    return found;
}
