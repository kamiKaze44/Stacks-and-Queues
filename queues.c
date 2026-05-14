#include "employees6.h"
#include <string.h>

// Queue operations
static void enqueue(Node **front, Node **rear, Employee e) {
    Node *newNode = createNode(e);

    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        newNode->prev = *rear;
        *rear = newNode;
    }

    printf("Employee %d enqueued.\n", e.id);
}

// Priority enqueue by salary
static void priorityEnqueue(Node **front, Node **rear, Employee e) {
    Node *newNode = createNode(e);

    if (*front == NULL) {
        *front = *rear = newNode;
        printf("Employee %d priority enqueued.\n", e.id);
        return;
    }

    if (e.salary > (*front)->data.salary) {
        newNode->next = *front;
        (*front)->prev = newNode;
        *front = newNode;
        printf("Employee %d priority enqueued.\n", e.id);
        return;
    }

    Node *current = *front;
    while (current->next != NULL &&
           current->next->data.salary >= e.salary) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL)
        current->next->prev = newNode;
    else
        *rear = newNode;

    current->next = newNode;

    printf("Employee %d priority enqueued.\n", e.id);
}

static void dequeueFront(Node **front, Node **rear) {

    if (*front == NULL) {
        printf("Queue Underflow!\n");
        return;
    }

    Node *temp = *front;

    *front = (*front)->next;

    if (*front == NULL)
        *rear = NULL;
    else
        (*front)->prev = NULL;

    printf("Employee %d dequeued from front.\n",
           temp->data.id);

    free(temp);
}
static void enqueueFront(Node **front,
                         Node **rear,
                         Employee e) {

    Node *newNode = createNode(e);

    if (*front == NULL) {
        *front = *rear = newNode;
    } else {
        newNode->next = *front;
        (*front)->prev = newNode;
        *front = newNode;
    }

    printf("Employee %d inserted at front.\n",
           e.id);
}
static void dequeueRear(Node **front,
                        Node **rear) {

    if (*rear == NULL) {
        printf("Queue Underflow!\n");
        return;
    }

    Node *temp = *rear;

    *rear = (*rear)->prev;

    if (*rear == NULL)
        *front = NULL;
    else
        (*rear)->next = NULL;

    printf("Employee %d removed from rear.\n",
           temp->data.id);

    free(temp);
}
static void displayQueue(Node *front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\n--- Queue Contents (Front to Rear) ---\n");
    Node *current = front;
    while (current != NULL) {
        printEmployee(current->data);
        current = current->next;
    }
}

static void searchQueueById(Node *front, int id) {
    Node *current = front;
    int pos = 1;

    while (current != NULL) {
        if (current->data.id == id) {
            printf("Found employee ID %d at position %d (from front).\n",
                   id, pos);
            printEmployee(current->data);
            return;
        }
        current = current->next;
        pos++;
    }

    printf("Employee ID %d not found in Queue.\n", id);
}
static void saveQueueToFile(Node *front, const char *filename) {
    FILE *file;
    if (strstr(filename, ".txt")) {
        file = fopen(filename, "w");
        if (!file) {
            printf("Could not open text file.\n");
            return;
        }
        Node *current = front;
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
        file = fopen(filename, "wb");
        if (!file) {
            printf("Could not open binary file.\n");
            return;
        }
        Node *current = front;
        while (current != NULL) {
            fwrite(&current->data, sizeof(Employee), 1, file);
            current = current->next;
        }
    }

    if (file) {
        fclose(file);
        printf("Queue successfully saved to %s.\n", filename);
    }
}
static void loadQueueFromFile(Node **front, Node **rear,
                              const char *filename) {

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

        enqueue(front, rear, e);
    }

    fclose(file);

    printf("Queue loaded from %s.\n", filename);
}
// Second main
int main(void) {
    Node *queueFront = NULL;
    Node *queueRear  = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n" B "--- QUEUE MENU ---\n" RE);
        printf("1. Simple Enqueue\n");
        printf("2. Priority Enqueue (Highest Salary First)\n");
        printf("3. Dequeue\n");
        printf("4. Enqueue Front (Deque)\n");
        printf("5. Dequeue Rear (Deque)\n");
        printf("6. Display Queue\n");
        printf("8. Save to File\n");
        printf("9. Load from File\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        getchar();

        switch (choice) {
            case 1:
                enqueue(&queueFront,
                        &queueRear,
                        inputEmployee());
                break;
            case 2:
                priorityEnqueue(&queueFront,
                                &queueRear,
                                inputEmployee());
                break;
            case 3:
                dequeueFront(&queueFront,
                             &queueRear);
                break;
            case 4:
                enqueueFront(&queueFront,
                             &queueRear,
                             inputEmployee());
                break;
            case 5:
                dequeueRear(&queueFront,
                             &queueRear);
                break;
            case 6:
                displayQueue(queueFront);
                break;
            case 7: {
                int id;
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                getchar();
                searchQueueById(queueFront, id);
                break;
            }
            case 8:
                printf("Enter filename: ");
                scanf("%255s", filename);
                getchar();
                saveQueueToFile(queueFront,
                                filename);
                break;
            case 9:
                printf("Enter filename: ");
                scanf("%255s", filename);
                getchar();
                loadQueueFromFile(&queueFront,
                                  &queueRear,
                                  filename);

                break;
            case 0:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}