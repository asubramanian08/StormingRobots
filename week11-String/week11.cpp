#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

// used for q1
void getAWord(char *str)
{
	printf("Enter a word: ");
	char ch = getchar();
	while (ch != '\n')
	{
		*str = ch;
		ch = getchar();
		*str++;
	}
	*str = '\0';
}
//chapeter 13 page  number 
//find the highest and lowerset in alfabetical order words
void q1(void)
{
	char word[21];
	char largest[21]; 
	getAWord((char *)largest);
	char smallest[21];
	getAWord((char *)smallest);
	if (strcmp(smallest, largest))
	{
		memcpy(word, smallest, sizeof(word) / sizeof(word[0]));
		memcpy(smallest, largest, sizeof(smallest) / sizeof(smallest[0]));
		memcpy(largest, word, sizeof(largest) / sizeof(largest[0]));
	}
	if (strlen(smallest) == 4)
	{
		printf("highgest: %s, smallest: %s\n", largest, smallest);
		return;
	}
	do
	{
		getAWord((char*)word);
		if(strcmp(smallest, word))
		{
			memcpy(smallest, word, sizeof(smallest) / sizeof(smallest[0]));
		}
		else if (strcmp(word, largest))
		{
			memcpy(largest, word, sizeof(largest) / sizeof(largest[0]));
		}
	} while (strlen(word) != 4);
	printf("highgest: %s, smallest: %s\n", largest, smallest);
}

//online string packact question 1
//print the locations of a phrase
/*void q2(void)
{
	char str[] = "how much wood could a woodchuck chuck if a woodchuck could chuck wood? A woodchuck would chuck as much wood as a woodchuck could if a woodchuck could chuck wood";
	char *p = str;
	do
	{
		p = strstr(p, "wood");
	} while (p != 0 && printf("%p %d\n", p, p - str) && (p = p + 4) );
}*/

//online string packet question 2
//print the location of the last wood
void q3(void)
{
	char str[] = "how much wood could a woodchuck chuck if a woodchuck could chuck wood";
	char *p = str, *q;
	q = 0;
	do
	{
		p = strstr(p, "wood");
		if (p)
		{
			q = p;
			p = p + 4;
		}
		else
		{
			printf("%p\n", q);
		}
	} while (p /*|| (printf("%p\n", str) && 0)*/);
}

//online sting packet question 3
//replace x in a sting for y
/*int q4(char *sentence, char *oldStr, char *newStr)
{
	char mainStr[100] = "";
	char *p = sentence;
	char *q = sentence;
	size_t len = strlen(oldStr);
	int count = 0;
	while (q = strstr(p, oldStr))
	{
		size_t size = q - p;
		strncat(mainStr, p, size);
		strcat(mainStr, newStr);
		p = q + len;
		count++;
	}
	strcat(mainStr, p);
	if (count != 0)
	{
		strncpy(sentence, mainStr, strlen(mainStr) );
	}
	return count;
}*/

//question 4 on online string packet
//eliminate all old string inputs
void q5(char* sentence, char * oldStr)
{
	int len = strlen(oldStr) - 1;
	char output[1000];
	char* p = output;
	char *q = sentence;
	q = strstr(q, oldStr);
	if (!q)
	{
		return;
	}
	q += len;
	memcpy(p, sentence, q - sentence);
	p = p + (q - sentence);
	do
	{
		*p = *q;
		if (memcmp(p - len, oldStr, len + 1) == 0)
		{   
			p = p - len - 1;
		}
		p++;
	}while ( (q < sentence + strlen(sentence)) && (++q));
	memcpy(sentence, output, p - output);
	//printf("%s", sentence);
}

//online string packet question 5
//find the value of a sring if, there is no value return 0, if there is a value return one.
long q6(char *a)
{
	long x = 0;
	char* p = a;
	while ((*p <= '9' && *p >= '0') || *p == ' ')
	{
		if (*p == ' ')
		{
			continue;
		}
		x = (x * 10) + *p - 0;
		if (p < a + strlen(a))
		{
			p++;
		}
		else
		{
		  	break;
		}
	}
	return x;
}
int main(void)
{
	//q1();
	//q2();
	//q3();
	/*char sentence[100] = "ytjtmoofdsfg", newstr[] = "", oldstr[] = "moo";
	printf("%d\n",q4(sentence,oldstr, newstr));
	printf("%s\n", sentence);*/
	char sentence1[] = "the momomomoomooooo farmer had a cow momooo2moo", oldStr[] = "moo";
	q5(sentence1, oldStr);
	//printf("%s\n", sentence1);
	/*char a[100] = "2405974";
	int x;
	x = q6(a);
	printf("%d\n", x);*/
	system("pause");
	return 0;
}
