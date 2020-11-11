// 修改程序entab 和 detab （第一章练习中编写的函数）,
// 使它们接受一组作为参数的制表符停止位, 如果启动程序时不带参数, 则使用默认的制表符停止位设置
#include <stdio.h>

#define MAXLINE 100     // maximum line size
#define TABINC  8       // default tab increment size
#define YES     1
#define NO      0

void settab(int argc, char *argv[], char *tab);
void entab(char *tab);
int tabpos(int pos, char *tab);

int main(int argc, char const *argv[])
{
    char tab[MAXLINE + 1];

    settab(argc, argv, tab);
    entab(tab);
    return 0;
}

// endtab: replace strings of blanks with tabs and blanks
void entab(char *tab) {
    int c, pos;
    int nb = 0; //# of blanks necessary
    int nt = 0; //# of tabs necessary

    for (pos=1; (c = getchar()) != EOF; pos++) {
        if (c = ' ') {
            if (tabpos(pos, tab) == NO) {
                ++nb;
            } else {
                nb = 0;
                ++nt;
            }
        } else {
            for ( ; nt > 0; nt--) {
                putchar('\t');  //output tab(s)
            }
            if (c == '\t') {
                nb = 0;
            } else {
                for ( ; nb > 0; nb--) {
                    putchar(' ');
                }
            }
            putchar(c);
            if (c == '\n') {
                pos = 0;
            } else if (c == '\t') {
                while (tabpos(pos, tab) != YES) {
                    ++pos;
                }
            }
        }
    }
}


#include <stdio.h>

#define MAXLINE 100     // maximum line size
#define TABINC  8       // default tab increment size
#define YES     1
#define NO      0

void settab(int argc, char *argv[], char *tab);
void detab(char *tab);
int tabpos(int pos, char *tab);

//replace tabs with blanks
int main(int argc, char const *argv[])
{
    char tab[MAXLINE + 1];
    settab(argc, argv, tab);    // initialize tab stops
    detab(tab);     // replace tab w/ blanks
    return 0;
}

void detab(char *tab) {
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
        if(c == '\t') {
            do {
                putchar(' ');
            }while (tabpos(pos++, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
}
