/******************************************************************************
 * Name: Russell Moon
 * Program: Random Test Card 1 (Village)
 * Description: Tests the Village card from dominion.c with radomized inputs
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
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
        smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    int testsFailed = 0; //counts number of tests failed
    int numTests = 1000;
    int maxDeck = 500;




    printf("**********************   CT 3: VILLAGE   *******************\n\n");

    for (int k = 0; k < numTests; k++)
    {
        printf("********************** Random Test: %d ***************\n", k);

        // printf("********************** TEST 1: +1 CARD ***************\n");
        /***************************   TEST 1: +1 CARD  ***********************/
        //Tests whether player has received 1 card
        r = initializeGame(numPlayer, kCards, seed, &G); // initialize a new test game

        //randomly generate current player
        int currPlayer = getRand(0, 3);
        G.whoseTurn = currPlayer;
        printf("********************** Player Tested: %d ***************\n", currPlayer);

        //set deck count
        G.deckCount[currPlayer] = maxDeck;

        //randomly seed deck with different card types (card # 0-26)
        for (int i = 0; i < maxDeck; i++)
        {
            G.deck[currPlayer][i] = getRand(0, 26);
        }

        memcpy(&ConG, &G, sizeof(struct gameState)); //copy game state to control
        cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus); //play Village

        //test function versus expected value
        printf("P0 hand count: %d; Expected: %d -> ", G.handCount[currPlayer],
               ConG.handCount[currPlayer] + 1 - 1);
        if (assertTrue(G.handCount[currPlayer], ConG.handCount[currPlayer] + 1 - 1, &testsFailed))
            printf("PASSED\n");
        else
            printf("FAILED\n");

        //printf("\n********************** TEST 2: +2 ACTIONS  ************************\n");
        /***************************   TEST 2: +2 ACTIONS  ****************************/
        //Check to see if number of actions has increased by 2

        //test function versus expected value
        printf("P0 Num actions: %d; Expected: %d -> ", G.numActions, ConG.numActions + 2);
        if (assertTrue(G.numActions, ConG.numActions + 2, &testsFailed))
            printf("PASSED\n");
        else
            printf("FAILED\n");

        //printf("\n************ TEST 3: NO STATE CHANGE OTHER PLAYERS *************\n");
        /*********************    TEST 3: NO STATE CHANGE OTHER PLAYERS    ******************/

        //ensure tested function hasn't altered other player's game state in unexpected way
        if (compareStates(&G, &ConG, currPlayer, numPlayer, 0, 0, 0, 1, 0, 0))
            printf("Compare other player states -> PASSED\n");
        else
        {
            printf("Compare other player states -> FAILED\n");
            testsFailed++;
        }

        //printf("\n*********** TEST 4: NO STATE CHANGE IN SUPPLY CARDS ************\n");
        /*********************    TEST 4: NO STATE CHANGE IN SUPPLY CARDS    ******************/

        //ensure tested function hasn't altered other player's game state in unexpected way
        if (compareStates(&G, &ConG, currPlayer, numPlayer, 1, 1, 1, 0, 0, 0))
            printf("Compare supply cards states -> PASSED\n");
        else
        {
            printf("Compare supply cards states -> FAILED\n");
            testsFailed++;
        }
    }//end randomization loop


    //Output Results
    printf("\n\n********************** CT 3: VILLAGE - RESULTS ********************\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
