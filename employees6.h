#ifndef EMPLOYEES6_H
#define EMPLOYEES6_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define B  "\x1b[38;2;135;206;250m"
#define G  "\x1b[38;2;152;251;152m"
#define RO "\x1b[38;2;255;107;107m"
#define RE "\x1b[0m"

// Enums
typedef enum { BACH = 1, MASTER, DOCT } Education;
typedef enum { IT = 1, ACC, CONSTRUCT, HRSPEC, MANAGER } Speciality;

// Date
typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id;
    char name[50];
    char surname[50];
    Education education;
    Speciality speciality;
    double salary;
    Date startDate;
    char status[20];
} Employee;

// Double Link List for stack and queue
typedef struct Node {
    Employee data;
    struct Node *next;
    struct Node *prev;
} Node;

// Helpers
static inline const char* educationStr(Education edu) {
    switch (edu) {
        case BACH:   return "Bachelors Degree";
        case MASTER: return "Masters Degree";
        case DOCT:   return "Doctorate";
        default:     return "Unknown";
    }
}

static inline const char* specialityStr(Speciality spec) {
    switch (spec) {
        case IT:        return "IT Engineer";
        case ACC:       return "Accountant";
        case CONSTRUCT: return "Construction Engineer";
        case HRSPEC:    return "HR Specialist";
        case MANAGER:   return "Manager";
        default:        return "Unknown";
    }
}

static inline void printEduMenu(void) {
    printf("Select Education Level:\n");
    printf(" 1. Bachelors Degree\n");
    printf(" 2. Masters Degree\n");
    printf(" 3. Doctorate\n");
}

static inline void printSpecMenu(void) {
    printf("Select Specialty:\n");
    printf(" 1. IT Engineer\n");
    printf(" 2. Accountant\n");
    printf(" 3. Construction Engineer\n");
    printf(" 4. HR Specialist\n");
    printf(" 5. Manager\n");
}


// Inputs used by both versions
static inline Employee inputEmployee(void) {
    Employee e;
    int ed, sp;

    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    getchar();

    printf("Enter Employee Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = 0;

    printf("Enter Employee Surname: ");
    fgets(e.surname, sizeof(e.surname), stdin);
    e.surname[strcspn(e.surname, "\n")] = 0;

    printEduMenu();
    printf("Choice: ");
    scanf("%d", &ed);
    e.education = (Education)ed;

    printSpecMenu();
    printf("Choice: ");
    scanf("%d", &sp);
    e.speciality = (Speciality)sp;

    printf("Enter Salary: ");
    scanf("%lf", &e.salary);

    printf("Enter Start Date (day month year): ");
    scanf("%d %d %d", &e.startDate.day, &e.startDate.month, &e.startDate.year);
    getchar();

    strcpy(e.status, "Active");
    return e;
}

static inline void printEmployee(Employee e) {
    printf("ID %d | %s %s | %s | %s | %.2f MDL | %02d.%02d.%04d | %s\n",
           e.id, e.name, e.surname,
           educationStr(e.education),
           specialityStr(e.speciality),
           e.salary,
           e.startDate.day, e.startDate.month, e.startDate.year,
           e.status);
}

static inline Node* createNode(Employee e) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf(RO "Memory allocation failed!\n" RE);
        exit(1);
    }
    newNode->data = e;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

#endif