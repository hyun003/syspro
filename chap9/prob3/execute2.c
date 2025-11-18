#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Parent process start\n");

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "First exec failed");
        exit(1);
    }

    if (fork() == 0) {
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "Second exec failed");
        exit(2);
    }

    if (fork() == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "Third exec failed");
        exit(3);
    }

    printf("Parent process end\n");
}

