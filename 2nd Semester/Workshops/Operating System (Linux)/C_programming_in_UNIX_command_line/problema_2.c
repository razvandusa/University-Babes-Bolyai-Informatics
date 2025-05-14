#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Data structure used for this will be linked list
 */
struct node {
    char *name;
    struct node *next;
};

/*
 * known verify if a node with the name is already registered
 * return 0 : not registered
 * return 1 : registered
 */
int known(char *name, struct node *head) {
    struct node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name,name) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/*
 * addNode adds a node in the linked list and it returns the new linked list
 * return struct node *newLinkedList
 */
struct node* addNode(char *name, struct node *head) {
    // Create new node and initialize it
    struct node *newNode = malloc(sizeof(struct node));
    newNode->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newNode->name,name);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return head;
    }

    struct node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

/*
 * freeList will free the memory alocated for the linked list
 * return None
 */
void freeList(struct node *head) {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

int main () {
    struct node *head = NULL;
    size_t lenght;
    char *name;
    printf("Type your name : ");
    while(getline(&name, &lenght, stdin) != -1) {
        if (known(name, head) == 1) {
            printf("Hello again %s",name);
        } else {
            head = addNode(name, head);
            printf("Hello %s",name);
        }
        printf("Type your name : ");
    }
    freeList(head);

    return 0;
}