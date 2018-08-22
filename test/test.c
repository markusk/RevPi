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
  printf("hello world.\n\n");


  return 0;
}
