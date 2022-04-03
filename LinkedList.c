#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Node {
    float data;
    Node *next;
    Node *previous;
};

typedef struct {
    Node *head;
    Node *tail;
} LinkedList;

Node *newNode(float data) {
    Node *node = malloc(sizeof(Node));

    if (!node) return NULL;

    node->data = data;
    node->next = NULL;
    node->previous = NULL;

    return node;
}

Node *getNext(Node *node) {
    return node ? node->next : node;
}

Node *getPrevious(Node *node) {
    return node ? node->previous : node;
}

Node* deleteNodeAfter(Node *node) {
    if (!node)
        return node;

    Node *next = node->next;
    if (!next) {
        node->next = NULL;

        return node;
    }

    node->next=next->next;
    if (next->next)
        next->next->previous = node;

    free(next);

    return node;
}

Node* deleteNode(Node *node) {
    if (!node)
        return NULL;

    Node* prev = node->previous;
    Node* next = node->next;

    if(next)
        next->previous = prev;

    if(prev)
        prev->next = next;

    free(node);

    return prev;
}

float getData(Node *node) {
    if (node)
        return node->data;
}

Node *searchNode(Node *node, float data) {
    if (!node || node->data == data)
        return node;

    return searchNode(getNext(node), data);
}

Node *insertNodeAfterNode(Node *node, Node *nodeAfter) {
    if(!node)
        return NULL;

    nodeAfter->next = node->next;
    nodeAfter->previous = node;

    if (node->next)
        node->next->previous = nodeAfter;
    node->next = nodeAfter;

    return nodeAfter;
}

Node *insertNodeBeforeNode(Node *node, Node *nodeBefore) {
    nodeBefore->previous = node->previous;
    nodeBefore->next = node;

    if (node->previous)
        node->previous->next = nodeBefore;
    node->previous = nodeBefore;

    return nodeBefore;
}

Node *insertNodeBefore(Node*node, float item) {
    Node* nodeBefore = newNode(item);

    return insertNodeBeforeNode(node, nodeBefore);
}

Node *insertNodeAfter(Node *node, float data) {
    Node *nodeAfter = newNode(data);

    return insertNodeAfterNode(node, nodeAfter);
}


/********** Linked List **************/

LinkedList *newLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));

    list->head = newNode(-1); // sentinel
    list->tail = insertNodeAfter(list->head, -1); // tail sentinel

    return list;
}

Node *getHead(LinkedList *list) {
    return list->head->next;
}

void setTail(LinkedList *list, Node *node) {
    insertNodeAfterNode(list->tail->previous, node);
}

void setHead(LinkedList *list, Node *node) {
    insertNodeAfterNode(list->head, node);
}

void setHeadData(LinkedList *list, float data) {
    setHead(list, newNode(data));
}

Node *getTail(LinkedList *list) {
    return list->tail;
}

void deleteTail(LinkedList *list) {
    if (list->head->next != list->tail)
        deleteNodeAfter(list->tail->previous->previous);
}

void deleteHead(LinkedList *list) {
    if (list->head->next != list->tail)
        deleteNodeAfter(list->head);
}

Node *searchLinkedList(LinkedList *list, float value) {
    return searchNode(getHead(list), value);
}

int isLinkedListEmpty(LinkedList *list) {
    return list->head->next == list->tail;
}

void displayLinkedList(LinkedList *list) {
    if (isLinkedListEmpty(list)) {
        return;
    }

    Node *node = getHead(list);
    do {
        printf(" -> %0.4f", getData(node));
    } while ((node = getNext(node)));

    printf("\n");
}