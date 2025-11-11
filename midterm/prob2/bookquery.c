#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        fprintf(stderr, "mode 0: list of all books\n");
        fprintf(stderr, "mode 1: list of available books\n");
        return 1;
    }

    int mode = atoi(argv[1]);
    if (mode != 0 && mode != 1) {
        fprintf(stderr, "Invalid mode. Use 0 or 1.\n");
        return 1;
    }

    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        perror("Error opening db.dat");
        return 1;
    }

    struct book current_book;

    printf("--bookquery--\n");
    printf("0: list of all books, 1: list of available books ) %d\n", mode);

    printf("%-4s %-10s %-10s %-6s %-13s %s\n", 
           "id", "bookname", "author", "year", "numofborrow", "borrow");

    while (fread(&current_book, sizeof(struct book), 1, fp) == 1) {
        
        if (mode == 0) {
            printf("%-4d %-10s %-10s %-6d %-13d %s\n",
                   current_book.id,
                   current_book.title,
                   current_book.author,
                   current_book.year,
                   current_book.numofborrow,
                   (current_book.is_borrowed ? "True" : "False"));
        } 
        else if (mode == 1) {
            if (current_book.is_borrowed == 1) {
            
                printf("%-4d %-10s %-10s %-6d %-13d %s\n",
                       current_book.id,
                       current_book.title,
                       current_book.author,
                       current_book.year,
                       current_book.numofborrow,
                       "True"); 
			}
        }
    }

    fclose(fp);
    return 0;
}
