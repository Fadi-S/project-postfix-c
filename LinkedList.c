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

void deleteNodeAfter(Node *node) {
    if (!node)
        return;

    Node *next = getNext(node);
    if (!next)
        return;

    node->next = getNext(next);
    node->next->previous = next->previous;

    free(next);
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

LinkedList *newLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));

    list->head = newNode(-1); // sentinel
    list->head->next = NULL;
    list->tail = NULL;

    return list;
}

Node *getHead(LinkedList *list) {
    return list->head->next;
}

void setTail(LinkedList *list, Node *node) {
    if (list->tail) {
        list->tail = insertNodeAfterNode(list->tail, node);

        return;
    }


    list->tail = insertNodeAfterNode(getHead(list), node);
}

void setHead(LinkedList *list, Node *node) {
    if (list->tail == NULL) {
        list->tail = node;

        list->tail->next = NULL;
        list->tail->previous = list->head;
    }

    insertNodeAfterNode(list->head, node);
}

void setHeadData(LinkedList *list, float data) {
    setHead(list, newNode(data));
}

Node *getTail(LinkedList *list) {
    return list->tail;
}

void deleteTail(LinkedList *list) {
    deleteNode(getTail(list));
}

Node *searchLinkedList(LinkedList *list, float value) {
    return searchNode(getHead(list), value);
}

int isLinkedListEmpty(LinkedList *list) {
    return !getHead(list);
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