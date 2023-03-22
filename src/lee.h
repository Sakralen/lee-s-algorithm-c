#ifndef LEE_H
#define LEE_H

#include "queue.h"

#define NOT_PASSABLE -1
#define MARKS_INIT_VAL -1
#define ROUTE_MARK -2

#define SYM_EMPTY ' '
#define SYM_NOT_PASSABLE '#'
#define SYM_SOURCE 'S'
#define SYM_DEST 'D'
#define SYM_ROUTE '@'
#define SYM_H_BOX '-'
#define SYM_V_BOX '|'

#define STATE_INIT 0
#define STATE_PRETRACE 1
#define STATE_TRACE 2

typedef struct {
	int field_height;
	int field_width;
	int** field;
	int** distMarks;
	int sourceX;
	int sourceY;
	int destX;
	int destY;
	int distance;
} LeeStruct;

extern const int kVonneumannY[4];
extern const int kVonneumannX[4];

void genField(LeeStruct* leeStruct);
void initMarks(LeeStruct* leeStruct);
void printField(LeeStruct* leeStruct, int state);
void clearStruct(LeeStruct* leeStruct);
int canVisit(LeeStruct* leeStruct, int x, int y);
void lee(LeeStruct* leeStruct);
void trace(LeeStruct* leeStruct);

#endif // !LEE_H
