#ifndef RBtree_H
#define RBtree_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#pragma warning (disable : 4996)

struct customer_info {
	int reservation_number;
	char name[10];
	char source[20];
	char destination[20];
	int date;
};

int array_RBTree[501];  //RBTree
int temp1[501];

struct customer_info reservation[500];


enum RBtree_node_color { RED, BLACK };

typedef struct RBtree_node_t {
	void* key;
	struct RBtree_node_t* left;
	struct RBtree_node_t* right;
	struct RBtree_node_t* parent;
	enum RBtree_node_color color;
} *RBtree_node;

typedef struct RBtree_t {
	RBtree_node root;
} *RBtree;

typedef int (*compare_func)(void* left, void* right);

RBtree RBtree_create();
void* RBtree_lookup(RBtree t, void* key, compare_func compare);
void RBtree_insert(RBtree t, void* key, compare_func compare);
void RBtree_delete(RBtree t, void* key, compare_func compare);
typedef RBtree_node node;
typedef enum RBtree_node_color color;


static node grandparent(node n);
static node sibling(node n);
static node uncle(node n);
static void verify_properties(RBtree t);
static void property_1(node root);
static void property_2(node root);
static color node_color(node n);
static void property_4(node root);
static void property_5(node root);
static void property_5_helper(node n, int black_count, int* black_count_path);

static node new_node(void* key, color node_color, node left, node right);
static node lookup_node(RBtree t, void* key, compare_func compare);
static void rotate_left(RBtree t, node n);
static void rotate_right(RBtree t, node n);


static void replace_node(RBtree t, node oldn, node newn);
static void insert_case1(RBtree t, node n);
static void insert_case2(RBtree t, node n);
static void insert_case3(RBtree t, node n);
static void insert_case4(RBtree t, node n);
static void insert_case5(RBtree t, node n);
static node maximum_node(node root);
static void delete_case1(RBtree t, node n);
static void delete_case2(RBtree t, node n);
static void delete_case3(RBtree t, node n);
static void delete_case4(RBtree t, node n);
static void delete_case5(RBtree t, node n);
static void delete_case6(RBtree t, node n);
int compare_int(void* left, void* right);

 void print_tree(RBtree t);
void print_tree_helper(RBtree_node n, int step);

#endif 