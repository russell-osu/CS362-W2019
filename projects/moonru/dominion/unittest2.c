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
    int seed = 1000; 
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G; //Game state used for testing
    struct gameState ConG; //Control (unchanged) game state used for comparison
    //int maxHandCount = 5;
    int testsFailed = 0; //counts number of tests failed
    int numTests = 50;


    printf("**************************** UT 2: isGameOver() ****************************\n\n");


    printf("**************************** TEST 1: PROVINCE ****************************\n\n");
    /*****************************   TEST 1: PROVINCE  ******************************/
    for (int i=-1; i <= 15; i++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game
        memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state

        //test province cards game ending condition
        G.supplyCount[province] = i; //set number of province cards in G

        /*FOR LATER RANDOMIZATION TESTING*/
        // int numCards = getRand(0,4); //generate random number of province cards
        // numCards *= getRand(1,1000); //multiply by random number for sake of variation
        // //add a few negative values (which are bound to fail)
        // if ((numCards % 11) == 0)
        //     numCards *= -1;
        

        //test function versus expected value
        printf("# Province cards: %d -> ", i);
        if (assertTrue(isGameOver(&G), i <= 0, &testsFailed))
                    printf("PASSED\n");
                else
                    printf("FAILED\n");

        
        /************************  TEST 1.1: COMPARE STATES  *************************/
        //ensure tested function hasn't altered game state in unexpected way
        if (compareStates(&G, &ConG, 0, numPlayer, 0, 1, 1, 1, 1, 1))
            printf("Compare states test -> PASSED\n");
        else
        {
                printf("Compare states test -> FAILED\n");
                testsFailed++;
        }
        
    }

    //     printf("********************** TEST 2: RANDOMIZED OTHER CARDS **********************\n\n");
    //     /*****************************   TEST 2: RANDOMIZED OTHER CARDS  ******************************/
    //     //testing cards other than Province for game ending condition
    //     //pick three random cards (other than Province) and set supply to zero to test
    //     //game ending condtion
    // for (int i=0; i < numTests; i++)
    // {
    //     memset(&G, 23, sizeof(struct gameState));   // clear the game state
    //     memset(&ConG, 23, sizeof(struct gameState));   // clear the game state
    //     r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game
    //     memcpy(&ConG, &G, sizeof(struct gameState)); // copy game state to control game state

    //     //test other cards game ending condition
    //     int cardArr[3] = {99}; //holds randomized cards used in test

    //     //populate card array with 3 unique supply cards (none should be Province)
    //     int chooseAgain;
    //     for (int j=0; j<3; j++)
    //     {   
    
    //         do
    //         {
    //             chooseAgain = 0; //flag for loop
    //             cardArr[j] = getRand(0,26);

    //             for (int k=0; k<3; k++) //make sure there are no dups in array
    //             {
    //                 if (j!=k) 
    //                 {   //choose again if it's a duplicate
    //                     if (cardArr[j] == cardArr[k]) {chooseAgain = 1;}
    //                 }
    //             }
    //             //if card is Province, choose again
    //             if (cardArr[j] == 3) {chooseAgain = 1;}

    //         }while (chooseAgain);

    //         //set count of supply cards corresponding to values in cardArr to 0
    //         G.supplyCount[cardArr[j]] = 0;

    //         //set a small number of the rand chosen supply cards to a positive 
    //         //non-zero value for variation
    //         if (cardArr[j] % 7 == 0) {G.supplyCount[cardArr[j]] = 1;}

    //     }

    //     //test function versus expected value
    //     printf("# Supply cards: %d: %d, %d: %d, %d: %d -> ", 
    //         cardArr[0], G.supplyCount[cardArr[0]], cardArr[1], 
    //         G.supplyCount[cardArr[1]], cardArr[2], G.supplyCount[cardArr[2]]);
    //     int gameOver = (G.supplyCount[cardArr[0]] == 0) && 
    //         (G.supplyCount[cardArr[1]] == 0) && (G.supplyCount[cardArr[2]] == 0);
    //     if (assertTrue(isGameOver(&G), gameOver, &testsFailed))
    //                 printf("PASSED\n");
    //             else
    //                 printf("FAILED\n");

    //     /************************  TEST 2.1: COMPARE STATES  *************************/
    //     //ensure tested function hasn't altered game state in unexpected way
    //     if (compareStates(&G, &ConG, 0, numPlayer, 0, 0, 0, 1, 1, 1))
    //         printf("Compare states test -> PASSED\n");
    //     else
    //     {
    //             printf("Compare states test -> FAILED\n");
    //             testsFailed++;
    //     }
        
    // }

    printf("**************************** TEST 2: ALL COMBOS OF 3 ****************************\n\n");
    /******************   TEST 2: ALL COMBINATIONS OF 3 CARDS  *******************/

    for (int i=0; i<27; i++)
    {
        for (int j=0; j<27; j++)
        {
            for (int m=0; m<27; m++)
            {
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new test game

                //reduce supply of 3 cards to 0
                G.supplyCount[i] = 0;
                G.supplyCount[j] = 0;
                G.supplyCount[m] = 0;


                //test only if all three supply cards are unique
                //and if none of the cards are Province (card 3)
                if (i!=j && i!=m && j!=m && i!=3 && j!=3 && m!=3)
                {
                    //test function versus expected value
                    int gameOver = (G.supplyCount[i] == 0) && 
                        (G.supplyCount[j] == 0) && (G.supplyCount[m] == 0);
                    //only output info about failed tests
                    if (assertTrue(isGameOver(&G), gameOver, &testsFailed))
                    {
                        //do nothing
                    }
                    else
                    {
                        printf("# Supply cards: %d: %d, %d: %d, %d: %d -> ", 
                            i, G.supplyCount[i], j, G.supplyCount[j], m, G.supplyCount[m]);
                        printf("FAILED\n");
                    }
                }

            }
        }
    }

    //Output Results
    printf("\n\n********************** UT 2: RESULTS **********************\n\n");
    if (testsFailed <= 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", testsFailed);
    

    return 0;
}
