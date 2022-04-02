//
// Created by Fadi Sarwat on 19/03/2022.
//

#ifndef LECTURE_5_LINKEDLIST_H
#define LECTURE_5_LINKEDLIST_H

typedef struct Node Node;
struct Node {
    float data;
    Node *next;
    Node *previous;
};

Node *newNode(float data);

Node *searchNode(Node *node, float data);

Node *insertNodeAfter(Node *node, float data);

Node *insertNodeBefore(Node *node, float data);

Node *getNext(Node *node);

float getData(Node *node);

Node *getPrevious(Node *node);

void deleteNodeAfter(Node *node);

Node* deleteNode(Node *node);

typedef struct LinkedList LinkedList;

LinkedList *newLinkedList();

void setHead(LinkedList *list, Node *node);

void setHeadData(LinkedList *list, float data);

void setTail(LinkedList *list, Node *node);

Node *getHead(LinkedList *list);

Node *getTail(LinkedList *list);

float isLinkedListEmpty(LinkedList *list);

Node *searchLinkedList(LinkedList *list, float value);

void deleteTail(LinkedList *list);

void displayLinkedList(LinkedList *list);

#endif //LECTURE_5_LINKEDLIST_H
