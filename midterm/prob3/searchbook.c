#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main() {
    FILE *fp;
    struct book current_book;
    char search_name[MAX_TITLE_LEN];
    int found = 0; 

    fp = fopen("db.dat", "rb");
    if (fp == NULL) {
        perror("Error opening db.dat");
        return 1;
    }

    printf("Input name of book > ");
    
    fgets(search_name, MAX_TITLE_LEN, stdin);
    search_name[strcspn(search_name, "\n")] = 0; 

    while (fread(&current_book, sizeof(struct book), 1, fp) == 1) {
        
        if (strcmp(current_book.title, search_name) == 0) {
            found = 1; 
            
            printf("%-4s %-10s %-10s %-6s %-13s %s\n", 
                   "id", "bookname", "author", "year", "numofborrow", "borrow");
            printf("%-4d %-10s %-10s %-6d %-13d %s\n",
                   current_book.id,
                   current_book.title,
                   current_book.author,
                   current_book.year,
                   current_book.numofborrow,
                   (current_book.is_borrowed ? "True" : "False"));
            
            break; 
        }
    }

    if (found == 0) {
        printf("not found book name : '%s'\n", search_name);
    }

    fclose(fp);
    return 0;
}
