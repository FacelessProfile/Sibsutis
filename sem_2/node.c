#include <stdio.h>
#include <stdlib.h>

struct list {
    int data;
    struct list *next;
    struct list *s;
};
typedef struct list node;

node* createNode(int data) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->s = NULL;
    return new_node;
}

void printList(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void addEnd(node *head, int data) {
    node *current = head;
    node *element = createNode(data);
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = element;
}

void AFK(node *head) {
    int data;
    while ((scanf("%d", &data) == 1) && (data != 0)) {
        addEnd(head, data);
    }
    while (getchar() != '\n'); 
}

void freeList(node *head) {
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

node* reverseList(node *head) {
    node *reversed = NULL;
    node *current = head;
    node *last = NULL;
    while (current != NULL) {
        node *new_node = createNode(current->data);
        new_node->next = reversed;
        reversed = new_node;
        if (last == NULL) {
            last = new_node;
        }
        new_node->s = last;
        current = current->next;
    }
    return reversed;
}

int listLength(node *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

node* trimList(node *head, int m) {
    if (m <= 0) {
        freeList(head);
        return NULL;
    }
    node *current = head;
    for (int i = 1; i < m && current != NULL; i++) {
        current = current->next;
    }
    if (current != NULL) {
        node *toFree = current->next;
        current->next = NULL;
        freeList(toFree);
    }
    return head;
}

void updateSPointer(node *head) {
    if (!head) return;
    node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    node *current = head;
    while (current != NULL) {
        current->s = last;
        current = current->next;
    }
}

void updateSForFirst(node *head) {
    while (head != NULL) {
        head->s = NULL;
        head = head->next;
    }
}

/*
 connectLists:
 1. вычислить длины первого и второго списков
 2. определить минимальную длину m
 3. обрезать оба списка до m нод
 4. обновлять поинтер s: для первого списка s=NULL для второго –s указывать на его новый последний узел(после обрезки)
 5. находить конец первого списка и соединять его с началом второго списка
*/
void connectLists(node **firstRef, node **secondRef) {
    int len1 = listLength(*firstRef);
    int len2 = listLength(*secondRef);
    int m = (len1 < len2) ? len1 : len2;

    *firstRef = trimList(*firstRef, m);
    *secondRef = trimList(*secondRef, m);
    updateSForFirst(*firstRef);
    updateSPointer(*secondRef);
    node *curr = *firstRef;
    if (curr == NULL) return;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = *secondRef;
}

void navigate(node *S) {
    node *current = S;
    node *first = S;
    char command;

    printf("Use WASD to move\nR to return to first\nQ to quit\n\n");

    while (1) {
        printf("Current data: %d\n", current->data);
        printf("Enter direction: ");
        scanf(" %c", &command);

        if (command == 'D' || command == 'd') {
            if (current->next) {
                current = current->next;
            } else {
                printf("Reached end of list. Return to start? (Y/N): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y')
                    current = first;
            }
        } else if (command == 'A' || command == 'a') {
            printf("Left movement not implemented.\n");
        } else if (command == 'S' || command == 's') {
            if (current->s) {
                current = current->s;
                printf("Moved to bottom node.\n");
            } else {
                printf("No bottom node available.\n");
            }
        } else if (command == 'W' || command == 'w') {
            printf("Up movement not implemented.\n");
        } else if (command == 'R' || command == 'r') {
            current = first;
            printf("Returned to start.\n");
        } else if (command == 'Q' || command == 'q') {
            printf("Exiting navigation.\n");
            break;
        } else {
            printf("Invalid direction. Use W, A, S, D, R or Q.\n");
        }
    }
}

int main() {
    printf("Input first list (end with 0):\n");
    node *head = createNode(0);
    AFK(head);
    printList(head);

    printf("----------------END--------------\n");
    printf("Input second list (end with 0):\n");
    node *second = createNode(0);
    AFK(second);
    printList(second);

    printf("Reverse the second list:\n");
    node *reversed_second = reverseList(second);
    printList(reversed_second);

    printf("Connecting the first and reversed second lists:\n");
    connectLists(&head, &reversed_second);
    printList(head);

    printf("-----------------Navigation stage----------------\n");
    navigate(head);

    freeList(head);
    freeList(&reversed_second);
    return 0;
}
