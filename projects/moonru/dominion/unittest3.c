/******************************************************************************
 * Name: Russell Moon
 * Program: Unit Test 3
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
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    int testsFailed = 0; //counts number of tests failed
    //int numTests = 50;



    printf("********************** UNIT TEST 3: whoseTurn() **********************\n");
    printf("**********************************************************************\n\n");

    printf("********************** TEST 1: EXPECTED RANGE ************************\n\n");
    /***************************   TEST 1: EXPECTED RANGE  ****************************/
    //Testing valid operation for up to numPlayer players (numPlayers is <= 4; i.e., the
    //expected range)
    for (int i=0; i < numPlayer; i++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game
        memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state

        //set players turn
        G.whoseTurn = i;

        //test function versus expected value
        printf("# Current player: %d -> ", i);
        if (assertTrue(whoseTurn(&G), i, &testsFailed))
                    printf("PASSED\n");
                else
                    printf("FAILED\n");

        
        /************************  TEST 1.1: COMPARE STATES  *************************/
        //ensure tested function hasn't altered game state in unexpected way
        if (compareStates(&G, &ConG, 0, numPlayer, 1, 1, 1, 1, 1, 1))
            printf("Compare states test -> PASSED\n");
        else
        {
                printf("Compare states test -> FAILED\n");
                testsFailed++;
        }
        
    }

    // printf("********************** TEST 2: RANDOM VALUES ************************\n\n");
    // /***************************   TEST 2: RANDOM VALUES  ****************************/
    // //test random values (including negative values) in range that is well outside of
    // //expected bounds
    // for (int i=0; i < numTests; i++)
    // {
    //     memset(&G, 23, sizeof(struct gameState));   // clear the game state
    //     r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game

    //     //randomize current player and make select values negative
    //     int currPlayer = getRand(0, 1000);
    //     if ((currPlayer % 7) == 0) { currPlayer *= -1; } //negate value
    //     G.whoseTurn = currPlayer; //set game state

    //     //test function versus expected value
    //     printf("# Current player: %d -> ", currPlayer);
    //     if (assertTrue(whoseTurn(&G), currPlayer, &testsFailed))
    //                 printf("PASSED\n");
    //             else
    //                 printf("FAILED\n");


    // }


    //Output Results
    printf("\n\n********************** UNIT TEST 3: RESULTS **********************\n\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
