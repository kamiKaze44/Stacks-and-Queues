#include "employees6.h"
#include <string.h>

/* ----- STACK OPERATIONS (Top = head of list) ----- */

static void push(Node **top, Employee e) {
    Node *newNode = createNode(e);

    if (*top != NULL) {
        newNode->next = *top;
        (*top)->prev = newNode;
    }
    *top = newNode;

    printf("Employee %d pushed to Stack.\n", e.id);
}

static void pop(Node **top) {
    if (*top == NULL) {
        printf("Stack Underflow! Nothing to pop.\n");
        return;
    }

    Node *temp = *top;
    *top = (*top)->next;
    if (*top != NULL)
        (*top)->prev = NULL;

    printf("Employee %d popped from Stack.\n", temp->data.id);
    free(temp);
}

static void displayStack(Node *top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("\n--- Stack Contents (Top to Bottom) ---\n");
    Node *current = top;
    while (current != NULL) {
        printEmployee(current->data);
        current = current->next;
    }
}

static void searchStackById(Node *top, int id) {
    Node *current = top;
    int pos = 1;

    while (current != NULL) {
        if (current->data.id == id) {
            printf("Found employee ID %d at position %d (from top).\n",
                   id, pos);
            printEmployee(current->data);
            return;
        }
        current = current->next;
        pos++;
    }
    printf("Employee ID %d not found in Stack.\n", id);
}




// First main
int main(void) {
    Node *stackTop = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n" B "   STACK MENU   \n" RE);
        printf("1. Push Employee\n");
        printf("2. Pop Employee\n");
        printf("3. Display Stack\n");
        printf("4. Search Stack\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        getchar();

        switch (choice) {
            case 1:
                push(&stackTop, inputEmployee());
                break;
            case 2:
                pop(&stackTop);
                break;
            case 3:
                displayStack(stackTop);
                break;
            case 4: {
                int id;
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                getchar();
                searchStackById(stackTop, id);
                break;
            }
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}