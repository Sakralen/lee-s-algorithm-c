#include "master.h"
#include "lee.h"

int main(int argc, char **argv) {
	srand(time(0));

	int field_height = atoi(argv[1]);
	int field_width = atoi(argv[2]);

	LeeStruct leeStruct;
	leeStruct.field_height = field_height;
	leeStruct.field_width = field_width;

#ifndef RANDOM_SRC_DEST
	leeStruct.sourceX = SOURCE_X;
	leeStruct.sourceY = SOURCE_Y;
	leeStruct.destX = DEST_X;
	leeStruct.destY = DEST_Y;
#else
	leeStruct.sourceX = rand() % field_width;
	leeStruct.sourceY = rand() % field_height;
	leeStruct.destX = rand() % field_width;
	leeStruct.destY = rand() % field_height;
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
