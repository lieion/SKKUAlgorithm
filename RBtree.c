#include "RBtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#pragma warning (disable : 4996)

node grandparent(node n) {
	assert(n != NULL);
	assert(n->parent != NULL);
	assert(n->parent->parent != NULL);
	return n->parent->parent;
}

node sibling(node n) {
	assert(n != NULL);
	assert(n->parent != NULL);
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

node uncle(node n) {
	assert(n != NULL);
	assert(n->parent != NULL);
	assert(n->parent->parent != NULL);
	return sibling(n->parent);
}

void verify_properties(RBtree t) {
	property_1(t->root);
	property_2(t->root);
	property_4(t->root);
	property_5(t->root);
}

void property_1(node n) {
	assert(node_color(n) == RED || node_color(n) == BLACK);
	if (n == NULL) return;
	property_1(n->left);
	property_1(n->right);
}

void property_2(node root) {
	assert(node_color(root) == BLACK);
}

color node_color(node n) {
	return n == NULL ? BLACK : n->color;
}

void property_4(node n) {
	if (node_color(n) == RED) {
		assert(node_color(n->left) == BLACK);
		assert(node_color(n->right) == BLACK);
		assert(node_color(n->parent) == BLACK);
	}
	if (n == NULL) return;
	property_4(n->left);
	property_4(n->right);
}

void property_5(node root) {
	int black_count_path = -1;
	property_5_helper(root, 0, &black_count_path);
}

void property_5_helper(node n, int black_count, int* path_black_count) {
	if (node_color(n) == BLACK) {
		black_count++;
	}
	if (n == NULL) {
		if (*path_black_count == -1) {
			*path_black_count = black_count;
		}
		else {
			assert(black_count == *path_black_count);
		}
		return;
	}
	property_5_helper(n->left, black_count, path_black_count);
	property_5_helper(n->right, black_count, path_black_count);
}

RBtree RBtree_create() {
	RBtree t = malloc(sizeof(struct RBtree_t));
	t->root = NULL;
	verify_properties(t);
	return t;
}

node new_node(void* key, color node_color, node left, node right) {
	node result = malloc(sizeof(struct RBtree_node_t));
	result->key = key;
	result->color = node_color;
	result->left = left;
	result->right = right;
	if (left != NULL)  left->parent = result;
	if (right != NULL) right->parent = result;
	result->parent = NULL;
	return result;
}

node lookup_node(RBtree t, void* key, compare_func compare) {
	node n = t->root;
	while (n != NULL) {
		int comp_result = compare(key, n->key);
		if (comp_result == 0) {
			return n;
		}
		else if (comp_result < 0) {
			n = n->left;
		}
		else {
			assert(comp_result > 0);
			n = n->right;
		}
	}
	return n;
}

void* RBtree_lookup(RBtree t, void* key, compare_func compare) {
	node n = lookup_node(t, key, compare);
	return n == NULL ? NULL : n->key;
}

void rotate_left(RBtree t, node n) {
	node r = n->right;
	replace_node(t, n, r);
	n->right = r->left;
	if (r->left != NULL) {
		r->left->parent = n;
	}
	r->left = n;
	n->parent = r;
}

void rotate_right(RBtree t, node n) {
	node L = n->left;
	replace_node(t, n, L);
	n->left = L->right;
	if (L->right != NULL) {
		L->right->parent = n;
	}
	L->right = n;
	n->parent = L;
}

void replace_node(RBtree t, node oldn, node newn) {
	if (oldn->parent == NULL) {
		t->root = newn;
	}
	else {
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL) {
		newn->parent = oldn->parent;
	}
}

void RBtree_insert(RBtree t, void* key, compare_func compare) {
	node inserted_node = new_node(key, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = inserted_node;
	}
	else {
		node n = t->root;
		while (1) {
			int comp_result = compare(key, n->key);
			if (comp_result == 0) {
				free(inserted_node);
				return;
			}
			else if (comp_result < 0) {
				if (n->left == NULL) {
					n->left = inserted_node;
					break;
				}
				else {
					n = n->left;
				}
			}
			else {
				assert(comp_result > 0);
				if (n->right == NULL) {
					n->right = inserted_node;
					break;
				}
				else {
					n = n->right;
				}
			}
		}
		inserted_node->parent = n;
	}
	insert_case1(t, inserted_node);
	verify_properties(t);
}

void insert_case1(RBtree t, node n) {
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(t, n);
}

void insert_case2(RBtree t, node n) {
	if (node_color(n->parent) == BLACK)
		return;
	else
		insert_case3(t, n);
}

void insert_case3(RBtree t, node n) {
	if (node_color(uncle(n)) == RED) {
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(t, grandparent(n));
	}
	else {
		insert_case4(t, n);
	}
}

void insert_case4(RBtree t, node n) {
	if (n == n->parent->right && n->parent == grandparent(n)->left) {
		rotate_left(t, n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right) {
		rotate_right(t, n->parent);
		n = n->right;
	}
	insert_case5(t, n);
}

void insert_case5(RBtree t, node n) {
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left) {
		rotate_right(t, grandparent(n));
	}
	else {
		assert(n == n->parent->right && n->parent == grandparent(n)->right);
		rotate_left(t, grandparent(n));
	}
}

void RBtree_delete(RBtree t, void* key, compare_func compare) {
	node child;
	node n = lookup_node(t, key, compare);
	if (n == NULL) return;
	if (n->left != NULL && n->right != NULL) {
		node pred = maximum_node(n->left);
		n->key = pred->key;
		n = pred;
	}

	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left : n->right;
	if (node_color(n) == BLACK) {
		n->color = node_color(child);
		delete_case1(t, n);
	}
	replace_node(t, n, child);
	if (n->parent == NULL && child != NULL)
		child->color = BLACK;
	free(n);

	verify_properties(t);
}

static node maximum_node(node n) {
	assert(n != NULL);
	while (n->right != NULL) {
		n = n->right;
	}
	return n;
}

void delete_case1(RBtree t, node n) {
	if (n->parent == NULL)
		return;
	else
		delete_case2(t, n);
}

void delete_case2(RBtree t, node n) {
	if (node_color(sibling(n)) == RED) {
		n->parent->color = RED;
		sibling(n)->color = BLACK;
		if (n == n->parent->left)
			rotate_left(t, n->parent);
		else
			rotate_right(t, n->parent);
	}
	delete_case3(t, n);
}

void delete_case3(RBtree t, node n) {
	if (node_color(n->parent) == BLACK &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		delete_case1(t, n->parent);
	}
	else
		delete_case4(t, n);
}

void delete_case4(RBtree t, node n) {
	if (node_color(n->parent) == RED &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == BLACK &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		n->parent->color = BLACK;
	}
	else
		delete_case5(t, n);
}

void delete_case5(RBtree t, node n) {
	if (n == n->parent->left &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->left) == RED &&
		node_color(sibling(n)->right) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->left->color = BLACK;
		rotate_right(t, sibling(n));
	}
	else if (n == n->parent->right &&
		node_color(sibling(n)) == BLACK &&
		node_color(sibling(n)->right) == RED &&
		node_color(sibling(n)->left) == BLACK)
	{
		sibling(n)->color = RED;
		sibling(n)->right->color = BLACK;
		rotate_left(t, sibling(n));
	}
	delete_case6(t, n);
}

