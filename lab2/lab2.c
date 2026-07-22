#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENT 100
#define MAX_ID 10

typedef struct {
    char id[MAX_ID];
    int time;
} StackNode;

typedef struct QueueNode {
    char id[MAX_ID];
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    StackNode stack[MAX_EVENT];
    int top, len;
    int n, m, p;
} Park;

void arrival(Park* park, char* id, int time) {
    if (park->top < park->n) {
        strcpy(park->stack[park->top].id, id);
        park->stack[park->top].time = time;
        park->top++;
        printf("P %d\n", park->top);
    } 
    else if (park->len < park->m) {
        park->len++;
        QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
        strcpy(newNode->id, id);
        newNode->next = NULL;
        if (park->rear == NULL) {
            park->front = newNode;
            park->rear = newNode;
        } else {
            park->rear->next = newNode;
            park->rear = newNode;
        }
        printf("W %d\n", park->len);
    } 
    else{
        printf("Parking lot is full. %s cannot enter.\n", id);
    }
}

void departure(Park* park, char* id, int time) {
    int i, stackfound = 0;
    if (park->top > 0) {
        for (i = 0; i < park->top; i++) {
            if (strcmp(park->stack[i].id, id) == 0) {
                stackfound = 1;
                break;
            }
        }
    }

    if (stackfound) {
        int parktime = time - park->stack[i].time;
        printf("%d %d\n", parktime, parktime * park->p);
        for (int j = i; j < park->top - 1; j++) {
            park->stack[j] = park->stack[j + 1];
        }

        if (park->len > 0) {
            QueueNode* temp = park->front;
            strcpy(park->stack[park->top-1].id, temp->id);
            park->stack[park->top-1].time = time;
            park->len--;
            park->front = park->front->next;
            if (park->front == NULL) {
                park->rear = NULL;
            }
            free(temp);
        } else {
            park->top--;
        }
    }
    else {
        QueueNode* prev = NULL;
        QueueNode* curr = park->front;
        while (curr != NULL) {
            if (strcmp(curr->id, id) == 0) {
                printf("%d %d\n", 0, 0);
                if (curr == park->front) {
                    park->front = curr->next;
                } else {
                    prev->next = curr->next;
                }
                if (curr == park->rear) {
                    park->rear = prev;
                }
                free(curr);
                park->len--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        printf("%s is not in the parking lot.\n", id);
    }
}

int main() {
    Park park;
    park.front = NULL;
    park.rear = NULL;
    park.top = 0;
    park.len = 0;
    scanf("%d %d %d", &park.n, &park.m, &park.p);
    
    char event, id[MAX_ID];
    int time;
    for ( ; ; ) {
        scanf(" %c %s %d", &event, id, &time);
        if (event == 'E')  
            break;
        if (event == 'A') 
            arrival(&park, id, time);
        if (event == 'D') 
            departure(&park, id, time);
    }

    while (park.front != NULL) {
        QueueNode* temp = park.front;
        park.front = park.front->next;
        free(temp);
    }

    return 0;
}