#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>

int getnum(void)
{
	int num = 0;
	char enter;
	while ((enter = getchar()) != '\n')
	{
		num = (num * 10) + enter - '0';
	}
	return num;
}
// chapter 7 page 157 question 2
void q1(void)
{
	int i, n;
	char enter;
	n = 0;
	printf("This program prints a table of squares .\n");
	printf("Enter number of entries in table:  ");
	n = getnum();
	for (i = 1; i <= n; i++)
	{
		printf("%10d%10d\n", i, i * i);
		if (i % 24 == 0)
		{
			printf("Press Enter to continue... \n");
			while ((enter = getchar()) != '\n');
		}
	}
}
// chapter 7 page 157 question 4 redo
void q2(void)
{
	printf("Enter phone number: ");
	char enter = getchar();
	while (enter != '\n')
	{
		if (enter <= 'Y' && enter >= 'A')
		{
			if (enter > 'Q')
			{
				enter--;
			}
			int number = (enter - 'A') / 3;
			number += 2;
			printf("%d", number);
		}
		else
		{
			putchar(enter);
		}
		enter = getchar();
	}
}
// chapter 7 page 158 question 7
void q3(void)
{
	printf("Enter your two fractions and the operation you want to do between them: \n");
	int num1, num2, denom1, denom2;
	char operation;
	scanf_s("%d/%d%c%d/%d", &num1, &denom1, &operation, &num2, &denom2);
	if (operation = '+')
	{
		printf("%d/%d", (num1 * denom2) + (num2 * denom1), denom1 * denom2);
	}
	else if (operation = '-')
	{
		printf("%d/%d", (num1 * denom2) - (num2 * denom1), denom1 * denom2);
	}
	else if (operation = '*')
	{
		printf("%d/%d", num1 * num2, denom1 * denom2);
	}
	else
	{
		printf("%d/%d", num1 * denom2, denom1 * num2);
	}

}
// chapter 7 page 158 question 8
void q4(void)
{
	printf("Enter a time: ");
	int isHour, hour1, min1, total;
	char input = getchar();
	isHour = true;
	hour1 = 0;
	min1 = 0;
	while (input != '\n')
	{
		if (input >= '0' && input <= '9')
		{
			int number = input - '0';
			if (isHour == true)
			{
				hour1 = (hour1 * 10) + number;
			}
			else
			{
				min1 = (min1 * 10) + number;
			}
		}
		else if (input == ':')
		{
			isHour = false;
		}
		else if (toupper(input) <= 'Z' && toupper(input) >= 'A')
		{
			input = toupper(input);
			if (input == 'P' && input != 12)
			{
				hour1 += 12;
			}
		}
		input = getchar();
	}
	total = (hour1 * 60) + min1;
	int current = (abs)(total - 480);
	if (current <= abs(total - 583))
	{
		printf("Closest departure time is 8:00 a.m., arriving at 10:16 a.m. \n");
		return;
	}
	else if (abs(total - 583) <= abs(total - 679))
	{
		printf("Closest departure time is 9:43 a.m., arriving at 11:52 a.m. \n");
		return;
	}
	else if (abs(total - 679) <= abs(total - 767))
	{
		printf("Closest departure time is 11:19 a.m., arriving at 1:31 p.m. \n");
		return;
	}
	else if (abs(total - 767) <= abs(total - 840))
	{
		printf("Closest departure time is 12:47 p.m., arriving at 3:00 p.m. \n");
		return;
	}
	else if (abs(total - 840) <= abs(total - 945))
	{
		printf("Closest departure time is 2:00 p.m., arriving at 4:08 p.m. \n");
		return;
	}
	else if (abs(total - 945) <= abs(total - 1140))
	{
		printf("Closest departure time is 3:45 p.m., arriving at 5:55 p.m. \n");
		return;
	}
	else if (abs(total - 1140) <= abs(total - 1305))
	{
		printf("Closest departure time is 7:00 p.m., arriving at 9:20 p.m. \n");
		return;
	}
	else
	{
		printf("Closest departure time is 9:45 p.m., arriving at 11:58 p.m. \n");
		return;
	}

}
// chapter 7 page 158 question 12
void q5(void)
{
	printf("Enter an expression: ");
	float countDec = 0;
	float num1 = 0.0;
	float num2 = 0.0;
	char oper = '+';
	char input;
	while (input = getchar())
	{
		if ((input - '0') >= 0 && (input - '0') <= 9)
		{
			
			if (countDec == 0)
			{
				num2 = (num2 * 10) + int(input - '0');
			}
			else if (countDec != 0)
			{
				num2 = num2 + (float(input - '0') * countDec);
				countDec /= 10;
			}
			continue;
		}
		else if (input == '.')
		{
			countDec = 0.1;
			continue;
		}
		switch (oper)
		{
		case '+': num1 = num1 + num2;
			num2 = 0;
			break;
		case '-': num1 = num1 - num2;
			num2 = 0;
			break;
		case '/': num1 = num1 / num2;
			num2 = 0;
			break;
		case '*': num1 = num1 * num2;
			num2 = 0;
			break;
		}
		oper = input;
		if (input == '\n')
		{
			break;
		}
	}
	printf("Value of expression: %f \n", num1);
}
// chapter 7 page 159 question 14
void q6(void)
{
	printf("enter a positive number: ");
	int square;
	double y = 0.0;
	double newY = 1.0;
	scanf_s("%d", &square);
	while (fabs(y - newY) >= .00001 * y)
	{
		y = newY;
		newY = ((square / y) + y) / 2;
	}
	printf("Square root: %lf \n", newY);
}
int main(void)
{
	//q1();
	//q2();
	//q3();
	//q4();
	q5();
	//q6();
	system("pause");
	return 0;
}