void delete_case6(RBtree t, node n) {
	sibling(n)->color = node_color(n->parent);
	n->parent->color = BLACK;
	if (n == n->parent->left) {
		assert(node_color(sibling(n)->right) == RED);
		sibling(n)->right->color = BLACK;
		rotate_left(t, n->parent);
	}
	else
	{
		assert(node_color(sibling(n)->left) == RED);
		sibling(n)->left->color = BLACK;
		rotate_right(t, n->parent);
	}
}


int compare_int(void* leftp, void* rightp) {
	int left = (int)leftp;
	int right = (int)rightp;
	if (left < right)
		return -1;
	else if (left > right)
		return 1;
	else {
		assert(left == right);
		return 0;
	}
}


void print_tree(RBtree t) {
	print_tree_helper(t->root, 0);
	puts("");
}

void print_tree_helper(RBtree_node n, int step) {
	int i;

	if (n == NULL) {
		fputs("<empty tree>", stdout);
		return;
	}
	if (n->right != NULL) {
		print_tree_helper(n->right, step + 4);
	}
	for (i = 0; i < step; i++) {
		fputs(" ", stdout);

	}
	if (n->color == BLACK) {
		printf("%d\n", (int)n->key);

	}
	else {
		printf("<%d>\n", (int)n->key);
	}
	if (n->left != NULL) {
		print_tree_helper(n->left, step + 4);
	}
}



int RBtree_search_node(struct RBtree_node_t* tree, int value)
{
	RBtree_node tmp = tree;

	while (tmp != NULL) {
		if (tmp->key == value) break;
		else if (tmp->key > value)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	return tmp;
}


int RBtree_height(struct RBtree_node_t* ptr) {
	if (!ptr)
		return 0;
	else {
		int left_h = RBtree_height(ptr->left);
		int right_h = RBtree_height(ptr->right);
		return 1 + (left_h > right_h ? left_h : right_h); // µÑ Áß Å« °ª¿¡ 1À» ´õÇØ ¹ÝÈ¯
	}
}
int RBtree_height(struct RBtree_node_t* ptr) {
	if (!ptr)
		return 0;
	else {
		int left_h = RBtree_height(ptr->left);
		int right_h = RBtree_height(ptr->right);
		return 1 + (left_h > right_h ? left_h : right_h); 
	}
}


int count_node(struct RBtree_node_t* ptr) {
	int count_node_number = 0;
	
	if (ptr == NULL) return 0;
	 count_node_number = 1+ count_node(ptr->left)+ count_node(ptr->right);
	 return count_node_number;
}
