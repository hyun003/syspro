#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXCMD 1024
#define MAXARG 64

int main() {
    char cmdline[MAXCMD];
    char *args[MAXARG];

    while (1) {
        printf("Shell> ");
        if (!fgets(cmdline, MAXCMD, stdin))
            break;

        cmdline[strcspn(cmdline, "\n")] = '\0';

        int background = 0;
        if (cmdline[strlen(cmdline) - 1] == '&') {
            background = 1;
            cmdline[strlen(cmdline) - 1] = '\0';
        }

        char *token = strtok(cmdline, " ");
        int i = 0;
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        } else {
            if (!background)
                waitpid(pid, NULL, 0);
        }
    }
    return 0;
}

