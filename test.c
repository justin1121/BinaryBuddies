#include <stdio.h>
#include <stdlib.h>

int main(){
  void * tehe = malloc(sizeof(char));

  // create string
  char test[10];
  sprintf(test, "%p", tehe);

  // convert string to int
  long int test1 = strtol(test, NULL, 16);

  // convert int to address
  void * tehe2 = (void *)test1;
}

