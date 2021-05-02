#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
//online question 11
//primes all the way to user number
void q1(void)
{
	const bool prime = 0;
	const bool comp = !(prime);
	int max = 0;
	printf("Enter a number: ");
	bool list[10001] = { prime };
	char input = getchar();
	while (input != '\n')
	{
		max = (max * 10) + (input - '0');
		input = getchar();
	}
	int goTo = sqrt(max) + 1;
	for (int i = 3; i <= goTo; i += 2)
	{
		if (list[i] == comp)
		{
			continue;
		}
		for (int j = i; (j * i) <= max; j += 2)
		{
			if (list[j] != comp || list[j / i] == prime)
			{
				list[i * j] = comp;
			}
		}
	}
	printf("%d ", 2);
	for (int l = 3; l <= max; l += 2)
	{
		if (list[l] == prime)
		{
			printf("%d ", l);
		}
	}
	printf("\n");
}
//online question 
//number of primes untill user number
void q2(void)
{
	int max = 0;
	int count = 0;
	printf("Enter a number: ");
	bool list[10001] = { 0 };
	list[1] = 1;
	char input = getchar();
	while (input != '\n')
	{
		max = (max * 10) + (input - '0');
		input = getchar();
	}
	for (int i = 3; i <= max; i += 2)
	{
		if (list[i] == 1)
		{
			count++;
			continue;
		}
		for (int j = i; (j * i) <= max; j += 2)
		{
			if ((list[j] == 1) && (j % i != 0))
			{
				continue;
			}
			list[i * j] = 1;
		}
	}
	printf("The number of prime numbers between 0 and %d is %d\n", max, (max - (max / 2)) - count);
}
//online question 13
//drink song from 10 to 0
void q3(void)
{
	for (int i = 10; i > 1; i--)
	{
		printf("%d bottles of drink on the wall, %d bottles of drink!\nSo take one down, pass it around, %d more bottles of drink on the wall!\n", i, i, i - 1);
	}
	printf("! bottle of drink on the wall, 1 bottle of drink!\nSo take one down, pass it around, no more bottles of drink on the wall!\n");
}
//online question 15
//convert base 10 to base 2
void q4(int number)
{
	int newInput = number;
	int ofTen = 0;
	int output[64] = { 0 };
	do
	{
		output[ofTen] = newInput % 2;
		newInput = newInput / 2;
		ofTen++;
	} while (newInput > 0);
	printf("%d(base-10) = ", number); 
	while (ofTen > 0)
	{
		printf("%d", output[ofTen - 1]);
		ofTen--;
	}
	printf("(base-2)\n");
}
//online question 16
void q5(void)
{
	char input[10][100] = { 0 };
	int numValues[10][26] = { 0 };
	int compare[10][26] = { 0 };
	int i = 0;
	printf("Enter the words that you want to see's anagrams. Put a space before the next word: ");
	char ch = getchar();
	int count;
	for (count = 0; ch != '\n'; count++)
	{
		while (ch != ' ' && ch != '\n')
		{
			input[count][i] = ch;
			ch = getchar();
			i++;
		}
		if (ch == ' ')
		{
			ch = getchar( );
		}
		i = 0;
	}
	int k;
	for (int j = 0; j < 10 && input[j][0] != 0; j++)
	{
		k = 0;
		while (input[j][k] != 0 && k < 100)
		{
			numValues[j][input[j][k] - 'a'] += 1;
			k++;
		}
	}
	for(int n = 25; n >= 0; n--)
	{
		compare[0][n] = numValues[0][n];
	}
	printf("%s 1", input[0]);
	int m = 0;
	int compareCount = 1;
	int numberComparing;
	for (int l = 1; l < count; l++)
	{
		numberComparing = 0;
		while (numberComparing < compareCount && m != 26)
		{
			m = 0;
			while (m < 26)
			{
				if (compare[numberComparing][m] != numValues[l][m])
					break;
				m++;
			}
			numberComparing++;
		}
		if (m < 26)
		{
			compareCount++;
			numberComparing++;
			for (int n = 25; n >= 0; n--)
			{
				compare[compareCount -1][n] = numValues[l][n];
			}
		}
		printf("\n%s %d", input[l], numberComparing);
		m = 0;
	}
	printf("\n");
}

int main(void)
{
	q1();
	//q2();
	//q3();
	/*printf("Enter a base-10 number: ");
	int number = 0;
	char i = getchar();
	while ( i != '\n')
	{
		number = (number * 10) + (i - '0');
		i = getchar();
	}
	q4(number);*/
	//q5();
	system("pause");
	return 0;
}