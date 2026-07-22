#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILENAME 100
#define MAXPAT 50
#define MAXROW 10000

void prefix(char *s, int len, int *next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len - 1) {
        if (j == -1 || s[i] == s[j]) {
            i++; j++;
            if (s[i] != s[j]) next[i] = j;
            else next[i] = next[j];
        }
        else j = next[j];
    }
}

int kmp_index(char *str, char *pat, int patlen, int *next) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (j == -1 || str[i] == pat[j]) {
            i++; j++;
            if (j == patlen) return 1;
        } else {
            j = next[j];
        }
    }
    return 0;
}

int main() {
    char filename[MAXFILENAME];
    char pat[MAXPAT];
    
    scanf("%s %s", filename, pat);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 1;
    }

    int row = 0;
    int patlen = strlen(pat);
    int next[MAXPAT];
    prefix(pat, patlen, next);

    char currrow[MAXROW];
    while (fgets(currrow, MAXROW, file) != NULL) {
        row++;
        if (kmp_index(currrow, pat, patlen, next)) {
            printf("%d %s", row, currrow);
        }
    }

    fclose(file);
    return 0;
}