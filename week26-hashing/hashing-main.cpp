#include<stdlib.h>
#include<stdio.h>
#include"chainedTableFuncs.cpp"
#include<time.h>

#define MAX_STRLEN 213
#define MAX_CHAR 256
#define HASH_RATIO 1.333333
#define RANDOM(bound) ((unsigned int)((double)bound * (rand() / (RAND_MAX + 1.0))))
unsigned int numOfElements;
unsigned int maxShift = (sizeof(unsigned int) - sizeof(char)) * 8;
bool computerTests;

unsigned long long userNum(void) {
	unsigned long long total = 0;
	unsigned char ch;
	while ((ch = getchar()) != '\n')
		total = (total * 10) + (ch - '0');
	return total;
}
unsigned char* userStr(unsigned int* strLen) {
	unsigned char* str = (unsigned char*)malloc(sizeof(unsigned char) * MAX_STRLEN);
	unsigned char* ch = str;
	while ((*ch = getchar()) != '\n')
		ch++;
	*strLen = ch - str;
	return (unsigned char*)realloc(str, sizeof(unsigned char) * (*strLen));
}
unsigned char* userStr(void) {
	unsigned char* str = (unsigned char*)malloc(sizeof(unsigned char) * MAX_STRLEN);
	unsigned char* ch = str;
	while ((*ch = getchar()) != '\n')
		ch++;
	*ch = '\0';
	return (unsigned char*)realloc(str, sizeof(unsigned char) * (ch - str + 1));
}

struct contInfo {
	unsigned long long pop;
	unsigned char* econ_stat;
	unsigned char* contenent;
	unsigned int timeDiff;
};
struct contName {
	unsigned char* str;
	unsigned int strLen;
};

unsigned int hash(void* id) {
	unsigned int index = 0;
	contName* name = (contName*)id;
	for (unsigned int i = 0; i < name->strLen; i++)
		index ^= ((unsigned int)name->str[i]) << (i % maxShift);
	return index % numOfElements;
}
bool sameId(void* id1, void* id2) {
	contName* n1 = (contName*)id1, * n2 = (contName*)id2;
	if (n1->strLen != n2->strLen)
		return false;
	for (unsigned int i = 0; i < numOfElements; i++)
		if (n1->str[i] != n2->str[i])
			return false;
	return true;
}
void freeItem(void* id, void* info){
	free(((contName*)id)->str);
	free((contName*)id);
	if (!computerTests) {
		free(((contInfo*)info)->econ_stat);
		free(((contInfo*)info)->contenent);
		free((contInfo*)info);
	}
}

void addCont(chainedTable* countries) {
	printf("Enter the coutrey name: ");
	contName* name = (contName*)malloc(sizeof(contName));
	name->str = userStr(&name->strLen);

	contInfo* info = (contInfo*)malloc(sizeof(contInfo));
	printf("Enter the population: ");
	info->pop = userNum();
	printf("Enter the economic status (string): ");
	info->econ_stat = userStr();
	printf("Enter the contenent is in mainly located on (string): ");
	info->contenent = userStr();
	printf("Enter the time change from England (positive hours): ");
	info->timeDiff = userNum();

	(*countries).add(name, info);
}
void remCont(chainedTable* countries) {
	bool worked = false;
	contName* name = (contName*)malloc(sizeof(contName));
	while (!worked) {
		printf("Enter the coutrey name (enter 's' to stop): ");
		name->str = userStr(&name->strLen);
		if ((name->str[0] == 's') && (name->strLen == 1)) {
			free(name->str);
			free(name);
			return;
		}
		worked = (*countries).dsty(name);
		free(name->str);
	}
	free(name);
}
void updtCont(chainedTable* countries) {
	contName* name = (contName*)malloc(sizeof(contName)); contInfo* info;
	do {
		printf("Enter the coutrey name (print 's' to stop): ");
		name->str = userStr(&name->strLen);
		if ((name->str[0] == 's') && (name->strLen == 1))
			return;
		info = (contInfo*)(*countries).updt(name, NULL);
		free(name->str);
	} while (info == NULL);
	free(name);

	printf("The current population is: %llu. \nDo you wish to update it 1 = yes, 0 = no: ", info->pop);
	if (userNum()) {
		printf("enter the new population: ");
		info->pop = userNum();
	}

	printf("The current economic status is: %s. \nDo you wish to update it 1 = yes, 0 = no: ", info->econ_stat);
	if (userNum()) {
		printf("enter the new economic status: ");
		info->econ_stat = userStr();
	}

	printf("The current contenent is: %s. \nDo you wish to update it 1 = yes, 0 = no: ", info->contenent);
	if (userNum()) {
		printf("enter the new contenent: ");
		info->contenent = userStr();
	}

	printf("The current time diffrence(from the prime meridian) is: %u. \nDo you wish to update it 1 = yes, 0 = no: ", info->timeDiff);
	if (userNum()) {
		printf("enter the new time diffrence: ");
		info->timeDiff = userNum();
	}
}
void infoCont(chainedTable* countries) {
	contName* name = (contName*)malloc(sizeof(contName)); contInfo* info;
	do {
		printf("Enter the coutrey name (print 's' to stop): ");
		name->str = userStr(&name->strLen);
		if ((name->str[0] == 's') && (name->strLen == 1))
			return;
		info = (contInfo*)(*countries).updt(name, NULL);
		free(name->str);
	} while (info == NULL);
	free(name);

	printf("The current population is: %llu.\n", info->pop);
	printf("The current economic status is: %s.\n", info->econ_stat);
	printf("The current contenent is: %s.\n", info->contenent);
	printf("The current time diffrence(from the prime meridian) is: %u.\n", info->timeDiff);
}
void maxChain(chainedTable* countries) {
	printf("Maximum chain size: %u\n", (*countries).maxChain());
}
void (*actions[])(chainedTable*) = { addCont, remCont, updtCont, infoCont, maxChain };

