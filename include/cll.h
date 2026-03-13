#ifndef CLL_H
#define CLL_H

/**
 * @file cll.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Circularly Linked List Library (Singly Linked).
 * @version 0.1
 * @date 2021-10-26
 * 
 */

#include <stddef.h>

/**
 * @brief Circularly Linked List Node Structure
 * 
 * @property data (void *): Data associated with node.
 * @property next (struct cll_node *): Pointer to next node.
 * 
 * @typedef cll_node_t
 */
typedef struct cll_node {
	void *data;
	struct cll_node *next;
} cll_node_t;

/**
 * @brief Circularly Linked List Structure
 * 
 * @property nodes (size_t): Number of nodes currently in the linked list.
 * @property head (struct cll_node *): Pointer to the cll's head node.
 * @property tail (struct cll_node *): Pointer to the cll's tail node.
 * 
 * @typedef cll_t
 */
typedef struct circular_linked_list {
	size_t nodes;
	struct cll_node *head;
	struct cll_node *tail;
} cll_t;

/**
 * @brief Create a cll node object.
 * 
 * @param data (void *): Data to be associated with the cll node.
 * @return (cll_node_t *): Pointer to cll node.
 */
cll_node_t *cll_create_node(void *data);

/**
 * @brief Create a cll object.
 * 
 * @return (cll_t *): Pointer to cll struct. 
 */
cll_t *cll_create(void);

/**
 * @brief Destroy a cll including all of its nodes and associated data.
 * 
 * @param cll (cll_t **): Double Pointer to cll struct.
 * @param destroy : User-defined deallocation / destruction function.
 */
void cll_destroy(cll_t **cll, void (*destroy)(void *));

/**
 * @brief Destroy all cll nodes within a cll, set the head and tail to NULL and 
 * nodes to 0.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param destroy : User-defined deallocation / destruction function.
 */
void cll_empty(cll_t *cll, void (*destroy)(void *));

/**
 * @brief Insert a node at the front of a cll.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param data (void *): Data to be associated with the cll node.
 * @return (int): 0 on success, -1 on failure.
 */
int cll_insert_front(cll_t *cll, void *data);

/**
 * @brief Insert a node at the rear of a cll.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param data (void *): Data to be associated with the cll node.
 * @return (int): 0 on success, -1 on failure.
 */
int cll_insert_rear(cll_t *cll, void *data);

/**
 * @brief Insert a node at a specific index in a cll (if the index exists).
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param index (size_t): Index to insert into.
 * @param data (void *): Data to be associated with the cll node.
 * @return (int): 0 on success, -1 on failure.
 */
int cll_insert_at_pos(cll_t *cll, size_t index, void *data);

/**
 * @brief Perform an insertion sort on a cll.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param head_ref (cll_node_t **): Pointer to pointer to the cll's head node.
 * @param data (void *): Data to be inserted.
 * @param compare : User-defined comparison function. The function must return an integer.
 * Negative if a is less than b, 0 if they are equal, and positive if a is greater than b.
 * @return (int): 0 on success, -1 on failure.
 */
int cll_sorted_insert(cll_t *cll, cll_node_t **head_ref, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Delete the first occurance of a cll node.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param data (void *): Data to be deleted.
 * @param destroy : User-defined deallocation / destruction function.
 * @return (int): 0 on success, -1 on failure.
 */
int cll_delete_node(cll_t *cll, void *data, void (*destroy)(void *));

/**
 * @brief Search a cll for data and return a reference to a node if found.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 * @param data (void *): Data to be searched.
 * @param compare : User-defined comparison function. The function must return an integer.
 * @return (cll_node_t *): Pointer to cll node. 
 */
cll_node_t *cll_search(cll_t *cll, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Display a CLL if all associated data are integers.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 */
void cll_display_ints(cll_t *cll);

/**
 * @brief Display a CLL if all associated data are strings.
 * 
 * @param cll (cll_t *): Pointer to cll struct.
 */
void cll_display_strings(cll_t *cll);

#endif // CLL_H