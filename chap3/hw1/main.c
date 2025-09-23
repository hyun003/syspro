#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 100
#define NUM 5

int main(void) {
    char lines[NUM][MAXLINE];
    char temp[MAXLINE];
    int i = 0;

    while (i < NUM && fgets(lines[i], MAXLINE, stdin) != NULL) {
        size_t len = strlen(lines[i]);
        if (len > 0 && lines[i][len - 1] == '\n') {
            lines[i][len - 1] = '\0';
        }
        i++;
    }
    int n = i;

    for (int a = 0; a < n - 1; ++a) {
        int max_idx = a;
        for (int b = a + 1; b < n; ++b) {
            if (strlen(lines[b]) > strlen(lines[max_idx])) {
                max_idx = b;
            }
        }
        if (max_idx != a) {
            copy(lines[a], temp);
            copy(lines[max_idx], lines[a]);
            copy(temp, lines[max_idx]);
        }
    }

    for (int k = 0; k < n; ++k) {
        printf("%s\n", lines[k]);
    }
    return 0;
}

