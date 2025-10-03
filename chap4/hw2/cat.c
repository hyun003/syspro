#include <stdio.h>
#include <string.h>

void process_file(FILE *fp, int show_lines, int *line_num_ptr);

int main(int argc, char *argv[]) {
    int show_line_numbers = 0;
    int line_count = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        show_line_numbers = 1;
        if (argc == 2) {
            process_file(stdin, show_line_numbers, &line_count);
        } else {
            for (int i = 2; i < argc; i++) {
                FILE *fp = fopen(argv[i], "r");
                if (fp == NULL) {
                    perror(argv[i]);
                    continue;
                }
                process_file(fp, show_line_numbers, &line_count);
                fclose(fp);
            }
        }
    } else {
        if (argc == 1) {
            process_file(stdin, show_line_numbers, &line_count);
        } else {
            for (int i = 1; i < argc; i++) {
                FILE *fp = fopen(argv[i], "r");
                if (fp == NULL) {
                    perror(argv[i]);
                    continue;
                }
                process_file(fp, show_line_numbers, &line_count);
                fclose(fp);
            }
        }
    }
    return 0;
}

void process_file(FILE *fp, int show_lines, int *line_num_ptr) {
    int c;
    int is_start_of_line = 1;

    while ((c = getc(fp)) != EOF) {
        if (show_lines && is_start_of_line) {
            printf("%6d\t", (*line_num_ptr)++);
            is_start_of_line = 0;
        }

        putc(c, stdout);

        if (c == '\n') {
            is_start_of_line = 1;
        }
    }
}
