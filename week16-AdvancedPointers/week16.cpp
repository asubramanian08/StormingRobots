#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
//advanced pointers
int fibonacci(int n, static int* fibArray)
{
	if ((!fibArray[n]) && (n != 0))
		fibArray[n] = fibonacci(n - 2, fibArray) + fibonacci(n - 1, fibArray);
	return fibArray[n];
}

void asserten(void)
{
	printf("Enter some stuff(assert): ");
	char ch = getchar();
	while (ch != '\n')
	{
		assert(ch != '0');
		ch = getchar();
	}
}

struct  COLOR {
	int r;  int g;  int b;  int hue;
};
void offsetOfStruct(void)
{
	printf("r: %d, g: %d, b: %d, hue: %d\n", offsetof(COLOR, r), offsetof(COLOR, g), offsetof(COLOR, b), offsetof(COLOR, hue));
}

void transpose(int* inputArray, int nRows, int nCols)
{
	int* transposed = (int *)malloc(sizeof(int) * nRows * nCols);
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
			transposed[i * nRows + j] = *(inputArray + j * nCols + i);
	}
	memcpy(inputArray, transposed, nRows * nCols*sizeof(int));
	free(transposed);
}

void multiplyMatrix(int* matrix1, int rows1, int cols1, int* matrix2, int rows2, int cols2, int* product)
{
	assert(cols1 == rows2);
	static int i = 0;
	static int j = 0;
	static int k = -1;
	if ((++k) == cols1)
	{
		k = 0;
		j++;
		if (j == cols2)
		{
			j = 0;
			i++;
			if (i == rows1)
				return;
		}
	}
	*(product + (i * cols2) + j) += (*(matrix1 + (i * cols1) + k)) * (*(matrix1 + (k * cols2) + j));
	multiplyMatrix(matrix1, rows1, cols1, matrix2, rows2, cols2, product);
}

int getNext(char* list, char deliminator)
{
	static char* reading = list;
	static long readLocation = 0;
	int total = 0;
	if (strcmp(reading, list) != 0)
		readLocation = 0;
	while ((list[readLocation] != deliminator) && (list[readLocation] != '\0'))
	{
		total = total * 10 + list[readLocation] - '0';
		readLocation++;
	}
	readLocation++;
	return total;
}

void printDecimal(int num)
{
	if (num)
	{
		printDecimal(num / 10);
		putc((num % 10) + '0', stdout);
	}
}
void printHex(int num)
{
	if (num)
	{
		printHex(num / 16);
		if (num % 16 < 10)
			putc(num % 16 + '0', stdout);
		else
			putc(num % 16 - 10 + 'a', stdout);
	}
}
void printString(char* str)
{
	while (*str != '\0')
	{
		putc(*str, stdout);
		str++;
	}
}
void myPrintf(int argTotals, const char* printStr, ...)
{
	va_list argList;
	int argTotal = 0;
	const char* p = printStr;
	if (*p == '%')
		argTotal++;
	while (p != NULL)
	{
		p = strchr(p + 1, '%');
		if ((p != NULL) && (*(p - 1) != '\\'))
			argTotal++;
	}
	va_start(argList, argTotals);
	va_arg(argList, int);
	p = printStr;
	while(*p != '\0')
	{
		if ((*p != '%') || (*(p - 1) == '\\'))
			putc(*p, stdout);
		else
		{
			p++;
			assert(*p == 'd' || *p == 'x' || *p == 's');
			int i;
			switch (*p) {
			case 'd': ;
				printDecimal(va_arg(argList, int));
				break;
			case 'x':
				printHex(va_arg(argList, int));
				break;
			case 's':
				printString(va_arg(argList, char*));
				break;
			}	
		}
		p++;
	}
}
int main(void)
{	/*int fibArray[100] = { 0, 1 };
	printf("%d", fibonacci(7, fibArray));*/
	//asserten();
	//offsetOfStruct();
	/*int x[][3] = { {1, 2, 3}, {4,5,6}, {7,8,9}, {10, 11, 12} };
	transpose(x[0], 4, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%d, ", *(*x + j + 4*i) );
		printf("\n");
	}*/

/*#define row1 3
#define col1 3
#define row2 col1
#define col2 2


	int x[row1][col1] = { {1,1,1}, {1,1,1}, {1,1,1} };
	int y[row2][col2] = { {1,1}, {1,1}, {1,1} };
	int product[row1][col2] = { 0 };
	multiplyMatrix(x[0], row1, col1, y[0], row2, col2, product[0]);
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col2; j++)
			printf("%d, ", *(*product + j + col2 * i));
		printf("\n");
	}*/
	/*char list[] = "0,,245,7,8,3,8,3,6,2,62";
	int n = 0;
	do {
		n = getNext(list, ',');
		printf("%d ", n);
	} while (1);*/
	//myPrintf(1, "hi this is bob and I am %s years old", "hi");

	system("pause");
	return 0;
}

