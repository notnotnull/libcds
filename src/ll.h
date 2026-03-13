#ifndef LL_H
#define LL_H

/**
 * @file ll.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Singly Linked List Library.
 * @version 1.0
 * @date 2021-11-08
 * 
 * @details Linked List - List ADT of a sequence of data containers where one container points
 * to the next container.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stddef.h>

/**
 * @brief Linked List Node Structure
 * 
 * @property data (void *): Data associated with node.
 * @property next (struct ll_node *): Pointer to next node.
 * 
 * @typedef ll_node_t
 */
typedef struct ll_node {
	void *data;
	struct ll_node *next;
} ll_node_t;

/**
 * @brief Linked List Structure
 * 
 * @property nodes (size_t): Number of nodes currently in the linked list.
 * @property head (struct ll_node *): Pointer to the linked list's head node.
 * 
 * @typedef linked_list_t
 */
typedef struct linked_list {
	size_t nodes;
	struct ll_node *head;
} linked_list_t;

/**
 * @brief Create a node structure
 * 
 * @param data (void *): Data to be associated with the created node.
 * @return (ll_node_t *): Pointer to a node structure. 
 */
ll_node_t *ll_create_node(void *data);

/**
 * @brief Create a ll structure.
 * 
 * @return (linked_list_t *): Pointer to created linked list structure
 */
linked_list_t *ll_create(void);

/**
 * @brief Destroy a linked list, deallocating heap memory. 
 * 
 * @param ll (linked_list_t **): Double Pointer to a linked list structure.
 * @param destroy : User defined memory deallocation function.
 */
void ll_destroy(linked_list_t **ll, void (*destroy)(void *));

/**
 * @brief Insert data into the front of a linked list.
 * 
 * @param ll (linked_list_t *): Pointer to a linked list structure.
 * @param data (void *): Data to be associated with the created node.
 * @return (int): 0 on success, -1 on failure.
 */
int ll_insert_front(linked_list_t *ll, void *data);

/**
 * @brief Insert data into the rear of a linked list.
 * 
 * @param ll (linked_list_t *): Pointer to a linked list structure.
 * @param data (void *): Data to be associated with the created node.
 * @return (int): 0 on success, -1 on failure.
 */
int ll_insert_rear(linked_list_t *ll, void *data);

/**
 * @brief Insert data into a specific position in a linked list.
 * 
 * @param ll (linked_list_t *): Pointer to a linked list structure.
 * @param index (size_t): Location of requested insertion.
 * @param data (void *): Data to be associated with the created node.
 * @return (int): 0 on success, -1 on failure.
 */
int ll_insert_at_pos(linked_list_t *ll, size_t index, void *data);

/**
 * @brief Delete a node given a linked list and data.
 * 
 * @param ll (linked_list_t *): Pointer to linked list.
 * @param data (void *): Data to be searched and deleted.
 * @return (int): 0 on successful delete, -1 on non delete.
 */
int ll_delete_node(linked_list_t *ll, void *data);

/**
 * @brief Search a linked list for the first occurrence of `data`
 * 
 * @param ll (linked_list_t *): Pointer to linked list.
 * @param data (void *): Data to be searched.
 * @return (ll_node_t *): Pointer to a linked list node.
 */
ll_node_t *ll_search(linked_list_t *ll, void *data);

/**
 * @brief Insert data into a linked list sorting the list in the process.
 * 
 * @param ll (linked_list_t *): Pointer to linked list.
 * @param head_ref (linked_list_t **): Pointer to linked list head.
 * @param data (void *): Data to be inserted and sorted.
 * @param compare : User-defined comparison function. The function must return an integer.
 * Negative if a is less than b, 0 if they are equal, and positive if a is greater than b.
 * @return (int) 0 on success, -1 on failure.  
 */
int ll_insertion_sort(linked_list_t *ll, void *data, int (*compare)(void *a, void *b));


void ll_display_ints(linked_list_t *ll);

#endif // LL_H