int main(void) { //country population
	printf("Are you testing (computer made tests)? 1 = yes, 0 = no: ");
	computerTests = userNum() == 1;
	if (computerTests) { //compter tests: rand name
		srand(time(0)); //for the rand name
		printf("Enter the number of countrys to hash: ");
		unsigned int tests = userNum(); contName* name;
		printf("After how many tests do you want to print the largest chain: ");
		unsigned int printWhen = userNum();
		//initialize the table
		numOfElements = (double)(tests + 1) * HASH_RATIO;
		chainedTable contries(numOfElements, hash, sameId, freeItem);
		//do all the tests
		for (unsigned int i = 0; i < tests; i++) {
			if (i % printWhen == 0)
				printf("The longest chain after %u tests is %u\n", i, contries.maxChain());
			name = (contName*)malloc(sizeof(contName));
			//name->strLen = rand() % MAX_STRLEN;
			name->strLen = 1 + RANDOM(MAX_STRLEN);
			name->str = (unsigned char*)malloc(sizeof(unsigned char) * name->strLen);
			for (unsigned int j = 0; j < name->strLen; j++)
				name->str[j] = RANDOM(MAX_CHAR);
			contries.add(name, NULL);
		}
		printf("The longest chain after %u tests is %u\n", tests, contries.maxChain());

		printf("Would you like to print the chain lengths to a CSV file? (yes = 1, no = 0): ");
		if (userNum() == 1) {
			printf("Enter the CSV file name: ");
			unsigned char* file = userStr();
			FILE* fp = fopen((const char*)file, "w");
			fprintf(fp, "Chain Length,Number of Buckets");
			free(file);
			const unsigned int* chainLengths = contries.listofChains();
			unsigned int maxChainSize = 0;
			for (unsigned int i = 0; i < numOfElements; i++)
				if (chainLengths[i] > maxChainSize)
					maxChainSize = chainLengths[i];
			unsigned int* chainsOfLen = (unsigned int*)calloc(maxChainSize + 1, sizeof(unsigned int));
			for (unsigned int i = 0; i < numOfElements; i++)
				chainsOfLen[chainLengths[i]]++;
			for (unsigned int i = 0; i <= maxChainSize; i++)
				fprintf(fp, "\n%u,%u", i, chainsOfLen[i]);
			free(chainsOfLen);
			printf("File writing finished\n");
			fclose(fp);
		}
		printf("press enter to finish: "); while (getchar() != '\n');
		return 0;
	}
	printf("Enter an estimate on the number of contrys to be hashed: ");
	numOfElements = (double)(userNum() + 1) * HASH_RATIO;
	chainedTable contries(numOfElements, hash, sameId, freeItem);
	unsigned int userAct;
	do {
		printf("\nYou can:\n1: add a country\n2: remove a contry\n3: update informating about a county\n4: Get \
information about a courtry\n5: get the maximum chain size\n0: quit, free, and exit\nEnter your choice here: ");
		userAct = userNum();
		if ((userAct <= 5) && (userAct != 0))
			actions[userAct - 1](&contries);
		else if(userAct != 0)
			printf("Invalid input! Try again\n");
	} while (userAct);
	return 0;
}