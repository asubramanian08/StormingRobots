#include <stdio.h>
# include <stdlib.h>

int main2(void)
{
	int height, length, width, volume, weight;
	printf("Enter height of the box:");
	scanf_s("%d", &height);
	printf("Enter length of the box:");
	scanf_s("%d", &length);
	printf("Enter width of the box:");
	scanf_s("%d", &width);
	volume = height * length * width  ;
	weight = (volume + 165) / 166;

	printf("Volume (cubic inches) : %d\n", volume);
	printf("Dimensional weight (pounds) :  %d\n", weight);
	system("pause");
	return 0;
}
