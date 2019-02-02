CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

test_functions.o: test_functions.c test_functions.h
	gcc -c test_functions.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

#unittest1: unittest1.c dominion.o rngs.o
	#gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

tests.out: unittest1.c dominion.o rngs.o test_functions.o
	
	echo "Result for running BST tests:" > tests.out
	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o test_functions.o $(CFLAGS)
	./unittest1 >> tests.out
	gcov dominion.c >> tests.out

all: playdom player tests.out

clean:
	rm -f *.o playdom.exe playdom player unittest1 tests.out player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
