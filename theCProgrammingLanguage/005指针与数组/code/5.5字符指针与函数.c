#include <stdio.h>
// 5.5 5. 2.
int main(void) { 
	printf("test\n");
	char amessage[] = "now is the time";
	char *pmessage = "now is the time";
	
	printf("%s\n", amessage);
	printf("%s\n", pmessage);
	amessage[1] = 'w';
	// *(pmessage+1) = 'u';
	printf("%s\n", amessage);
	printf("%s\n", *(pmessage+1));  // ?
	return 0;
}

// 复制字符串的例

void strcpy(char *s, char *t) {
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0') {
        i++;
    }
}


void strcry_(char *s, char *t) {
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}


void strcpy__(char *s, char *t) {
    while (*s++ = *t++) {
        ;
    }
}

// 比较字符串的例子
int strcmp(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++) {
        if (s[i] == '\0') {
            return 0;
        }
    }
    return s[i] - t[i];
}


int strcmp_(char *s, char *t) {
    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    return *s - *t;
}