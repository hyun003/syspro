#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main()
{ 
    printf("My Real User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("My Effective User ID: %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
    printf("My Real Group ID: %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
    printf("My Effective Group ID: %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
}

