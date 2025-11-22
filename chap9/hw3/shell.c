#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD 1024
#define MAX_ARG 64

void execute_cmd(char *cmd) {
    char *args[MAX_ARG];
    int i = 0;
    int background = 0;
    int in_redirect = 0, out_redirect = 0;
    char *infile = NULL, *outfile = NULL;

    if (cmd[strlen(cmd) - 1] == '&') {
        background = 1;
        cmd[strlen(cmd) - 1] = '\0';
    }

    char *token = strtok(cmd, " ");
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            in_redirect = 1;
            token = strtok(NULL, " ");
            infile = token;
        } else if (strcmp(token, ">") == 0) {
            out_redirect = 1;
            token = strtok(NULL, " ");
            outfile = token;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    pid_t pid = fork();
    if (pid == 0) {
        if (in_redirect) {
            int fd = open(infile, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (out_redirect) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (!background) {
        waitpid(pid, NULL, 0); // 순차적 실행
    }
}

int main() {
    char cmdline[MAX_CMD];

    while (1) {
        printf("shell> ");
        if (!fgets(cmdline, MAX_CMD, stdin)) break;

        cmdline[strcspn(cmdline, "\n")] = '\0';

        char *cmd = strtok(cmdline, ";");
        while (cmd != NULL) {
            execute_cmd(cmd);
            cmd = strtok(NULL, ";");
        }
    }
    return 0;
}

