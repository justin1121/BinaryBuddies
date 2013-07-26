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
  void * mem_block = NULL;
	
  // get the first node of the tree
  BuddyTreeNode * node = BuddyTree_get(tree, mem + 1); 
  
  if(((mem_header_t *)node->data)->size < size){
     // error 
  }
  else{
    while(((mem_header_t *)node->data)->free){
      mem_header_t * data = ((mem_header_t *)node->data);
      // check if the node is the right size
      	// if yes, allocate memory and break
      if(!(data->size / 2 >= size)){ 
      	// set the memory to return
				mem_block = node->key;
				data->free = 0;
			}	
			else{
        // trying to go below MIN_SIZE block return, no mem
        if(data->size / 2 < MIN_SIZE){
          return NULL;
        } 
      	// if no, check for children
				if(node->left == NULL){
					// if there are none, make children
          mem_header_t * newleft  = data + 1,
                       * newright = data + 2;
          newleft->size = data->size / 2;
          newleft->size = data->size / 2;
          newright->free = 1;
          newright->free = 1;

          void * keyleft  = node->key; 
          void * keyright = node->key + 4; 
						// left
					if(BuddyTree_set(tree, keyleft, newleft) == -1){
						// error
					}
						// right
					if(BuddyTree_set(tree, keyright, newright) == -1){
						// error
					}
				}
					
				// if there are children, check if the left is free
				if(((mem_header_t *)node->left->data)->free){
					// if yes, move to the left node
					node = BuddyTree_get(tree, node->left->key);
				}
				// if no, check if the right node is free
				else if(((mem_header_t *)node->right->data)->free){
					// if yes, move to the right node
					node = BuddyTree_get(tree, node->right->key);
				}
				else{
					// if neither are free
					// while parent is not null and right node is allocated
					while(node->parent != NULL && !((mem_header_t *)node->right->data)->free){	
						// move to parent and check if right node is not allocated
						node = BuddyTree_get(tree, node->parent->key);
						if(((mem_header_t *)node->right->data)->free){
							// if not, move to right node
							node = BuddyTree_get(tree, node->right->key);	
						}	
					}
				}
				// check if parent is null
				if(node->parent == NULL){
					// if yes, notify that there is no mem
					// error
					return NULL;
				}
   	 	}
		}
  }
	return mem_block;
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

  if((tree = BuddyTree_create(address_compare, mem)) == NULL){
    return 0;
  }
 
  mem_header_t * data = ((mem_header_t *)((BuddyTree *)mem) + 1);
  data->size = size;
  data->free = 1;

  BuddyTreeNode * address = (BuddyTreeNode *)(data + 1);
  if(BuddyTree_set(tree, address, data) == -1){
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
