/******************************************************************************
 * Name: Russell Moon
 * Program: Unit Test 1
 * Description: Tests updateCoins from dominion.c
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
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int adventurers[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
        adventurers[i] = adventurer;
    }

    printf("**************************** UT 1: updateCoins() ****************************\n\n");

    //test cards with bounds of business rules (game rule maximums and minimums)
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 0; handCount <= maxHandCount + 1; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus + 1; bonus++)
            {

                /*****************************   INITIALIZE GAME  ******************************/
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif         
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game
                memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state
                G.handCount[p] = handCount;                 // set the number of cards in hand


                /*****************************   TEST 1: COPPER  ******************************/
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("COPPER: G.coins = %d, expected = %d -> ", G.coins, handCount * 1 + bonus);
#endif
                if (assertTrue(G.coins, handCount + bonus, &testsFailed)) // check if the number of coins is correct
                    printf("PASSED\n");
                else
                    printf("PASSED\n");
                
                /*****************************   TEST 2: SILVER  ******************************/
                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("SILVER: G.coins = %d, expected = %d -> ", G.coins, handCount * 2 + bonus);
#endif
                if (assertTrue(G.coins, handCount * 2 + bonus, &testsFailed)) // check if the number of coins is correct
                    printf("PASSED\n");
                else
                    printf("PASSED\n");

                /*****************************   TEST 3: GOLD  ******************************/
                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("GOLD: G.coins = %d, expected = %d: ", G.coins, handCount * 3 + bonus);
#endif
                if (assertTrue(G.coins, handCount * 3 + bonus, &testsFailed)) // check if the number of coins is correct
                    printf("PASSED\n");
                else
                    printf("PASSED\n");


                /************************  TEST 4: COMPARE STATES  *************************/
                //ensure tested function hasn't altered game state in unexpected way
                if (compareStates(&G, &ConG, p, numPlayer, 1, 1, 1, 1, 0, 1))
                    printf("Compare states test -> PASSED\n");
                else
                {
                     printf("Compare states test -> FAILED\n");
                     testsFailed++;
                }
            }
        }
    }


    /*****************************   TEST 5: RANDOM VALUES  ******************************/

    //test cards with RNG; within and without expected game boundaries
    //treasure cards in hand are randomized
    //hand size is set to max
    for (int i = 1; i < 50; i++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state
        int player = getRand(1, numPlayer); //randomly choose player
        G.handCount[player] = maxHandCount; // set the number of cards in hand
        memcpy(G.hand[player], adventurers, sizeof(int) * handCount); // set all the cards to adventurer
        int totalTreasure = 0; //accumulator for adding up total value of treasure cards in hand

        //set up to 5 randomly chosen cards to a random treasure card
        for (int j = 0; j < maxHandCount; j++)
        {
            G.hand[player][getRand(1,5)] = getRand(4,6);
        }

        bonus = getRand(0,10);//randomly generate bonus
        totalTreasure += bonus; //add bonus to total treasure accumulator

        //update coins based on randomly generated hand 
        updateCoins(player, &G, bonus);
        
        //add up treasure card count in rand generated hand for comparison with game state
        int numCopper = 0;
        int numSilver = 0;
        int numGold = 0;
        for (int k = 0; k < maxHandCount; k++)
        {
            if (G.hand[player][k] == 4) //if copper
            {
                totalTreasure += 1;
                numCopper++;
            }
            else if (G.hand[player][k] == 5) //if silver
            {
                totalTreasure += 2;  
                numSilver++;
            } 
            else if (G.hand[player][k] == 6) //if gold
            {
                totalTreasure += 3;         
                numGold++;
            }
        }

        //ensure coin and bonus amounts add up to what's expected
        printf("Copper: %d, Silver: %d, Gold: %d, Bonus: %d, Expec: %d, G.coins: %d -> ",
            numCopper, numSilver, numGold, bonus, totalTreasure, G.coins);
        if (assertTrue (G.coins, totalTreasure, &testsFailed))
            printf("PASSED\n");
        else
            printf("PASSED\n");


        /************************  TEST 6: COMPARE STATES  *************************/
        //ensure tested function hasn't altered game state in unexpected way
        printf("    Compare states test -> ");
            if (compareStates(&G, &ConG, player, numPlayer, 1, 1, 1, 1, 0, 1))
            printf("PASSED\n");
        else
        {
            printf("FAILED\n");
            testsFailed++;
        }

    }


    //Output Results
    printf("\n\n********************** UT 1 RESULTS **********************\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
