#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
//#include <errno.h> //find the errno values
#include <signal.h> //run signals + raises

//for q6
/*#include <setjmp.h>
jmp_buf env;*/

void(*origHandeler)(int);

//for q2
/*void segV_ERROR(int sig)
{
	printf("noooooooooooooooooooooo, segmentation fault!!!! Bye my frined\n");
	signal(SIGSEGV, origHandeler);
	//exit(EXIT_FAILURE);
}*/

//for q3
/*#ifdef _WIN32
#include <Windows.h>
#define SLEEP Sleep(2000)
#else
#include <unistd.h>
#define SLEEP sleep(2)
#endif
void segINT_Handeler(int sig)
{
	printf("I am in my signal interupt\n");
	signal(SIGINT, segINT_Handeler); //reset it to the new handeler -> windows automaticly resets iy
}*/

//for q5
/*#ifdef _WIN32
#define numSigCovered 4
#include <Windows.h>
#define sleep Sleep(1000)
#else
#define numSigCovered 7
#include <unistd.h>
#define sleep sleep(1)
#endif // _WIN32
inline int whichSig(unsigned short sigNum)
{
	switch (sigNum)
	{
	case 0:
		return SIGINT;
	case 1:
		return SIGABRT;
	case 2:
		return SIGSEGV;
	case 3:
		return SIGTERM;
#ifndef _WIN32
	case 4:
		return SIGKILL;
	case 5:
		return SIGTSTP;
	case 6:
		return SIGWINCH;
#endif // !_WIN32
	default:
		return 0;
	}
}
void q5_SIGINT(int seg)
{
	printf("operation interupted: SIGINT\nProgram quitting\n");
	exit(EXIT_SUCCESS);
}
void q5_SIGABRT(int seg)
{
	printf("operation aborted: SIGABRT #1\nProgram quitting\n");
	exit(EXIT_FAILURE);
}
void q5_SIGSEGV(int seg)
{
	printf("segmentation fault triggered: SIGSEGV #2\n");
	signal(SIGSEGV, q5_SIGSEGV);
}
#ifndef _WIN32
void q5_SIGTERM(int seg)
{
	printf("signal raised: SIGTERM #3\n");
}
void q5_SIGKILL(int seg)
{
	printf("signal raised: SIGKILL #4\n");
}
void q5_SIGTSTP(int seg)
{
	printf("a signal stop raised (Ctrl+Z): SIGTSTP #5\n");
}
void q5_SIGWINCH(int seg)
{
	printf("Window has been changed: SIGWINCH #6\n");
}
#endif // !windows
void (*q5_SIG_Funcs[])(int) = {
	q5_SIGINT, q5_SIGABRT, q5_SIGSEGV, //windows including functions
#ifndef _WIN32
	q5_SIGTERM,q5_SIGKILL, q5_SIGTSTP, q5_SIGWINCH
#endif // !windows
};*/

// for q6 -> run on linux only
/*#include <unistd.h>
unsigned int alarmGap = 1;
unsigned int waitTime = 10;
bool go = false;
void SIGTSTP_StopAlarm(int sig)
{
	go = true;
}
void sendAlarm(int sig)
{
	static unsigned int time = 0;
	printf("Monitor: %u seconds have passed\n", time);
	if (time >= waitTime)
		if (go)
			printf("\nMonitor: stopped montitering***\n\n");
		else
			longjmp(env, 1);//do the jump
	else
		alarm(alarmGap);
	time += alarmGap;
}
unsigned int getNum(char* str)
{
	unsigned int total = 0; 
	while (*str != '\0') {
		total = (total * 10) + (*str - '0');
		str++;
	}
	return total;
}*/
int main(/*int argc, char* argv[] for q5 and q6*/)
{
	//q2
	/*origHandeler = signal(SIGSEGV, segV_ERROR);
	int* a = NULL;
	*a = 5;*/

	//q3
	/*void(*origHandeler)(int) = signal(SIGINT, segINT_Handeler);
	while (true) {
		SLEEP;
		printf("My progmarm persistes\n");
	}
	signal(SIGINT, origHandeler);*/

	//q5 -> handle lots of signals
	/* * * * * * * * * * * * * * * * *
	 *	SIGINT:  //used to quit (0)  *
	 *	SIGABRT : 1                  *
	 *	SIGSEGV : 2                  *
	 *	SIGTERM : 3//this down is	 *
	 *	SIGKILL : 4//linux only      *
	 *	SIGTSTP : 5                  *
	 *	SIGWINCH : 6                 *
	 * * * * * * * * * * * * * * * * */
	/*unsigned short activated = 1;
	for (unsigned short i = 1; i < argc; i++)
		if (argv[i][1] == 'a')
			activated = ~0;
		else 
			activated |= 1 << (argv[i][1] - '0');
	for (unsigned short i = 0; i < numSigCovered; i++)
		if (activated & (1 << i))
			signal(whichSig(i), q5_SIG_Funcs[i]);
	while (true) {
		sleep; //one second
		printf("program still running\n");
	}*/ //actal code

	//q6 -> alarm
	/*int returnVal;
	if ((argc >= 2) && (returnVal = getNum(argv[1])))
		alarmGap = returnVal;
	if (argc >= 3)
		waitTime = getNum(argv[2]);
	signal(SIGTSTP, SIGTSTP_StopAlarm);
	signal(SIGALRM, sendAlarm);
	raise(SIGALRM);//set off alarm
	if (setjmp(env) != 0) {
		printf("\nMain: OOOOFFFFF, alarm wasn't turned off in %u seconds. I stopped waiting\n\n", waitTime);
		return 0;
	}
	unsigned int secondsPassed = 0;
	while (true) {
		sleep(1);
		secondsPassed++;
		printf("Main: still running and busy, %u seconds passed\n", secondsPassed);
	}*/

	return 0;
}