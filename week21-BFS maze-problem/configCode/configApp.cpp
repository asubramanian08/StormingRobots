#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
#include <assert.h>
typedef unsigned long dimention;
#define range '-'
#define nextItem ';'
//#define 
dimention getNum(char** fp)
{
	dimention total = 0;
	while ((**fp >= '0') && (**fp <= '9')) {
		total = (total * 10) + (**fp - '0');
		(*fp)++;
	}
	return total;
}
int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	if ((argc < 2) || ((fp = fopen(argv[1], "r")) == NULL)) {
		printf("MAIN: incorrent or no location given!!\n");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0L, SEEK_END);
	unsigned long long fileSize = ftell(fp);
	rewind(fp);
	char* inFile = (char*)malloc(sizeof(char) * fileSize);
	fread(inFile, sizeof(char), fileSize, fp);
	fclose(fp);
	char* readPtr = inFile;
	dimention temp;
	const dimention numOfRows = getNum(&readPtr);
	assert((*readPtr == ' ') || (*readPtr == ','));
	readPtr++;
	const dimention numOfCols = getNum(&readPtr);
	assert(*readPtr == '\n');
	readPtr++;
	char** grid = (char**)malloc(sizeof(char*) * ((2 * numOfRows) + 1));
	dimention store = (2 * numOfRows) + 1;
	for (dimention i = 0; i < store; i++) {
		grid[i] = (char*)malloc(((2 * numOfCols) + (i & 1) + 1) * sizeof(char));
		memset(grid[i], ' ', ((2 * numOfCols) + (i & 1) + 1) * sizeof(char));
		grid[i][(2 * numOfCols) + (i & 1)] = '\0';
	}
	dimention rowLow, rowHigh, colLow, colHigh;

	//place the victems
	if (*readPtr != '\n') {
		readPtr--;
		*readPtr = nextItem;
	}
	while (*readPtr == nextItem) {
		readPtr++;
		rowLow = getNum(&readPtr);
		readPtr++;
		if (*(readPtr - 1) == range)
			rowHigh = getNum(&readPtr);
		else {
			rowHigh = rowLow;
			readPtr--;
		}
		assert(*readPtr == ',');
		readPtr++;
		colLow = getNum(&readPtr);
		readPtr++;
		if (*(readPtr - 1) == range)
			colHigh = getNum(&readPtr);
		else {
			colHigh = colLow;
			readPtr--;
		}
		temp = colLow;
		while (rowLow <= rowHigh) {
			while (colLow <= colHigh) {
				grid[2 * rowLow + 1][2 * colLow + 1] = 'X';
				colLow++;
			}
			rowLow++;
			colLow = temp;
		}
	}
	assert(*readPtr == '\n');
	readPtr++;

	//place the left/right walls
	if (*readPtr != '\n') {
		readPtr--;
		*readPtr = nextItem;
	}
	while (*readPtr == nextItem) {
		readPtr++;
		rowLow = getNum(&readPtr); //inclusing
		readPtr++;
		if (*(readPtr - 1) == range)
			rowHigh = getNum(&readPtr); //inclusinve
		else {
			readPtr--;
			rowHigh = rowLow;
		}
		assert(*readPtr == ',');
		readPtr++;
		if (tolower(*readPtr) == 'e') {
			readPtr++;
			colLow = 0;
		}
		else 
			colLow = getNum(&readPtr) + 1; //inclusinve
		assert(*readPtr == range);
		readPtr++;
		if (tolower(*readPtr) == 'e') {
			colHigh = numOfCols + 1;
			readPtr++;
		}
		else 
			colHigh = getNum(&readPtr) + 1; //exclusinve
		//put info into grid
		temp = colLow;
		while (rowLow <= rowHigh) {
			while (colLow < colHigh) {
				grid[2 * rowLow + 1][2 * colLow] = '|';
				colLow++;
			}
			rowLow++;
			colLow = temp;
		}
	}
	assert(*readPtr == '\n');
	readPtr++;

	//place the top/bottem walls
	if (*readPtr != '\n') {
		readPtr--;
		*readPtr = nextItem;
	}
	while (*readPtr == nextItem) {
		readPtr++;
		if (*readPtr == 'e') {
			readPtr++;
			rowLow = 0;
		}
		else 
			rowLow = getNum(&readPtr) + 1; 
		assert(*readPtr == range);
		readPtr++;
		if (*readPtr == 'e') {
			readPtr++;
			rowHigh = numOfRows + 1;
		}
		else
			rowHigh = getNum(&readPtr) + 1; 
		assert(*readPtr == ',');
		readPtr++;
		colLow = getNum(&readPtr);
		readPtr++;
		if (*(readPtr - 1) == range)
			colHigh = getNum(&readPtr);
		else {
			readPtr--;
			colHigh = colLow;
		}
		temp = colLow;
		while (rowLow < rowHigh) {
			while (colLow <= colHigh) {
				grid[2 * rowLow][2 * colLow + 1] = '_';
				colLow++;
			}
			rowLow++;
			colLow = temp;
		}
	}
	assert(*readPtr == '\n');
	free(inFile);
	
	//open the grid file
	fp = NULL;
	if (argc >= 3) {
		if ((fp = fopen(argv[2], "w")) == NULL) {
			printf("MAIN: User error -> invaled location for the grid location\n");
			//clean up
			store = 2 * numOfRows + 1;
			for (dimention i = 0; i < store; i++)
				free(grid[i]);
			free(grid);

			exit(EXIT_FAILURE); //exit
		}
	}
	else
		fp = fopen("grid.txt", "w");
	store = 2 * numOfRows + 1;
	//free and print grid[i] for all i
	for (dimention i = 0; i < store; i++) {
		fprintf(fp, "%s\n", grid[i]);
		free(grid[i]);
	}
	fclose(fp);
	free(grid);
	return 0;
}