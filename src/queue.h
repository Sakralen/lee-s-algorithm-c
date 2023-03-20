#ifndef QUEUE
#define QUEUE

#include "master.h"

typedef struct {
	int x;
	int y;
	int distMark;
} Data;

typedef struct Node {
	Data* data;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct {
	Node head;
	Node tail;
} Queue;

void qinit(Queue* q);
int qempty(Queue* q);
void qpush(Queue* q, int x, int y, int mark);
Data qfront(Queue* q);
void qpop(Queue* q);
void qclear(Queue* q);

#endif // !QUEUE
