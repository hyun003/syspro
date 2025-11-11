#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int compare_books(const void *a, const void *b) {
    struct book *bookA = (struct book *)a;
    struct book *bookB = (struct book *)b;

    return bookB->numofborrow - bookA->numofborrow;
}

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

    struct book all_books[100];
    int count = 0;

    while (fread(&all_books[count], sizeof(struct book), 1, fp) == 1) {
        count++;
        if (count >= 100) break;
    }
    fclose(fp);

    qsort(all_books, count, sizeof(struct book), compare_books);

    printf("--bookquery--\n");
    printf("0: list of all books, 1: list of available books ) %d\n", mode);
    printf("%-4s %-10s %-10s %-6s %-13s %s\n", 
           "id", "bookname", "author", "year", "numofborrow", "borrow");
    
    for (int i = 0; i < count; i++) {
        
        if (mode == 0) {
            printf("%-4d %-10s %-10s %-6d %-13d %s\n",
                   all_books[i].id,
                   all_books[i].title,
                   all_books[i].author,
                   all_books[i].year,
                   all_books[i].numofborrow,
                   (all_books[i].is_borrowed ? "True" : "False"));
        } 
        else if (mode == 1) {
            
            if (all_books[i].is_borrowed == 1) {
                printf("%-4d %-10s %-10s %-6d %-13d %s\n",
                       all_books[i].id,
                       all_books[i].title,
                       all_books[i].author,
                       all_books[i].year,
                       all_books[i].numofborrow,
                       "True");
            }
        }
    }

    return 0;
}
