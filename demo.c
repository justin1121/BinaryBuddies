#include <stdio.h>
#include <stdlib.h>
#include "bbuddies.h"

int main(int argc, char * argv[]){
  if(start_memory(32)){
    printf("WOOO\n");
  }
  void * mem = get_memory(8);
  void * mem2 = get_memory(8);

  return 0;
}
