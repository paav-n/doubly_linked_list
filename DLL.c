#include <stdio.h>
#include <stdlib.h>


/* self-referential structure */
struct Node {
    int item;
    struct Node *next;
    struct Node *prev;

};

struct List {
    struct Node *head;
    struct Node *tail;
};


struct List DLL_new(){
    /* construct an empty list */
    struct List list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

int DLL_length(struct List *list) {
    /* return the number of items in the list */
    struct Node *p;

    int n = 0;
    for (p = list->head; p != NULL; p = p->next) {
        ++n;
    }
    return n;
}

int DLL_empty(struct List *list) {
    /* return true if the list contains no items */
    return list->head == NULL;
}

int DLL_pop(struct List *list) {
    /* remove and return the first item of the list */
    struct Node *node = list->head;
    int item = node->item;
    list->head = node->next;
    if (DLL_empty(list)) {
        list->tail = NULL;
    }
    free(node);
    return item;
}

int DLL_detach(struct List *list) {
    /* remove and return the last item of the list */
    struct Node *node = list->tail;
    int item = node->item;
    list->tail = node->prev;
    if(list->tail == NULL){
        list->head = NULL;
        free(node);
        return item;
    }
    list->tail->next = NULL;
    if (DLL_empty(list)) {
        list->head = NULL;
    }
    free(node);
    return item;
}

void DLL_clear(struct List *list) {
    /* remove all the items from the list */
    while (!DLL_empty(list)) {
        DLL_pop(list);
    }
}

void DLL_push(struct List *list, int item) {
    /* insert the item at the front of the list */
    struct Node *node = malloc(sizeof(struct Node));
    node->item = item;
    node->next = list->head;
    node->prev = NULL;
    if (DLL_empty(list)) {
        list->tail = node;
    }
    if (list->head != NULL) {
        list->head->prev = node;
    }
    list->head = node;
}

void DLL_append(struct List *list, int item) {
    /* append the item to the end of the list */
    if (DLL_empty(list)) {
        DLL_push(list, item);
    }
    else {
        struct Node *node = malloc(sizeof(struct Node));
        node->item = item;
        node->next = NULL;
        list->tail->next = node;
        node->prev =  list->tail;
        list->tail = node;
    }
}


int main() {
    int i;

    struct List list = DLL_new();
    for (i = 0; i < 5; ++i) {
        DLL_push(&list, i);
        DLL_append(&list, i);

    }

    while (!DLL_empty(&list)) {
        printf("%d\n", DLL_detach(&list));
    }

    return 0;
}