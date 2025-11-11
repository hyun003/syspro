#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main() {
    FILE *fp;
    struct book current_book;
    int mode, bookId;
    int found = 0;

    fp = fopen("db.dat", "r+b");
    if (fp == NULL) {
        perror("Error opening db.dat");
        return 1;
    }

    printf("--bookupdate--\n");
    printf("0 bookId: borrow book, 1 bookId: return book ) ");
    scanf("%d %d", &mode, &bookId);

    while (fread(&current_book, sizeof(struct book), 1, fp) == 1) {
        
        if (current_book.id == bookId) {
            found = 1;

            if (mode == 0) { 
                
                if (current_book.is_borrowed == 0) { 
                    
                    current_book.is_borrowed = 1; 
                    current_book.numofborrow++;

                    fseek(fp, -sizeof(struct book), SEEK_CUR);
                    fwrite(&current_book, sizeof(struct book), 1, fp);

                    printf("You've got bellow book..\n");
                } else { 
                    printf("You cannot borrow below book since it has been booked.\n");
                }

            } else if (mode == 1) { 
                
                if (current_book.is_borrowed == 1) {
                    
                    current_book.is_borrowed = 0; 

                    fseek(fp, -sizeof(struct book), SEEK_CUR);
                    fwrite(&current_book, sizeof(struct book), 1, fp);

                    printf("You've returned bellow book..\n");
                } else { 
                    printf("You cannot return below book since it is available.\n");
                }
            }
            
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

    if (!found) {
        printf("Book with ID %d not found.\n", bookId);
    }

    fclose(fp);
    return 0;
}
