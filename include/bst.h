#ifndef BST_H
#define BST_H
/**
 * @file bst.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Binary Search Tree Library.
 * @version 0.1
 * @date 2021-10-26
 * 
 * @details Binary Search Tree (BST) - a binary tree with an ordering on node keys such 
 * that for any parent node, it's left child has a lesser key and its right child has a greater key.
 * 
 */

#include <stddef.h>

/**
 * @brief Binary Search Tree Node Structure.
 * 
 * @property key (size_t): Unique key for insertion, deletion, and searching purposes
 * @property data (void *): Data to be stored alongside the node.
 * @property left (struct bst_node *) Pointer to left child node.
 * @property right (struct bst_node *) Pointer to right child node.
 * 
 * @typedef bst_node_t
 * 
 */
typedef struct bst_node {
	size_t key;
	void *data;
	struct bst_node *left;
	struct bst_node *right;
} bst_node_t;

/**
 * @brief Binary Search Tree Structure.
 * 
 * @property root (struct bst_node *) Pointer to bst's root node.
 * 
 * @typedef bst_t
 * 
 */
typedef struct bst {
	struct bst_node *root;
} bst_t;

/**
 * @brief Create a bst node object
 * 
 * @param key (size_t): Unique node key.
 * @param data (void *): Void pointer to user data to be stored alongside the node.
 * @return (bst_node_t *): Pointer to a bst_node_t, or NULL if failure occurs, or key is not unique. 
 * 
 * @note The user must define the unique key that is to be associated with the data. Searching, insertion,
 * and deletion is centered around this key.
 */
bst_node_t *create_bst_node(size_t key, void *data);

/**
 * @brief Allocate memory for a Binary Search Tree Node.
 * 
 * @return (bst_t *): Pointer to Binary Search Tree, or NULL if memory allocation fails. 
 * 
 * @note Memory allocated must be deallocated using a function like `free` after usage.
 * 
 * example:
 * bst_t *bst = create_bst();
 * 
 * // Do work on Tree //
 * 
 * free(bst);
 */
bst_t *create_bst(void);

/**
 * @brief Insert a node into a Binary Search Tree.
 * 
 * @param root (bst_node_t): Pointer to the bst's root node.
 * @param key (size_t): Unique node key.
 * @param data (void *): Void pointer to user data to be stored alongside the node.
 * @return (bst_node_t *): Pointer to a bst_node_t, or NULL if failure occurs, or key is not unique.
 */
bst_node_t *insert_bst(bst_node_t *root, size_t key, void *data);

/**
 * @brief Delete a Binary Search Tree Node given a key for the node.
 * 
 * @param root (bst_node_t): Pointer to the bst's root node.
 * @param key (size_t): Unique node key.
 * @param destroy (void (*(void *))): Void function address for a user defined destruction sequence.
 * @return (bst_node_t *): Pointer to a bst_node_t, or NULL if the key does not exist.
 */
bst_node_t *delete_bst_node(bst_node_t *root, size_t key, void (*destroy)(void *));

/**
 * @brief Search a Binary Search Tree for the node of a given key.
 * 
 * @param root (bst_node_t): Pointer to the bst's root node.
 * @param key (size_t): Unique node key.
 * @return (bst_node_t *): Pointer to a bst_node_t.
 */
bst_node_t *search_bst(bst_node_t *root, size_t key);

/**
 * @brief Destroy a Binary Search Tree and its nodes.
 * 
 * @param root (bst_node_t): Pointer to the bst's root node.
 * @param destroy (void (*(void *))): Void function address for a user defined destruction sequence.
 */
void destroy_bst(bst_node_t *root, void (*destroy)(void *));

#endif // BST_H