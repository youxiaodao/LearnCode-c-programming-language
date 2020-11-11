// 对程序endtab和detab做一些扩充, 以接受下面的命令
// entab -m +n
// 表示制表符从第m列开始, 每隔n列停止, 选择（对使用者而言) 比较方便的默认行为

#include <stdio.h>

#define MAXLINE 100     // maximum line size
#define TABINC  8       // default tab increment size
#define YES     1
#define NO      0
void esettab(int argc, char *argv[], char *tab);
void entab(char *tab);

int main(int argc, char const *argv[])
{
    char tab[MAXLINE];
    esettab(argc, argv, tab);
    entab(tab);
    return 0;
}

#include <stdio.h>

#define MAXLINE 100     // maxumum line size
#define TABINC  8       // default tab increment size
#define YES     1
#define NO      0

void esettab(int argc, char *argv[], char *tab) {
    int i, inc, pos;

    if (argc <= 1) {
        for (i = 1; i<=MAXLINE; i++) {
            if (i % TABINC == 0) {
                tab[i] = YES;
            } else {
                tab[i] = NO;
            }
        }
    } else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+'){    // argc == 3 user provided range 
        pos = atoi(&(*++argv)[1]);
        inc = atoi(&(*++argv)[1]);
        for (i = 1; i <= MAXLINE; i++) {
            if (i != pos) {
                tab[i] = NO;
            } else {
                tab[i] = YES;
            }
        }
    } else {    // user provided tab stops
        for (i = 1; i <= MAXLINE; i++) {
            tab[i] = NO;
        }
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE) {
                tab[pos] = YES;
            }
        }
    }
}


#include <stdio.h>

#define MAXLINE 100     // maxumum line size
#define TABINC  8       // default tab increment size
#define YES     1
#define NO      0

void esettab(int argc, char *argv[], char *tab);
void detab(char *tab);

//replace tabs with blanks
main(int argc, char *argv[]) {
    char tab[MAXLINE];

    esettab(argc, argv, tab);   // initialize tab stops
    detab(tab);     // replace tab w/ blanks
}

