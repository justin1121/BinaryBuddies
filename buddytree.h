#ifndef _BuddyTree_h
#define _BuddyTree_h


typedef int (*BuddyTree_compare)(void *a, void *b);

typedef struct BuddyTreeNode {
    void *key;
    void *data;

    struct BuddyTreeNode *left;
    struct BuddyTreeNode *right;
    struct BuddyTreeNode *parent;
} BuddyTreeNode;

typedef struct BuddyTree {
    int count;
    BuddyTree_compare compare;
    BuddyTreeNode *root;
} BuddyTree;

typedef int (*BuddyTree_traverse_cb)(BuddyTreeNode *node, void *address);

BuddyTree *BuddyTree_create(BuddyTree_compare compare, void *address);
void BuddyTree_destroy(BuddyTree *map);

int BuddyTree_set(BuddyTree *map, void *key, void *data, void * address);
BuddyTreeNode *BuddyTree_get(BuddyTree *map, void *key);

int BuddyTree_traverse(BuddyTree *map, void *key, BuddyTree_traverse_cb traverse_cb);

void *BuddyTree_delete(BuddyTree *map, void *key);

#endif
