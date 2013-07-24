#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 4

typedef struct _mem_header{
  int size;
  int free;
} mem_header_t;

void * mem;

void * get_memory(int size){
  return NULL;
}

void * grow_memory(int size, void * mem){
  return NULL;

} 

void * pregrow_memory(int size, void * mem){
  return NULL;

}

void release_memory(void * mem){

}

int start_memory(int size){
  if((size & (size - 1)) == 0){
    int totalnodes = size / MIN_SIZE;  
    size += sizeof(/*BTREE NODE*/int) * totalnodes * sizeof(mem_header_t) * totalnodes;
    if((mem = malloc(size)) == NULL){
      return 0;
    }
    else{
      return 1;
    } 
  }
  else{
    return 0;
  }
}

void end_memory(void){

}
