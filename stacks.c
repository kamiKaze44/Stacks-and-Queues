#include "employees6.h"
#include <string.h>


// Stack Operations
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

// Saving to binary or txt file
static void saveStackToFile(Node *top, const char *filename) {
    FILE *file;
    if (strstr(filename, ".txt")) {
        file = fopen(filename, "a");
        if (!file) {
            printf("Could not open text file.\n");
            return;
        }
        Node *current = top;
        while (current != NULL) {
            Employee e = current->data;
            fprintf(file, "%d|%s|%s|%d|%d|%.2f|%d|%d|%d|%s\n",
                    e.id, e.name, e.surname,
                    e.education, e.speciality, e.salary,
                    e.startDate.day, e.startDate.month, e.startDate.year,
                    e.status);
            current = current->next;
        }
    } else {
        file = fopen(filename, "ab");
        if (!file) {
            printf("Could not open binary file.\n");
            return;
        }
        Node *current = top;
        while (current != NULL) {
            fwrite(&current->data, sizeof(Employee), 1, file);
            current = current->next;
        }
    }

    if (file) {
        fclose(file);
        printf("Stack successfully saved to %s.\n", filename);
    }
}

static void loadStackFromFile(Node **top, const char *filename) {

    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("Could not open file.\n");
        return;
    }

    Employee e;

    while (fscanf(file,
           "%d|%49[^|]|%49[^|]|%d|%d|%f|%d|%d|%d|%19[^\n]\n",
           &e.id,
           e.name,
           e.surname,
           &e.education,
           &e.speciality,
           &e.salary,
           &e.startDate.day,
           &e.startDate.month,
           &e.startDate.year,
           e.status) == 10) {

        push(top, e);
    }

    fclose(file);

    printf("Stack loaded from %s.\n", filename);
}

// First main
int main(void) {
    Node *stackTop = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n" B "--- STACK MENU ---\n" RE);
        printf("1. Push Employee\n");
        printf("2. Pop Employee\n");
        printf("3. Display Stack\n");
        printf("4. Search Stack\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
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
            case 5:
                printf("Enter filename (e.g., stack.txt or stack.bin): ");
                scanf("%255s", filename);
                getchar();
                saveStackToFile(stackTop, filename);
                break;
            case 6:
                printf("Enter filename: ");
                scanf("%255s", filename);
                getchar();
                loadStackFromFile(&stackTop, filename);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}