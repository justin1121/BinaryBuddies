#include <stdlib.h>
#include "buddytree.h"
#include "dbg.h"

static int level = 0;
static int node_found = 0;

static int default_compare(void *a, void *b){
  if(strncmp((char *)a, (char *)b, 32) == 0){
    return 0;
  }
  else{
    if(((char *)b)[level + 1] == '0'){
      level++;
      return -1;
    }
    else{
      level++;
      return 1;
    }
  }
}

BuddyTree *BuddyTree_create(BuddyTree_compare compare, void *address){
	BuddyTree *map = address; //calloc(1, sizeof(BuddyTree));
	check_mem(map);

	map->compare = compare == NULL ? default_compare : compare;

	return map;

error:	
	if(map) {
		BuddyTree_destroy(map);
    }
   return NULL;
}

static long int BuddyTree_destroy_cb(BuddyTreeNode *node, void *address){
  free(node);
  return 0;
}

void BuddyTree_destroy(BuddyTree *map){
	if(map) {
		BuddyTree_traverse(map, NULL, BuddyTree_destroy_cb);
    free(map);
  }
}

static inline BuddyTreeNode *BuddyTreeNode_create(BuddyTreeNode *parent, void *key, void *data, void * address){
	BuddyTreeNode *node = address; //calloc(1, sizeof(BuddyTreeNode));
	check_mem(node);

  node->key = key;
  node->data = data;
  node->parent = parent;
  return node;

error:
  return NULL;
}

static inline void BuddyTree_setnode(BuddyTree *map, BuddyTreeNode *node, void *key, void *data, void * address){
  int cmp = map->compare(node->key, key);

  if(cmp <= 0) {
      if(node->left) {
          BuddyTree_setnode(map, node->left, key, data, address);
      } else {
          node->left = BuddyTreeNode_create(node, key, data, address);
      }
  } else {
      if(node->right) {
          BuddyTree_setnode(map, node->right, key, data, address);
      } else {
          node->right = BuddyTreeNode_create(node, key, data, address);
      }
  }
}

int BuddyTree_set(BuddyTree *map, void *key, void *data, void * address){
  if(map->root == NULL) {
      // first so just make it and get out
      map->root = BuddyTreeNode_create(NULL, key, data, address);
      check_mem(map->root);
  } else {
      BuddyTree_setnode(map, map->root, key, data, address);
  }

  level = 0;

  return 0;
error:
  return -1;
}

static inline BuddyTreeNode *BuddyTree_getnode(BuddyTree *map, BuddyTreeNode *node, void *key){
  int cmp = map->compare(node->key, key);

  if(cmp == 0) {
      return node;
  } else if(cmp < 0) {
      if(node->left) {
          return BuddyTree_getnode(map, node->left, key);
      } else {
          return NULL;
      }
  } else {
      if(node->right) {
          return BuddyTree_getnode(map, node->right, key);
      } else {
          return NULL;
      }
  }
}

BuddyTreeNode *BuddyTree_get(BuddyTree *map, void *key){
  if(map->root == NULL) {
      return NULL;
  } else {
      BuddyTreeNode *node = BuddyTree_getnode(map, map->root, key);
      level = 0;
      return node == NULL ? NULL : node;
  }
}

static inline long int BuddyTree_traverse_nodes(BuddyTreeNode *node, void *key, BuddyTree_traverse_cb traverse_cb){
  long int rc = 0;
	long int address = 0;

  if(node->left) {
    rc = BuddyTree_traverse_nodes(node->left, key,traverse_cb);
    if(rc != 0) return rc;
  }

  if(node->right) {
    rc = BuddyTree_traverse_nodes(node->right, key, traverse_cb);
    if(rc != 0) return rc;
  }

	if(node_found == 0){
		address = traverse_cb(node, key);
		if(address != 0){
			node_found = 1;
		}
	}
  return address;
}

long int BuddyTree_traverse(BuddyTree *map, void *key, BuddyTree_traverse_cb traverse_cb){
  node_found = 0;
	if(map->root){
    return BuddyTree_traverse_nodes(map->root, key, traverse_cb);
  }

  return 0;
}

static inline BuddyTreeNode *BuddyTree_find_min(BuddyTreeNode *node){
  while(node->left) {
    node = node->left;
  }

  return node;
}

static inline void BuddyTree_replace_node_in_parent(BuddyTree *map, BuddyTreeNode *node, BuddyTreeNode *new_value)
{
    if(node->parent) {
        if(node == node->parent->left) {
            node->parent->left = new_value;
        } else {
            node->parent->right = new_value;
        }
    } else {
        // this is the root so gotta change it
        map->root = new_value;
    }

    if(new_value) {
        new_value->parent = node->parent;
    }
}

