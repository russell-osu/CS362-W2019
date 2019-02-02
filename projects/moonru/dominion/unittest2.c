/******************************************************************************
 * Name: Russell Moon
 * Program: Unit Test 2
 * Description: Tests isGameOver() from dominion.c
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
    int i;
    int seed = 1000; 
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    int maxHandCount = 5;
    int testsFailed = 0; //counts number of tests failed
    int numProvTests = 50;


    printf("**************************** UT 2: isGameOver() ****************************\n");

    /*****************************   TEST 1: PROVINCE  ******************************/
    for (int i=0; i < numProvTests; i++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game
        memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state

        //test province cards game ending condition
        int numCards = getRand(0,4); //generate random number of province cards
        numCards *= getRand(1,1000); //multiply by random number for sake of variation
        //add a few negative values (which are bound to fail)
        if ((numCards % 11) == 0)
            numCards *= -1;
        G.supplyCount[province] = numCards; //set number of province cards in G

        //test function versus expected value
        printf("# Province cards: %d -> ", numCards);
        if (assertTrue(isGameOver(&G), numCards <= 0, &testsFailed))
                    printf("PASSED\n");
                else
                    printf("FAILED\n");

        /************************  TEST 2: COMPARE STATES  *************************/
        //ensure tested function hasn't altered game state in unexpected way
        if (compareStates(&G, &ConG, p, numPlayer, 1, 1, 1, 1, 0, 1))
            printf("Compare states test -> PASSED\n");
        else
        {
                printf("Compare states test -> FAILED\n");
                testsFailed++;
        }
        

    }

    //Output Results
    printf("\n\n********************** UT 2 RESULTS **********************\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
