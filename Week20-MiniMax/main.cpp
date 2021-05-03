#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>

bool testType;                                 //performance or accuracy
unsigned long long iterations = 0;             // used for performace -> num looped through mini_max
bool optimization = 0;                         // weather to do alpha beta pruning or not
char moves[2] = {'X', 'O'};                    //easy way to check the two moves
char *grid = (char *)malloc(sizeof(char) * 9); //my useable grid

void printGrid(void) //print the current grid nicely
{
    for (int i = 0; i < 3; i++) //every line
    {
        printf("%c", grid[i * 3]);  //first char
        for (int j = 1; j < 3; j++) //every char
            printf("|%c", grid[i * 3 + j]);
        printf("\n-----\n"); //making it neat
    }
}
bool winCheck(int justPlaced) //check if what just got placed wins the game
{
    if ((grid[justPlaced % 3] == grid[(justPlaced % 3) + 3]) && (grid[(justPlaced % 3) + 3] == grid[(justPlaced % 3) + 6])) // check down the line
        return 1;
    else if ((grid[3 * (justPlaced / 3)] == grid[(3 * (justPlaced / 3)) + 1]) && (grid[(3 * (justPlaced / 3)) + 1] == grid[(3 * (justPlaced / 3)) + 2])) //check on the row
        return 1;
    else if ((justPlaced % 2 != 1) && (grid[justPlaced] == grid[4])) //if it is on the diagonal
    {
        if (((justPlaced != 0) && (justPlaced != 8)) && ((grid[2] == grid[4]) && (grid[4] == grid[6]))) //bottem left to top right
            return 1;
        if (((justPlaced != 2) && (justPlaced != 6)) && ((grid[0] == grid[4]) && (grid[4] == grid[8]))) //top left to bottem right
            return 1;
    }
    return 0; //nothing matches
}

int mini_max(bool toPlace, char **spot, int prevHigh) //actual program | recursion | 1 - win, 0 - tie, -1 -
{
    int currHigh = -2;
    int curr;
    char *junk = NULL; //something I give to the next func call

    for (int i = 0; i < 9; i++)
    { //check every position
        if ((grid[i] != 'X') && (grid[i] != 'O'))
        {                             //if not filled
            grid[i] = moves[toPlace]; //try out a placement in ith location temporarily
            if (!winCheck(i))
            {                                               //if what I just said didn't win anything
                curr = mini_max(!toPlace, &junk, currHigh); //call recursion
                if (-1 * curr > currHigh)
                { //if this is an improvement from what I originally have
                    *spot = grid + i;
                    currHigh = -1 * curr; //the curr is of the opposite type
                    if (optimization && (-1 * currHigh < prevHigh))
                    {                      //pruning
                        grid[i] = i + '0'; //Clean up the temporary placement
                        return prevHigh;
                    }
                }
                grid[i] = i + '0'; //Clean up the temporary placement
            }
            else
            { //I just found how to win
                *spot = grid + i;
                grid[i] = i + '0'; //Clean up the temporary placement
                return 1;          //return I won
            }
        }
        if (!testType) //i have to -> count iterations
            iterations++;
    }
    return currHigh % 2; //return my current status
}
int main(void) //setup + running tests + end display
{
    int numOfWins = 0; // Used for -
    int numOfTie = 0;  //	accuracy -
    int numOfLoss = 0; // test
    int usersMove = 0;
    char *nowGrid = grid;
    unsigned long timesRun = 1;                                                                                          //how many times the run the same thing
    char win[][38] = {"You won. Good job!\n", "It's a tie. Who is better?\n", "Computer won. Better luck next time!\n"}; //feedback from win status

    printf("Enter the test you want:\n0: performance test(numIterations)\n1: accuracy test(how many tie, win, and loss)\nEnter number(1 or 0): "); //asking test type
    testType = getchar() - '0';                                                                                                                    //storing test type
    while (getchar() != '\n')
        ; //till user enters
    if (testType)
    { //accuracy -> find times to run
        timesRun = 0;
        printf("Enter num Of times to run: "); //ask for run num
        char ch = getchar();
        while (ch != '\n')
        { //get number of times to loop
            timesRun = (timesRun * 10) + ch - '0';
            ch = getchar();
        }
    }
    else
    {
        printf("Do you want to be X or O?: "); //ask start type
        if (toupper(getchar()) == 'O')
            usersMove = 1;
        getchar();
    }
    printf("Do you want to optimize(alpha beta pruning) your code? (Y/N): "); //ask about optimisation
    if (toupper(getchar()) == 'Y')                                            // if it is a yes
        optimization = 1;
    getchar();

    if (testType)                     //if accuracy is used
        srand(time(0));               //plant seed
    char *locationOfPlacement = grid; //where to place
    unsigned long timesPlayed = 0;
    int currPlace = 0;
    while (timesPlayed < timesRun)
    { //run game timesRun number of times
        currPlace = 0;
        while (currPlace < 9)
        { //set grid
            *(grid + currPlace) = '0' + currPlace;
            currPlace++;
        }
        currPlace = 0;
        //printf("Let's play tic tac toe\nTo play enter the number of the box you want to place in.\n");

        while (currPlace < 9)
        { //game cycle

            //check if the game is done
            if (winCheck(locationOfPlacement - grid))
                break;

            // get a valid user input or a random input
            if (currPlace % 2 == usersMove)
            { //get non-program generated number
                if (!testType)
                { //performance -> asking user where to go
                    do
                    {
                        printGrid();
                        printf("enter the number you want to chose: ");
                        locationOfPlacement = grid + getchar() - '0';
                        getchar();
                    } while (*locationOfPlacement != locationOfPlacement - grid + '0'); //if it is occupied go again
                }
                else
                { //accuracy - getting rand location
                    locationOfPlacement = grid + rand() % 9;
                    while (*locationOfPlacement == 'X' || *locationOfPlacement == 'O')
                    {                                        //while this is not possible
                        if (locationOfPlacement - grid != 8) //make sure it doesn't go to 9
                            locationOfPlacement++;
                        else
                            locationOfPlacement = grid; //put back to 0 other wise
                    }
                }
            }
            else //computer's turn - call minimax func
                mini_max(!usersMove, &locationOfPlacement, -2);

            *locationOfPlacement = moves[currPlace % 2];
            currPlace++;
        } //end of game cycle

        if (!testType)
        { //performance -> indicate endgame type
            printGrid();
            if (currPlace == 9)
                printf(win[1]);
            else if (currPlace % 2 == usersMove)
                printf(win[2]);
            else
                printf(win[0]);
        }
        else
        { //accuracy -> increment endgame type
            if (currPlace == 9)
                numOfTie++;
            else if (currPlace % 2 != usersMove)
                numOfLoss++;
            else
                numOfWins++;
        }
        timesPlayed++;
    } //total numOfTimesToPlay loop ends

    if (testType) //tell endgame numbers
        printf("num Of Loss: %d\nNum of win: %d\nnum of tie: %d\n", numOfLoss, numOfWins, numOfTie);
    else //tell num of iteration
        printf("Number of iterations: %u\n", iterations);
    system("timeout 10");
    return 0;
}