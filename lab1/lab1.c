#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrNode;
struct Node {
    int num;
    int data;
    PtrNode next;
};

PtrNode BuildList() {
    int n;
    scanf("%d", &n);
    if (n < 1) return NULL;

    PtrNode head = (PtrNode)malloc(sizeof(struct Node));
    PtrNode current = head;
    head->num = 1;
    scanf("%d", &head->data);

    for (int i = 2; i <= n; i++) {
        PtrNode newNode = (PtrNode)malloc(sizeof(struct Node));
        newNode->num = i;
        scanf("%d", &newNode->data);
        current->next = newNode;
        current = newNode;
    }
    current->next = head; // Make the list circular
    return current; // Return the last node to facilitate circular traversal
}

PtrNode CountOff(PtrNode head, int *m) {
    if (*m < 1) return head; // Invalid count-off number
    if (head->next == head) {
        printf("%d\n", head->num);
        free(head);
        return NULL; // Only one node left
    }

    PtrNode current = head;
    for (int i = 1; i < *m; i++) 
        current = current->next;

    PtrNode toDelete = current->next;
    printf("%d ", toDelete->num);
    current->next = toDelete->next; // Remove the node
    *m = toDelete->data;
    free(toDelete);
    return current; 
}

int main() {
    PtrNode head = BuildList();
    int m;
    scanf("%d", &m);

    while (head != NULL) {
        head = CountOff(head, &m);
    }
    return 0;
}
