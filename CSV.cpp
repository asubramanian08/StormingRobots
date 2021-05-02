#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

enum CSV_itemType
{
	str, Int, DOB
}dataType;
int printType;
struct CSV_info
{
	char* lineStart; //where in the peopInfo it is in starts
	char* numInLine; //where it ends;
	char* item;
};
int string(const void* a, const void* b)
{
	CSV_info* p = (CSV_info*)a;
	CSV_info* q = (CSV_info*)b;
	int i = 0;

	while (((p->item[i] != ',') && (q->item[i] != ',')) && ((p->item[i] != '\n') && (q->item[i] != '\n'))) //the loop to compare char by char
	{
		if (p->item[i] != q->item[i])
		{
			if (q->item[i] - p->item[i] > 0)
				return -1 * printType;
			else
				return 1 * printType;
		}
		i++;
	}
	if (p->item[i] == q->item[i])
		return 0;
	else if (q->item[i] == ',' || q->item[i] == '\n')
		return 1 * printType;
	else
		return -1 * printType;
}
int integer(const void* a, const void* b)
{
	CSV_info* p1 = (CSV_info*)a;
	CSV_info* p2 = (CSV_info*)b;

	int total1 = 0;
	int i = 0;
	while ((p1->item[i] != ',') && (p1->item[i] != '\n'))
	{
		total1 = (total1 * 10) + p1->item[i] - '0';
		i++;
	}
	int total2 = 0;
	i = 0;
	while ((p2->item[i] != ',') && (p2->item[i] != '\n'))
	{
		total2 = (total2 * 10) + p2->item[i] - '0';
		i++;
	}
	if (total1 > total2)
		return -1 * printType;
	else if (total1 < total2)
		return 1 * printType;
	else
		return 0;
}
int date(const void* a, const void* b)
{
	CSV_info* p = (CSV_info*)a;
	CSV_info* q = (CSV_info*)b;

	int year1 = ((p->item[6] - '0') * 1000) + ((p->item[7] - '0') * 100) + ((p->item[8] - '0') * 10) + p->item[9] - '0';
	int month1 = (p->item[0] - '0') * 10 + p->item[1] - '0';
	int day1 = (p->item[3] - '0') * 10 + p->item[4] - '0';

	int year2 = ((q->item[6] - '0') * 1000) + ((q->item[7] - '0') * 100) + ((q->item[8] - '0') * 10) + q->item[9] - '0';
	int month2 = (q->item[0] - '0') * 10 + q->item[1] - '0';
	int day2 = (q->item[3] - '0') * 10 + q->item[4] - '0';
	int totalValue = ((year1 * 10000) + (month1 * 100) + day1) - ((year2 * 10000) + (month2 * 100) + day2);
	return totalValue * printType;
}
int (*compare_Description[]) (const void* a, const void* b) =
{
	string,
	integer,
	date
};

long getFileSize(FILE* fp)
{
	if (fp == NULL)
		return -1;
	long fileLen;
	fseek(fp, 0L, SEEK_END);
	fileLen = ftell(fp);
	rewind(fp);
	return fileLen;
}
int findCol(char** inFile_ptr, char* colName, int colNameLen)
{
	int onArgv = 0;
	int colNum = 0;

	while (**inFile_ptr != '\n')
	{
		if (**inFile_ptr == ',')
		{
			colNum++;
			onArgv = 0;
		}
		else if (**inFile_ptr == colName[onArgv]) //if the letter I am looking at is the same is the word I am looking for
		{
			onArgv++;
			if (onArgv == colNameLen)
				break;
		}
		else
			onArgv = 0;
		(*inFile_ptr)++;
	}
	*inFile_ptr = strchr(*inFile_ptr, '\n');
	return colNum;
}
int readCSV_Data(CSV_info **sortThisPtr, int colNum, char* inFile, int maxCount, char sortType)
{
	int colCount = 0;
	int itemNum = 0;

	while (*(inFile + 1) != '\0')
	{
		if (maxCount <= itemNum) //need more space
		{
			maxCount *= 2;
			*sortThisPtr = (CSV_info*)realloc(*sortThisPtr, (maxCount) * sizeof(CSV_info));
		}
		(*sortThisPtr + itemNum)->lineStart = inFile + 1;

		while (colCount < colNum) //get to where the column I need to look at is
		{
			inFile = strchr(inFile + 1, ',');
			colCount++;
		}
		(*sortThisPtr + itemNum)->item = inFile + 1;

		inFile = strchr(inFile + 1, '\n');
		(*sortThisPtr + itemNum)->numInLine = inFile;
		itemNum++;
		colCount = 0;
	}
	return itemNum;
}
void printCSV(const char* fileout, char* peopInfo, int headerLen, int itemNum, CSV_info * sortThis)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileout, "w");
	char* inFile = peopInfo;
	int letter = 0;
	while (letter < headerLen) //print the header
	{
		fputc(*inFile, fp);
		inFile++;
		letter++;
	}
	letter = 0;
	int line = 0;
	while (line < itemNum) //print the rest of the lines in order
	{
		fprintf(fp, "\n");
		char* letter = sortThis[line].lineStart;
		while (letter < sortThis[line].numInLine)
		{
			fprintf(fp, "%c", *letter);
			letter++;
		}
		line++;
	}
	fprintf(fp, "\n");
	fclose(fp);
}
void orderA_CSV(int argc, char argv[][10], const char* file)
{
	FILE* fp = NULL;
	fopen_s(&fp, file, "r");
	long fileLen = getFileSize(fp);
	char* peopInfo = (char*)malloc(fileLen + 1);
	memset(peopInfo, 0, fileLen + 1);
	fread(peopInfo, sizeof(char), fileLen, fp);
	fclose(fp);

	int maxCount = 100;
	CSV_info * sortThis = (CSV_info*)malloc(maxCount * sizeof(CSV_info));
	char* inFile = peopInfo;
	int colNum = findCol(&inFile, argv[1], strlen(argv[1]));
	int headerLen = inFile - peopInfo; //inFile is at the first (/n)
	int itemNum = readCSV_Data(&sortThis, colNum, inFile, maxCount, argv[2][0]);
	qsort(sortThis, itemNum, sizeof(CSV_info), compare_Description[dataType]);

	printCSV(file, peopInfo, headerLen, itemNum, sortThis);
}

int main(void)
{
	char argv[4][10] = { "loadthis", "DOB", "d", "d" }; //to change
	if (argv[2][0] == 's')
		dataType = str;
	else if (argv[2][0] == 'i')
		dataType = Int;
	else if (argv[2][0] == 'd')
		dataType = DOB;
	else
		return 0;

	if (argv[3][0] == 'a')
		printType = 1;
	else if (argv[3][0] == 'd')
		printType = -1;
	else
		return 0;
	orderA_CSV(4, argv, "./inCSV");
	system("pause");
	return 0;
}