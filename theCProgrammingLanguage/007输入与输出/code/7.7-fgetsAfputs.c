#include <stdio.h>

char *fgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n') {
            break;
        }
    }
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char *s, FILE *iop) {
    int c;
    while (c = *s++) {
        putc(c, iop);
    }
    return ferror(iop) ? EOF : "非负值"
}

// ANSI规定ferror在发生错误时返回非0，而发puts在发生错误时返回EOF，其它情况返回一个非负值