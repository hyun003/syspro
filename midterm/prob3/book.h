#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 50

struct book {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int year;
    int numofborrow;
    int is_borrowed;
};

#endif
