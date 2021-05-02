#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
//Numbers exerecizes: two four ten 
//programing project: 3

//example from book
int openFile(const char *filename) {
	FILE* fp = NULL;
	fopen_s(&fp, filename, "a+"); //remember
	int n;
	if (fp == NULL)
	{
		return -1;
	}
	while (fscanf_s(fp, "%d", &n) != 1)
	{
		if (ferror(fp))
		{
			fclose(fp);
			return -2;
		}
		if (feof(fp))
		{
			fclose(fp);
			return -3;
		}
		fscanf_s(fp, "%*[^\n]");
	}
	fclose(fp);
	return n;
}

int main(void)
{
	//printf("%d\n", openFile("C:\\Users\\Arjun\\Desktop\\test.txt.txt"));
	system("pause");
	return 0;
}