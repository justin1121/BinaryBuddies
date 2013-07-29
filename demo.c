#include <stdio.h>
#include <stdlib.h>
#include "bbuddies.h"

int main(int argc, char * argv[]){
  if(start_memory(1024)){
    printf("WOOO\n");
  }
  void * mem = get_memory(32);
  void * mem2 = get_memory(64);

  return 0;
}
