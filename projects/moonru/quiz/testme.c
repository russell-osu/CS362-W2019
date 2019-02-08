#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/******************************************************************************
Function: int getRand(int low, int high)
This function returns a random integer in the specified range. With help from
Gaddis, 9E, p. 135.
******************************************************************************/
int getRand(int low, int high)
{
	return (rand() % (high - low + 1)) + low;
}

char inputChar()
{
    //create char array with characters used in target
    char chacters[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};

    //return random character (from constrained input space)
    return chacters[getRand(0,8)];
}

char *inputString()
{
    //create char array with characters used in target string
    char chacters[6] = {'r', 'e', 's', 'e', 't', '\0'};
    static char randString[6];
    //iterate through string and populate with random chars
    for(int i=0; i<6; i++)
    {
      randString[i] = chacters[getRand(0,5)];
    }
    //return randomized string
    return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
