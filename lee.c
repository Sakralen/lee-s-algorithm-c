#include "master.h"
#include "lee.h"

const int kVonneumannY[] = { 0, 0, 1, -1 };
const int kVonneumannX[] = { 1, -1, 0, 0 };

void genField(LeeStruct* leeStruct) {
	leeStruct->field = (int**)malloc(V_DIM * sizeof(int*));
	for (int i = 0; i < V_DIM; i++) {
		leeStruct->field[i] = (int*)malloc(H_DIM * sizeof(int));
	}

	for (int i = 0; i < V_DIM; i++) {
		for (int j = 0; j < H_DIM; j++) {
			if (i == leeStruct->sourceY && j == leeStruct->sourceX) {
				leeStruct->field[i][j] = RAND_HIGH;
				continue;
			}

			if (i == leeStruct->destY && j == leeStruct->destX) {
				leeStruct->field[i][j] = RAND_HIGH;
				continue;
			}

			leeStruct->field[i][j] = (rand() % (RAND_HIGH - RAND_LOW + 1)) + RAND_LOW;
		}
	}
}

void initMarks(LeeStruct* leeStruct) {
	leeStruct->distMarks = (int**)malloc(V_DIM * sizeof(int*));
	for (int i = 0; i < V_DIM; i++) {
		leeStruct->distMarks[i] = (int*)malloc(H_DIM * sizeof(int));
	}

	for (int i = 0; i < V_DIM; i++) {
		for (int j = 0; j < H_DIM; j++) {
			leeStruct->distMarks[i][j] = MARKS_INIT_VAL;
		}
	}

	leeStruct->distMarks[leeStruct->sourceY][leeStruct->sourceX] = 0;
}

void printField(LeeStruct* leeStruct, int state) {
	for (int i = 0; i < H_DIM + 2; i++) {
		printf("%3c", SYM_H_BOX);
	}
	printf("\n");

	for (int i = 0; i < V_DIM; i++) {
		printf("%3c", SYM_V_BOX);

		for (int j = 0; j < H_DIM; j++) {
			if (i == leeStruct->sourceY && j == leeStruct->sourceX) {
				printf("%3c", SYM_SOURCE);
				continue;
			}

			if (i == leeStruct->destY && j == leeStruct->destX) {
				printf("%3c", SYM_DEST);
				continue;
			}

			if (state == STATE_INIT) {
				if (leeStruct->field[i][j] != NOT_PASSABLE) {
					printf("%3c", SYM_EMPTY);
				}
				else {
					printf("%3c", SYM_NOT_PASSABLE);
				}
				continue;
			}

			if (state == STATE_PRETRACE) {
				if (leeStruct->field[i][j] != NOT_PASSABLE) {
					printf("%3d", leeStruct->distMarks[i][j]);
				}
				else {
					printf("%3c", SYM_NOT_PASSABLE);
				}
				continue;
			}

			if (state == STATE_TRACE) {
				if (leeStruct->field[i][j] != NOT_PASSABLE) {
					if (leeStruct->field[i][j] == ROUTE_MARK) {
						printf("%3c", SYM_ROUTE);
					}
					else {
						printf("%3c", SYM_EMPTY);
					}		
				}
				else {
					printf("%3c", SYM_NOT_PASSABLE);
				}
			}
		}

		printf("%3c", SYM_V_BOX);
		printf("\n");
	}

	for (int i = 0; i < H_DIM + 2; i++) {
		printf("%3c", SYM_H_BOX);
	}

	printf("\n\n");
}

void clearStruct(LeeStruct* leeStruct) {
	for (int i = 0; i < V_DIM; i++) {
		free(leeStruct->field[i]);
	}
	free(leeStruct->field);

	for (int i = 0; i < V_DIM; i++) {
		free(leeStruct->distMarks[i]);
	}
	free(leeStruct->distMarks);
}

int canVisit(LeeStruct* leeStruct, int x, int y) {
	if ((x < 0) || (y < 0) || (x > (H_DIM - 1)) || (y > (V_DIM - 1))) {
		return 0;
	}

	if (leeStruct->field[y][x] == NOT_PASSABLE) {
		return 0;
	}

	return 1;
}

void lee(LeeStruct* leeStruct) {
	Queue q;
	qinit(&q);
	qpush(&q, leeStruct->sourceX, leeStruct->sourceY, 0);

	Data cur;
	int adjX, adjY;

	while (!qempty(&q)) {
		cur = qfront(&q);
		qpop(&q);

		if (cur.x == leeStruct->destX && cur.y == leeStruct->destY) {
			qclear(&q);
			leeStruct->distance = cur.distMark;
			return;
		}

		for (int i = 0; i < 4; i++) {
			adjY = cur.y + kVonneumannY[i];
			adjX = cur.x + kVonneumannX[i];

			if (!canVisit(leeStruct, adjX, adjY)) {
				continue;
			}

			if (leeStruct->distMarks[adjY][adjX] != MARKS_INIT_VAL) {
				continue;
			}

			leeStruct->distMarks[adjY][adjX] = cur.distMark + 1;
			qpush(&q, adjX, adjY, cur.distMark + 1);
		}
	}

	qclear(&q);
	leeStruct->distance = -1;
	return;
}

void trace(LeeStruct* leeStruct) {
	int curX = leeStruct->destX, curY = leeStruct->destY;
	int adjX, adjY;
	int minX, minY, minDist;

	while (!(curX == leeStruct->sourceX && curY == leeStruct->sourceY)) {
		minDist = MAX_DIST;

		for (int i = 0; i < 4; i++) {
			adjY = curY + kVonneumannY[i];
			adjX = curX + kVonneumannX[i];

			if (!canVisit(leeStruct, adjX, adjY)) {
				continue;
			}

			if (leeStruct->distMarks[adjY][adjX] < minDist && leeStruct->distMarks[adjY][adjX] != MARKS_INIT_VAL) {
				minX = adjX;
				minY = adjY;
				minDist = leeStruct->distMarks[adjY][adjX];
			}
		}

		curX = minX;
		curY = minY;
		leeStruct->field[curY][curX] = ROUTE_MARK;	
	} 
}
