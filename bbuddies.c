#include <stdio.h>
#include <stdlib.h>
#include "buddytree.h"

#define MIN_SIZE 4

static int address_compare(void * a, void * b);

typedef struct _mem_header{
  int size;
  int free;
} mem_header_t;

void * mem;
void * usermemoffset;
BuddyTree * tree;

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
  int tmpsize;

  if((size & (size - 1)) == 0){
    int totalnodes = size / MIN_SIZE;  
    tmpsize = sizeof(BuddyTree) + size + 
              (sizeof(BuddyTreeNode) * totalnodes) + 
              (sizeof(mem_header_t) * totalnodes);
    if((mem = malloc(tmpsize)) == NULL){
      return 0;
    }
  }
  else{
    return 0;
  }

  // set the mem in buddy tree this needs to be done
  if((tree = BuddyTree_create(address_compare, mem)) == NULL){
    return 0;
  }
 
  mem_header_t * data = ((mem_header_t *)((BuddyTree *)mem) + 1);
  data->size = size;
  data->free = 1;

  BuddyTreeNode * address = (BuddyTreeNode *)(data + 1);

  // set the mem in buddy tree this needs to be done
  if(BuddyTree_set(tree, tree, data, address) == -1){
    return 0; 
  }
  usermemoffset = mem + (tmpsize - size);

  return 1;
}

void end_memory(void){

}

static int address_compare(void * a, void * b){
  if(a == b){
    return 0;
  } 
  else{
    return 1;
  }
}
