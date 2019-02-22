/******************************************************************************
 * Name: Russell Moon
 * Program: Rand Test Adventurer
 * Description: Tests the Adventurer card from dominion.c with randomized
 * inputs
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
    int maxDeck = 500;
    int r;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int kCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
        smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    int testsFailed = 0; //counts number of tests failed
    int numTests = 100;





    printf("**********************  ADVENTURER RANDOM TEST  *******************\n\n");
  
    //iterate through random tests

    for (int k = 0; k < numTests; k++)
    {
        printf("********************** Random Test: %d ***************\n", k);
        /***************************   TEST 1: +2 treasure cards  ***********************/
        //Tests whether player has received 2 treasure cards
        memset(&G, 23, sizeof(struct gameState));        // clear the test game state
        memset(&ConG, 23, sizeof(struct gameState));     // clear the control game state
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
            G.deck[currPlayer][getRand(0, 26)];
        }



        memcpy(&ConG, &G, sizeof(struct gameState));  //copy game state to control
        cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus); //play Adventurer

        //count number of treasurer cards in hand for test and control games
        //test game (G)
        int testTreasure = 0;
        G.whoseTurn = currPlayer;
        for (int i = 0; i < G.handCount[currPlayer]; i++)
        {
            int currCard = G.hand[currPlayer][i];
            if (currCard == copper || currCard == silver || currCard == gold)
                testTreasure++;
        }
        //control game (ConG)
        int controlTreasure = 0;
        ConG.whoseTurn = currPlayer;
        for (int i = 0; i < ConG.handCount[currPlayer]; i++) //test game (G)
        {
            int currCard = ConG.hand[currPlayer][i];
            if (currCard == copper || currCard == silver || currCard == gold)
                controlTreasure++;
        }

        //test function versus expected value
        printf("Test treasure cards: %d; Control treasure cards: %d -> ", testTreasure, controlTreasure);
        if (assertTrue(testTreasure, controlTreasure + 2, &testsFailed))
            printf("PASSED\n");
        else
            printf("FAILED\n");

        //printf("\n********************** TEST 2: DECK/DISCARD PILE ************************\n");
        /***************************   TEST 2: DECK/DISCARD PILE  ****************************/
        //Check to see if discard pile increased by same amount as decrease in deck pile minus
        //the two treasure cards

        int discardInc = G.discardCount[currPlayer] - ConG.discardCount[currPlayer];
        int deckDec = ConG.deckCount[currPlayer] - G.deckCount[currPlayer];

        //printf("Discard Increase: %d, Deck Decrease: %d\n", discardInc, deckDec);

        //test function versus expected value
        printf("Discard Increase: %d; Expected: %d -> ", discardInc, deckDec - 2);
        if (assertTrue(discardInc, deckDec - 2, &testsFailed))
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
    } //end random test loop



    //Output Results
    printf("\n\n********************** CT 2: ADVENTURER - RESULTS ********************\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
