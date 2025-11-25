#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*tail == NULL) {
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int delete(struct node **head, struct node **tail)
{
    struct node *temp;
    int value;

    if (*head == NULL) {
        return -1;
    }
    temp = *head;
    value = temp->data;
    *head = temp->next;

    if (*head == NULL)
        *tail = NULL;

    free(temp);
    return value;
}

void printQueue(struct node *head)
{
    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main()
{
    struct node *head = NULL, *tail = NULL;
    int num;

    while (scanf("%d", &num) == 1) {
        if (num <= 0)
            break;
        addq(&head, &tail, num);
    }

    printQueue(head);
    return 0;
}

