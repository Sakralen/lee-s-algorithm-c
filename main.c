#include "master.h"
#include "lee.h"

int main() {
	srand(time(0));

	LeeStruct leeStruct;
#ifndef RANDOM_SRC_DEST
	leeStruct.sourceX = SOURCE_X;
	leeStruct.sourceY = SOURCE_Y;
	leeStruct.destX = DEST_X;
	leeStruct.destY = DEST_Y;
#else
	leeStruct.sourceX = rand() % H_DIM;
	leeStruct.sourceY = rand() % V_DIM;
	leeStruct.destX = rand() % H_DIM;
	leeStruct.destY = rand() % V_DIM;
#endif // !RANDOM_SRC_DEST	
	genField(&leeStruct);
	initMarks(&leeStruct);
	printField(&leeStruct, STATE_INIT);

	lee(&leeStruct);
	printf("Min distance is: %d\n\n", leeStruct.distance);
	if (leeStruct.distance != -1) {
		printField(&leeStruct, STATE_PRETRACE);
		trace(&leeStruct);
		printField(&leeStruct, STATE_TRACE);
	}

	clearStruct(&leeStruct);

	getchar();

	return 0;
}
