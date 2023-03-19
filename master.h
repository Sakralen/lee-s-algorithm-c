#ifndef MASTER_H
#define MASTER_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>

//#define DEBUG

#ifdef DEBUG
#include "vld.h"
#endif // DEBUG

#define H_DIM 10
#define V_DIM 10

#define RAND_LOW -1
#define RAND_HIGH 3

#define SOURCE_X 0
#define SOURCE_Y 0

#define DEST_X (H_DIM - 1)
#define DEST_Y (V_DIM - 1)

#define MAX_DIST INT_MAX

#endif // !MASTER_H
