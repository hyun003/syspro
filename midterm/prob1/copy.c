#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;
    int mode;

    if (argc != 4) {
        fprintf(stderr, "How to use: %s mode source_file destination_file\n", argv[0]);
        return 1;
    }

    mode = argv[1][0] - '0';

    fp1 = fopen(argv[2], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s Open Error\n", argv[2]);
        return 2;
    }

    fp2 = fopen(argv[3], "w");
    if (fp2 == NULL) {
        fprintf(stderr, "File %s Create Error\n", argv[3]);
        fclose(fp1);
        return 3;
    }

    while ((c = fgetc(fp1)) != EOF) {
        if (mode == 1)
            c = tolower((unsigned char)c);
        else if (mode == 2)
            c = toupper((unsigned char)c);
        fputc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}

