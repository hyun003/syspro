#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

struct Node {
    struct book data;
    struct Node *next;
};

void insert_sorted(struct Node **head_ref, struct book new_book) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_book;
    new_node->next = NULL;

    struct Node* current;

    if (*head_ref == NULL || (*head_ref)->data.year < new_book.year) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        current = *head_ref;
        while (current->next != NULL && current->next->data.year > new_book.year) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

int main() {
    FILE *fp;
    struct Node *head = NULL; 
    struct book books_db[4];
    
    books_db[0].id = 1;
    strcpy(books_db[0].title, "1984");
    strcpy(books_db[0].author, "George");
    books_db[0].year = 1949;
    books_db[0].numofborrow = 7;
    books_db[0].is_borrowed = 0; 

    books_db[1].id = 2;
    strcpy(books_db[1].title, "Luster");
    strcpy(books_db[1].author, "Raven");
    books_db[1].year = 2020;
    books_db[1].numofborrow = 3;
    books_db[1].is_borrowed = 1; 

    books_db[2].id = 3;
    strcpy(books_db[2].title, "Hamnet");
    strcpy(books_db[2].author, "Maggie");
    books_db[2].year = 2020;
    books_db[2].numofborrow = 1; 
    books_db[2].is_borrowed = 0; 

    books_db[3].id = 4;
    strcpy(books_db[3].title, "TheWish");
    strcpy(books_db[3].author, "Nocholas");
    books_db[3].year = 2021;
    books_db[3].numofborrow = 2;
    books_db[3].is_borrowed = 1; 

    for (int i = 0; i < 4; i++) {
        insert_sorted(&head, books_db[i]);
    }

    fp = fopen("db.dat", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    struct Node *current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(struct book), 1, fp);
        current = current->next;
    }
    
    fclose(fp);
    printf("db.dat file sorted by year (desc) created successfully.\n");

    current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
