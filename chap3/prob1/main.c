#include <stdio.h>
#include <string.h>
#include "copy.h"

int main(void) {
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    longest[0] = '\0';

    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
            --len;
        }
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    if (max > 0)
        printf("%s\n", longest);
    else
        printf("No input.\n");

    return 0;
}

