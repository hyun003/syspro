#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-e [name]] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            for (int i = 0; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);
        } else {
            char *value = getenv(argv[2]);
            if (value)
                printf("%s=%s\n", argv[2], value);
            else
                printf("Environment variable %s not found.\n", argv[2]);
        }
    }
    else if (strcmp(argv[1], "-u") == 0) {
        printf("Real User ID: %d\n", getuid());
        printf("Effective User ID: %d\n", geteuid());
    }
    else if (strcmp(argv[1], "-g") == 0) {
        printf("Real Group ID: %d\n", getgid());
        printf("Effective Group ID: %d\n", getegid());
    }
    else if (strcmp(argv[1], "-i") == 0) {
        printf("Process ID: %d\n", getpid());
    }
    else if (strcmp(argv[1], "-p") == 0) {
        printf("Parent Process ID: %d\n", getppid());
    }
    else {
        printf("Invalid option.\n");
    }

    return 0;
}

