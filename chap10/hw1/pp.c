#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(struct node **top) {
    struct node *temp;
    int value;

    if (*top == NULL) {
        return -1;
    }
    temp = *top;
    value = temp->data;
    *top = temp->next;
    free(temp);
    return value;
}

void printStack(struct node *top) {
    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int main() {
    struct node *top = NULL;
    int num;

    while (scanf("%d", &num) == 1) {
        if (num <= 0) {
            break;
        }
        push(&top, num);
    }

    printStack(top);
    return 0;
}

