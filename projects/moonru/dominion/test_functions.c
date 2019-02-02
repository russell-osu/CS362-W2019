/******************************************************************************
 * Name: Russell Moon
 * Program: test_functions
 * Description: contains functions for running Dominion unit tests
 * Class: CS 362
 * Notes: 
 *****************************************************************************/

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


//custom assert function that will not stop execution (and prints result)
int assertTrue (int a, int b, int *testsFailed)
{
    if (a == b)
    {
        return 1;
    }
    else
    {
        *testsFailed = *testsFailed + 1; 
        return 0;
    }
}



//Returns a random integer in the specified range. 
//With help from Gaddis, 9E, p. 135.
int getRand(int low, int high)
{
	return (rand() % (high - low + 1)) + low;
}

//Sets the seed for rand()
void setSeed()
{
	//set the seed for RNG
	unsigned seed = time(NULL);
	srand(seed);
}



//ensure tested function hasn't altered game state in unexpected way
//flags used for victory, treasure, kingdom, player and played cards 
//to determine if they need to be checked for consistency
int compareStates(struct gameState *G, struct gameState *ConG, int player, 
    int numPlayer, int victoryFlag, int treasureFlag, int kingdomFlag, 
    int otherPlayerFlag, int currPlayerFlag, int playedFlag)
{
    int passed = 1; //flag for passing all compare state tests

    //create new game state in order to calculate array sizes for memcmp
    struct gameState S;
    int handArrSize = sizeof(S.hand[0]);
    int deckArrSize = sizeof(S.deck[0]);
    int discardArrSize = sizeof(S.discard[0]);
    int playedArrSize = sizeof(S.playedCards);

    //ensure that victory, treasure, and kingdom card supply 
    //counts remain the same
    if (victoryFlag)
    {
        for (int i=0; i<=3; i++)
        {
            if (G->supplyCount[i] != ConG->supplyCount[i])
                passed = 0;
        }
    }
    if (treasureFlag)
    {
        for (int i=4; i<=6; i++)
        {
            if (G->supplyCount[i] != ConG->supplyCount[i])
                passed = 0;
        }
    }
    if (kingdomFlag)
    {
        for (int i=7; i<=26; i++)
        {
            if (G->supplyCount[i] != ConG->supplyCount[i])
                passed = 0;
        }
    }


    // ensure that other players' hand, deck and discard states haven't changed
    // (excludes current player)
    if (otherPlayerFlag)
    {
        for (int j=0; j<numPlayer; j++)
        {
            if (player != j)
            {
                if (memcmp(G->hand[j], ConG->hand[j], handArrSize) != 0)
                    passed = 0;

                if (G->handCount[j] != ConG->handCount[j])
                    passed = 0;

                if (memcmp(G->deck[j], ConG->deck[j], deckArrSize) != 0)
                    passed = 0;

                if (G->deckCount[j] != ConG->deckCount[j])
                    passed = 0;

                if (memcmp(G->discard[j], ConG->discard[j], discardArrSize) != 0)
                    passed = 0;                 

                if (G->discardCount[j] != ConG->discardCount[j])
                    passed = 0;                    
            }

        }

    }

    //ensure that curr player's hand, deck and discard states haven't changed
    if (currPlayerFlag)
    {
        if (memcmp(G->hand[player], ConG->hand[player], handArrSize) != 0)
            passed = 0;

        if (G->handCount[player] != ConG->handCount[player])
            passed = 0;

        if (memcmp(G->deck[player], ConG->deck[player], deckArrSize) != 0)
            passed = 0;

        if (G->deckCount[player] != ConG->deckCount[player])
            passed = 0;

        if (memcmp(G->discard[player], ConG->discard[player], discardArrSize) != 0)
            passed = 0;                 

        if (G->discardCount[player] != ConG->discardCount[player])
            passed = 0;    
    }

    //ensure that played cards haven't changed
    if (playedFlag)
    {
        if (memcmp(G->playedCards, ConG->playedCards, playedArrSize) != 0)
            passed = 0;              
    }


    return passed;

}