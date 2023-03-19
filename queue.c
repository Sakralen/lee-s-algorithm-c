#include "queue.h"

void qinit(Queue* q) {
	q->head.next = &q->tail;
	q->tail.next = NULL;

	q->head.prev = NULL;
	q->tail.prev = &q->head;

	q->head.data = NULL;
	q->tail.data = NULL;
}

int qempty(Queue* q) {
	if (q->head.next == &q->tail) {
		return 1;
	}
	
	return 0;
}

void qpush(Queue* q, int x, int y, int mark) {
	Node* toPush = (Node*)malloc(sizeof(Node));
	Data* data = (Data*)malloc(sizeof(Data));

	data->x = x;
	data->y = y;
	data->distMark = mark;

	toPush->data = data;
	
	toPush->next = &q->tail;
	toPush->prev = q->tail.prev;
	toPush->prev->next = toPush;
	q->tail.prev = toPush;
}

Data qfront(Queue* q) {
	if (!qempty(q)) {
		return *q->head.next->data;
	}
}

void qpop(Queue* q) {
	if (!qempty(q)) {
		Node* toPop = q->head.next;
		q->head.next = toPop->next;
		toPop->next->prev = &q->head;

		free(toPop->data);
		free(toPop);
	}
}

void qclear(Queue* q) {
	while (!qempty(q)) {
		qpop(q);
	}
}
