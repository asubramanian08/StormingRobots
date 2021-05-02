#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
// chapter 8 page 177 number 6
// print numbers the way computers do
void q1(void)
{
	const int segments[10][9] =
	{ {0,1,0,1,0,1,1,1,1}
	, {0,0,0,0,0,1,0,0,1}
	, {0,1,0,0,1,1,1,1,0}
	, {0,1,0,0,1,1,0,1,1}
	, {0,0,0,1,1,1,0,0,1}
	, {0,1,0,1,1,0,0,1,1}
	, {0,1,0,1,1,0,1,1,1}
	, {0,1,0,0,0,1,0,0,1}
	, {0,1,0,1,1,1,1,1,1}
	, {0,1,0,1,1,1,0,1,1} };
	printf("Enter a number: ");
	char x = getchar();
	int userNumber[10] = { 0 };
	int j = 0;

	//get the users number and count the number of digits
	while (x != '\n')
	{
		userNumber[j] = x - '0';
		x = getchar();
		j++;
	}

	//for each "line" of the output
	for (int z = 0; z < 3; z++)
	{
		//for each number that needs to be printed
		for (int b = 0; b < j; b++)
		{
			//for each character
			for (int k = 3 * z; k < (3 * (z + 1)); k++)
			{
				if (segments[userNumber[b]][k] == 0)
					printf(" ");
				else if (k % 3 == 1)
					printf("_");
				else
					printf("|");
			}
			printf(" ");
		}
		printf("\n");
	}
}
int main(void)
{
	//q1();
	system("pause");
	return 0;
}