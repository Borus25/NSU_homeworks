#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

void init(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int size_linked_list(LinkedList llist) {
    return llist.size;
}

Node* getFirst(LinkedList llist) {
    return llist.head;
}

Node* getLast(LinkedList llist) {
    return llist.tail;
}

Node* getI(LinkedList llist, int i) {
    if (i < 0 || i >= llist.size) {
        return NULL; // или подходящая обработка ошибки
    }
    Node* current = llist.head;
    for (int j = 0; j < i; j++) {
        current = current->next;
    }
    return current;
}

void addNewTail(LinkedList *list, int data) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = data;
    new_node->next = NULL;
    if (!list->size) {
        list->head = new_node;
        list->tail = list->head;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void addNewHead(LinkedList *list, int data) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    if (!list->size) {
        list->tail = new_node;
    }
    list->size++;
}

void addI(LinkedList *list, int data, int n) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = data;
    if (n <= 0) {
        new_node->next = list->head;
        list->head = new_node;
        if (list->size == 0) {
            list->tail = new_node;
        }
    } else if (n >= list->size) {
        new_node->next = NULL;
        if (list->tail) {
            list->tail->next = new_node;
        }
        list->tail = new_node;
    } else {
        Node* current = list->head;
        for (int i = 0; i < n - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    list->size++;
}

void removeHead(LinkedList *list) {
    if (!list->head) return;
    Node* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->size--;
}

void removeTail(LinkedList *list) {
    if (!list->head) return;
    free(list->tail);
    list->size--;
    list->tail = getI(*list, list->size - 1);
    list->tail->next = NULL;
}

void removeI(LinkedList *list, int i) {
    if (i < 0 || i >= list->size) return;
    if (i == 0) {
        removeHead(list);
    }
    if (i == list->size-1) {
        removeTail(list);
    }
    Node* tmp = getI(*list, i + 1);
    Node* current = list->head;
    while (i - 1 != 0) {
        current = current->next;
        i--;
    }
    free(current->next);
    current->next = tmp;
    list->size--;
}

void freeList(LinkedList *list) {
    if (!list->size) return;
    while (list->head->next) {
        removeTail(list);
    }
    removeHead(list);
}

void printLinkedList(const Node *head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    LinkedList linked_list;
    init(&linked_list);

    printf("linked list create\n");
    printf("linked list size: %d\n", size_linked_list(linked_list));
    addNewTail(&linked_list, 10);
    addNewTail(&linked_list, 20);
    addNewTail(&linked_list, 30);
    addNewHead(&linked_list, -10);
    addNewHead(&linked_list, -20);
    addI(&linked_list, 5, 3);

    Node* tail = getLast(linked_list);
    printf("Tail: %d\n", tail->data);
    printf("Head: %d\n", getFirst(linked_list)->data);
    printf("2: %d\n", getI(linked_list, 2)->data);
//    addI(&linked_list, 5, 1);
    printLinkedList(linked_list.head);

    removeTail(&linked_list);
    printLinkedList(linked_list.head);

    addNewTail(&linked_list, 40);
    printLinkedList(linked_list.head);

    tail = getLast(linked_list);
    if (!tail->next) {
        printf("tail next is NULL\n");
    } else {
        printf("tail next is not NULL\n");
    }

    removeI(&linked_list, 3);
    printLinkedList(linked_list.head);

    freeList(&linked_list);
    if (!linked_list.head) {
        printf("head pointer is NULL\n");
    } else {
        printf("head pointer is NOT NULL\n");
    }
    addNewTail(&linked_list, 40);
    printLinkedList(linked_list.head);
    return 0;
}