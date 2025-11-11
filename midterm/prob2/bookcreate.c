#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

int main() {
    FILE *fp;
    struct book new_book;

    fp = fopen("db.dat", "ab");
    if (fp == NULL) {
        perror("Error opening db.dat");
        return 1;
    }

    printf("Enter new book information.\n");

    printf("Enter ID: ");
    scanf("%d", &new_book.id);

    printf("Enter Title: ");
    scanf("%s", new_book.title); //

    printf("Enter Author: ");
    scanf("%s", new_book.author);

    printf("Enter Year: ");
    scanf("%d", &new_book.year);

    printf("Enter numofborrow: ");
    scanf("%d", &new_book.numofborrow);

    printf("Enter borrow (0:False/Available, 1:True/Borrowed): ");
    scanf("%d", &new_book.is_borrowed);

    fwrite(&new_book, sizeof(struct book), 1, fp);
    
    printf("\nNew book (ID: %d) added successfully.\n", new_book.id);

    fclose(fp);
    return 0;
}
