#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
  printf("Content-Type: text/html;charset=utf-8\n\n");
  // printf("hello world.\n\n");

  // print a 0 or 1 as "return code"
  srand(time(NULL));   // should only be called once
  int r = rand() % 2;      // returns a pseudo-random integer between 0 and 1

  if (r == 1)
    printf("true");
  else
    printf("false");


  return 0;
}
