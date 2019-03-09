/******************************************************************************
 * Name: Russell Moon
 * Program: Unit Test 4
 * Description: Tests whoseTurn() from dominion.c
 * Class: CS 362
 * Notes: This code is based on the testUpdateCoins.c file included in the
 * week 4 lectures    
 *****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_functions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//function prototypes


int main()
{
    setSeed(); //set seed for local RNG (not rngs.h)
    int seed = 1000; 
    int numPlayer = 4;
    int maxHandSize = 25;
    int r;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    int testsFailed = 0; //counts number of tests failed
    //int numTests = 50;



    printf("********************** UNIT TEST 4: handCard() **********************\n");
    printf("**********************************************************************\n\n");

    printf("********************** TEST 1: EXPECTED RANGE ************************\n\n");
    /***************************   TEST 1: EXPECTED RANGE  ****************************/
    //Testing valid operation for up to numPlayer players (numPlayers is <= 4; i.e., the
    //expected range); testing range of 0 to 25 for hand position; testing all 
    //cards (0 to 26), curse to treasure_map
    for (int i = 0; i < numPlayer; i++)
    {
        for (int j = 0; j <= maxHandSize; j++)
        {
            for (int k = 0; k < 27; k++)
            {
                int currPlayer = i;
                int currPos = j;
                int currCard = k;
                memset(&G, 23, sizeof(struct gameState));        // clear the test game state
                memset(&ConG, 23, sizeof(struct gameState));     // clear the control game state
                r = initializeGame(numPlayer, kCards, seed, &G); // initialize a new test game

                //set player, position and card
                G.whoseTurn = currPlayer;
                G.hand[currPlayer][currPos] = currCard;

                // copy test game state to control game state
                memcpy(&ConG, &G, sizeof(struct gameState));     

                //test function versus expected value
                printf("Player: %d, HandPos: %d, Card: %d -> ", currPlayer, currPos, currCard);
                if (assertTrue(handCard(currPos, &G), currCard, &testsFailed))
                    printf("PASSED;  ");
                else
                    printf("FAILED;  ");

                /************************  TEST 1.1: COMPARE STATES  *************************/
                //ensure tested function hasn't altered game state in unexpected way
                if (compareStates(&G, &ConG, currPlayer, numPlayer, 1, 1, 1, 1, 1, 1))
                    printf("Compare states -> PASSED\n");
                else
                {
                    printf("Compare states -> FAILED\n");
                    testsFailed++;
                }
            }
        }
    }



    //Output Results
    printf("\n\n********************** UNIT TEST 4: RESULTS **********************\n\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
