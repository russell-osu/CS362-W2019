#ifndef _TEST_FUNCTIONS_H
#define _TEST_FUNCTIONS_H

//custom assert function that will not stop execution (and prints result)
int assertTrue(int a, int b, int *testsFailed);
int assertTruePrint (int a, int b, int *testsFailed, char* msg);

//Returns a random integer in the specified range.
int getRand(int low, int high);

//Sets the seed for rand()
void setSeed();

//ensure tested function hasn't altered game state in unexpected way
int compareStates(struct gameState *G, struct gameState *ConG, int player,
    int numPlayer, int victory, int treasure, int kingdom, int otherPlayerFlag, 
    int currPlayerFlag, int playedFlag);


#endif