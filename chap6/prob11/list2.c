#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <unistd.h>

char type(mode_t);
char* perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int opt_i = 0, opt_p = 0, opt_Q = 0;
    int c;

    while ((c = getopt(argc, argv, "ipQ")) != -1) {
        if (c == 'i') opt_i = 1;
        else if (c == 'p') opt_p = 1;
        else if (c == 'Q') opt_Q = 1;
    }

    if (optind < argc) dir = argv[optind];
    else dir = ".";

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
            continue;
        }
        printStat(path, d->d_name, &st, opt_i, opt_p, opt_Q);
    }

    closedir(dp);
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st, int opt_i, int opt_p, int opt_Q) {
    struct passwd *pw;
    struct group  *gr;
    char timebuf[64];
    char *timestr;

    pw = getpwuid(st->st_uid);
    gr = getgrgid(st->st_gid);
    timestr = ctime(&st->st_mtime);
    if (timestr == NULL) timestr = "";

    /* blocks */
    printf("%5ld ", (long)st->st_blocks / 2); /* 보통 ls -s 는 1K-block 단위; 필요하면 나눔/조정 */
    if (opt_i) printf("%-10llu ", (unsigned long long)st->st_ino);

    if (opt_p) {
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    } else {
        /* 기본 예시에서는 타입+권한도 보이므로 출력하도록 함 (과제 예시 맞춤) */
        printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    }

    printf("%3ld ", (long)st->st_nlink);
    printf("%-8s ", pw ? pw->pw_name : "UNKNOWN");
    printf("%-8s ", gr ? gr->gr_name : "UNKNOWN");
    printf("%8ld ", (long)st->st_size);

    /* 시간: ctime 문자열에서 "Mmm dd hh:mm" 형태 (skip weekday) */
    if (timestr[0] != '\0') {
        snprintf(timebuf, sizeof(timebuf), "%.12s", timestr + 4);
        printf("%s ", timebuf);
    } else {
        printf("------------ ");
    }

    if (opt_Q) printf("\"%s\"\n", file);
    else printf("%s\n", file);
}

char type(mode_t mode) {
    if (S_ISREG(mode)) return('-');
    if (S_ISDIR(mode)) return('d');
    if (S_ISCHR(mode)) return('c');
    if (S_ISBLK(mode)) return('b');
    if (S_ISLNK(mode)) return('l');
    if (S_ISFIFO(mode)) return('p');
    if (S_ISSOCK(mode)) return('s');
    return('?');
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");
    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';
    return perms;
}

