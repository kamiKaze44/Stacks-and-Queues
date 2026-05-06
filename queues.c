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

static void dequeue(Node **front, Node **rear) {
    if (*front == NULL) {
        printf("Queue Underflow! Nothing to dequeue.\n");
        return;
    }

    Node *temp = *front;
    *front = (*front)->next;

    if (*front == NULL)
        *rear = NULL;
    else
        (*front)->prev = NULL;

    printf("Employee %d dequeued.\n", temp->data.id);
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


// Second main
int main(void) {
    Node *queueFront = NULL;
    Node *queueRear  = NULL;
    int choice;
    char filename[256];

    while (1) {
        printf("\n" B "=== QUEUE MENU ===\n" RE);
        printf("1. Simple Enqueue\n");
        printf("2. Priority Enqueue (Highest Salary First)\n");
        printf("3. Dequeue\n");
        printf("4. Display Queue\n");
        printf("5. Search Queue\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) return 0;
        getchar();

        switch (choice) {
            case 1:
                enqueue(&queueFront, &queueRear, inputEmployee());
                break;
            case 2:
                priorityEnqueue(&queueFront, &queueRear, inputEmployee());
                break;
            case 3:
                dequeue(&queueFront, &queueRear);
                break;
            case 4:
                displayQueue(queueFront);
                break;
            case 5: {
                int id;
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                getchar();
                searchQueueById(queueFront, id);
                break;
            }
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}