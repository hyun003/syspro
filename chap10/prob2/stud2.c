#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main()
{
    int count = 0, id;
    char name[20];
    struct student *p, *head = NULL;

    printf("Enter student ID and name.\n");
    while (scanf("%d %s", &id, name) == 2) {
        p = (struct student *) malloc(sizeof(struct student));
        if (p == NULL) {
            perror("malloc");
            exit(1);
        }
        p->id = id;
        strcpy(p->name, name);
        p->next = head;
        head = p;
    }

    printf("\nStudent list (reverse order)\n");
    p = head;
    while (p != NULL) {
        count++;
        printf("ID: %d Name: %s\n", p->id, p->name);
        p = p->next;
    }

    printf("Total: %d students.\n", count);
    exit(0);
}

