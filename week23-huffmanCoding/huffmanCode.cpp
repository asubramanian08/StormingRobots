#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"
#include <limits.h>
#define MAX_CHAR (UCHAR_MAX + 1)
#ifdef pQue_test
#undef pQue_test
#endif // pQue_test
typedef unsigned int frequency;
struct huffman
{
	unsigned char whichChar;
	frequency timesRepeted;
	huffman* lChild;
	huffman* rChild;
};
FILE* checkFile(const char* fileName, const char* fileMode)
{
	FILE* fp = fopen(fileName, fileMode);
	if (!fp) {
		printf("FILE I/O error has occered\n\
1: Check that the input/output files exist\n\
2: Ensure that no other programs are using the files\n\
3: Remember to put the mode ('d' - decompression, 'c' - compression, 'i' - instructions).\n\
It might have messed up ordering of mode/input/output strings.\n\
If you need furthar instructions on how to operate this compression/decompression algorithum run the code with mode i\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}
bool compareFunc_minHeap(const void* p1, const void* p2)
{
	return ((huffman*)p1)->timesRepeted < ((huffman*)p2)->timesRepeted;
}
huffman* buildTree(void)
{
	huffman* rightChild;
	huffman* parent = (huffman*)malloc(sizeof(huffman));
	huffman* leftChild = (huffman*)pQue_deque(sizeof(huffman), compareFunc_minHeap);
	while (rightChild = (huffman*)pQue_deque(sizeof(huffman), compareFunc_minHeap)) {
		parent->lChild = leftChild;
		parent->rChild = rightChild;
		parent->timesRepeted = leftChild->timesRepeted + rightChild->timesRepeted;
		parent->whichChar = 0;
		pQue_enque(parent, sizeof(huffman), compareFunc_minHeap);

		leftChild = (huffman*)pQue_deque(sizeof(huffman), compareFunc_minHeap);
	}
	return leftChild;
}
#define	isLeaf(currNode) (currNode->lChild == NULL)

struct bits
{
	unsigned long long num;
	unsigned short numOfBits;
};
inline void enqueFreqTable(frequency* freqTable)
{
	huffman* newNode = (huffman*)malloc(sizeof(huffman));
	unsigned char counter = 0;
	do {
		if (freqTable[counter]) {
			newNode->lChild = NULL;
			newNode->rChild = NULL;
			newNode->timesRepeted = freqTable[counter];
			newNode->whichChar = counter;
			pQue_enque(newNode, sizeof(huffman), compareFunc_minHeap);
		}
	} while (++counter != 0); //keep it from getting to 256
}
void traverseTree(huffman* huffman_tree, bits* conversion, unsigned short depth, unsigned long long number)
{
	if (isLeaf(huffman_tree))
		conversion[huffman_tree->whichChar] = { number, depth };
	else {
		traverseTree(huffman_tree->lChild, conversion, depth + 1, (number << 1) | 1);
		traverseTree(huffman_tree->rChild, conversion, depth + 1, number << 1);
	}
	free(huffman_tree); //clean up -> don't need the tree anymore
}
inline void fillBiteArray(unsigned char* compressedData, bits* conversion, FILE* fp, frequency * currChar, char* bitsLeft)
{
	unsigned char ch; unsigned short temp; *currChar = 0; *bitsLeft = CHAR_BIT;
	while ((ch = fgetc(fp)) != (unsigned char)EOF) {
		if (*bitsLeft < conversion[ch].numOfBits) { //i need to split it in more than one element
			compressedData[*currChar] |= conversion[ch].num >> (temp = conversion[ch].numOfBits - *bitsLeft);
			while (temp > CHAR_BIT) // for when it needs to reach more that 2 elements
				compressedData[++(*currChar)] |= conversion[ch].num >> (temp -= CHAR_BIT);
			compressedData[++(*currChar)] |= conversion[ch].num << (*bitsLeft = CHAR_BIT - temp);
		}
		else
			compressedData[*currChar] |= conversion[ch].num << (*bitsLeft -= conversion[ch].numOfBits);
	}
}
#define DEFAULT_BINARY_FILE "compressed.bin"
inline void finalWriting(frequency* freqTable, frequency currChar, char bitsLeft, unsigned char* compressedData, FILE* fp)
{
	unsigned char counter = 0;
	//write out the frequency table
	do {
		if (freqTable[counter]) {
			fwrite(freqTable + counter, sizeof(frequency), 1, fp); //frequency
			fwrite(&counter, sizeof(unsigned char), 1, fp); //charactor
		}
	} while (++counter != 0); //keep it from getting to 256
	fwrite(&(*freqTable = 0), sizeof(frequency), 1, fp); //imply an ending of freqTable
	free(freqTable);
	//write out compressed table + metadata
	currChar++;
	fwrite(&currChar, sizeof(frequency), 1, fp);
	fwrite(&bitsLeft, sizeof(char), 1, fp);
	fwrite(compressedData, sizeof(char), currChar, fp);
	free(compressedData);
}
void compression(const char* inputFile, const char* outputFile)
{
	//get the frequencyTable
	FILE* fp = checkFile(inputFile, "r");
	frequency* freqTable = (frequency*)calloc(MAX_CHAR, sizeof(frequency));
	unsigned char ch;
	while ((ch = fgetc(fp)) != (unsigned char)EOF)
		freqTable[ch]++;
	fclose(fp);

	enqueFreqTable(freqTable); //enque all valed node into priority que
	//get the tree
	huffman* huffman_tree = buildTree();
	if (!huffman_tree) { //check
		printf("NOTHING in file!!!\n");
		exit(EXIT_FAILURE);
	}
	doneWith_pQue(); //free the pQue

	//form conversion to bits
	bits* conversion = (bits*)malloc(sizeof(bits) * MAX_CHAR);
	const frequency MAX_SPACE = huffman_tree->timesRepeted << 1;
	traverseTree(huffman_tree, conversion, 0, 0); //fills the conversion + frees huffman tree
											  
	//write the data into a char array
	fp = checkFile(inputFile, "r");
	unsigned char* compressedData = (unsigned char*)calloc(MAX_SPACE, sizeof(unsigned char));
	frequency currChar; char bitsLeft;
	fillBiteArray(compressedData, conversion, fp, &currChar, &bitsLeft);
	fclose(fp); //close the input file after reading a second time
	free(conversion);

	//write tp file
	if(outputFile)
		fp = checkFile(outputFile, "wb");
	else
		fp = checkFile(DEFAULT_BINARY_FILE, "wb");
	finalWriting(freqTable, currChar, bitsLeft, compressedData, fp);
	fclose(fp);
}

inline void enque_items(FILE* fp)
{
	huffman* newNode = (huffman*)malloc(sizeof(huffman));
	newNode->lChild = NULL; newNode->rChild = NULL;
	fread(&newNode->timesRepeted, sizeof(frequency), 1, fp);
	while (newNode->timesRepeted) {
		fread(&newNode->whichChar, sizeof(unsigned char), 1, fp);
		pQue_enque(newNode, sizeof(huffman), compareFunc_minHeap);
		fread(&newNode->timesRepeted, sizeof(frequency), 1, fp);
	}
	free(newNode);
}
#define DEFAULT_TEXT_FILE "file.txt"
inline void printToFile(frequency numCompressedBytes, huffman* huffman_tree, FILE* fp, unsigned char* compressedData, char lastBit)
{
	frequency currChar = 0;
	char currBit = CHAR_BIT - 1;
	huffman* currSpot = huffman_tree;
	numCompressedBytes--; //the last bit is only partialy filled and needs to be handled diffferently
	while (currChar < numCompressedBytes) { //loop through the majority of bits
		if (compressedData[currChar] & 1 << currBit)
			currSpot = currSpot->lChild;
		else
			currSpot = currSpot->rChild;
		if (isLeaf(currSpot)) { //found a char
			fputc(currSpot->whichChar, fp);
			currSpot = huffman_tree;
		}
		if (!currBit) { //on last bit
			currBit = CHAR_BIT;
			currChar++;
		}
		currBit--;
	}
	while (currBit >= lastBit) { //finsih last bits
		if (compressedData[currChar] & 1 << currBit)
			currSpot = currSpot->lChild;
		else
			currSpot = currSpot->rChild;
		if (isLeaf(currSpot)) {
			fputc(currSpot->whichChar, fp);
			currSpot = huffman_tree;
		}
		currBit--;
	}
}
void freeTree(huffman* huffman_tree)
{
	if (!isLeaf(huffman_tree)) {
		freeTree(huffman_tree->lChild);
		freeTree(huffman_tree->rChild);
	}
	free(huffman_tree); //do the freeing
}
void decompression(const char* inputFile, const char* outputFile)
{
	//var declaration
	frequency numCompressedBytes;
	char lastBit;

	//finsih nessisary file input
	FILE* fp = checkFile(inputFile, "rb");
	//freqtable + pQue
	enque_items(fp);//enque every thing: bypass making actual freq table
	//binary file rep. + meta data to help
	fread(&numCompressedBytes, sizeof(frequency), 1, fp);
	fread(&lastBit, sizeof(char), 1, fp);
	unsigned char* compressedData = (unsigned char*)malloc(sizeof(unsigned char*) * numCompressedBytes);
	fread(compressedData, sizeof(unsigned char), numCompressedBytes, fp);
	fclose(fp);

	//get tree
	huffman* huffman_tree = buildTree();
	doneWith_pQue(); //free the pQue

	//fill file
	if (outputFile)
		fp = checkFile(outputFile, "w");
	else
		fp = checkFile(DEFAULT_TEXT_FILE, "w");
	printToFile(numCompressedBytes, huffman_tree, fp, compressedData, lastBit); //every char is imediatly spit into file
	fclose(fp);

	//clean up
	free(compressedData);
	freeTree(huffman_tree);
}

//marco of input instuctions
#define HOW_TO_USE "\nInstructions:\n\n\
 - WARNING: THERE ARE NO DASHES IN FROUNT OF ANY ARGUMENT\n\
 - You first: run the program name\n\
 - Then: write the mode of use -> 'c' - compression, 'd' - decompression, or 'i' - instructions\n\
 - If doing compression or decompression: write the input file. \n\
For compression it should be a text file and for decompression a binanry file made by the compression algorithum\n\
 - If doing compression or decompression: the next argument is the output file.\n\
This file in not manditory but if you choose -> the output file type of: commpression will be bianary and decommpression will be text\n\n\n\
General:\n\n\
 - This compression teqneque is called huffman coding\n\
 - WARNING: The maximum frequency of a charactor is %llu\n\
 - The default output file of: compression is \"%s\", and decompression is \"%s\"\n\
 - A priority que is used to activly sort frequencys\n\
 - There is no need for the macro \"pQue_test\" to be turn on and the program activly tries to disable it\n\
After all it is including a library of priority que functions\n\n"
void (*compressionFunc[])(const char*, const char*) = { decompression, compression };
int main(int argc, char* argv[])
{
	if (argc < 2) { //no mode
		printf("Not enough parameters given!\nRun mode 'i' (instructions) for further information\n");
		exit(EXIT_FAILURE);
	}
	if ((argv[1][0] != 'c') && (argv[1][0] != 'd')) { //insturctions
		printf(HOW_TO_USE, (unsigned long long)(~((frequency)0)), DEFAULT_BINARY_FILE, DEFAULT_TEXT_FILE);
		exit(EXIT_SUCCESS);
	}
	else { //real program
		if (argc < 3) { //no input
			printf("No input file given!\nRun mode 'i' (instructions) for further information\n");
			exit(EXIT_FAILURE);
		}
		else if(argc < 4) //no output file
			compressionFunc[argv[1][0] == 'c'](argv[2], NULL);
		else //everything normal
			compressionFunc[argv[1][0] == 'c'](argv[2], argv[3]);
	}
	return 0; //done
}