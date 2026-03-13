#ifndef DLL_H
#define DLL_H

/**
 * @file dll.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Doubly Linked List Library.
 * @version 0.1
 * @date 2021-10-26
 * 
 */

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Doubly Linked List Node
 * 
 * @property data (void *): Data associated with node.
 * @property next (struct dll_node *): Pointer to next node.
 * @property next (struct dll_node *): Pointer to previous node.
 * 
 * @typedef dll_node_t
 */
typedef struct dll_node {
	void *data;
    struct dll_node *previous;
	struct dll_node *next;
} dll_node_t;

/**
 * @brief Doubly Linked List Structure
 * 
 * @property nodes (size_t): Number of nodes currently in the linked list.
 * @property head (struct dll_node *): Pointer to the dll's head node.
 * @property tail (struct dll_node *): Pointer to the dll's tail node.
 * 
 * @typedef dll_t
 */
typedef struct dll {
	size_t nodes;
	struct dll_node *head;
    struct dll_node *tail;
} dll_t;

/**
 * @brief Create a dll node object
 * 
 * @param data (void *): Data to be associated with the node.
 * @return (dll_node_t *): Pointer to dll_node struct. 
 */
dll_node_t *dll_create_node(void *data);

/**
 * @brief Create a dll object
 * 
 * @return (dll_t *): Pointer to doubly_linked_list struct. 
 */
dll_t *dll_create(void);

/**
 * @brief Free allocated memory associated with a dll struct.
 * 
 * @param dll (dll_t **): Double Pointer to doubly_linked_list struct.
 * @param destroy : User defined memory deallocation function.
 */
void dll_destroy(dll_t **dll, void (*destroy)(void *));

/**
 * @brief Insert node at the front of dll.
 * 
 * @param dll (dll_t *): Pointer to doubly_linked_list struct. 
 * @param data (void *): Data to be associated with the node. 
 * @return (int): 0 on success, -1 on failure.
 */
int dll_insert_front(dll_t *dll, void *data);

/**
 * @brief Insert node at the rear of dll.
 * 
 * @param dll (dll_t *): Pointer to doubly_linked_list struct. 
 * @param data (void *): Data to be associated with the node. 
 * @return (int): 0 on success, -1 on failure.
 */
int dll_insert_rear(dll_t *dll, void *data);

/**
 * @brief Insert node at a given position of dll.
 * 
 * @param dll (dll_t *): Pointer to doubly_linked_list struct.
 * @param index (size_t): Position to insert data. 
 * @param data (void *): Data to be associated with the node. 
 * @return (int): 0 on success, -1 on failure.
 */
int dll_insert_at_pos(dll_t *dll, size_t index, void *data);

/**
 * @brief Delete a node given at the front of dll.
 * 
 * @param dll (linked_list_t *): Pointer to linked list.
 * @return (int): 0 on successful delete, -1 on non delete.
 */
int dll_delete_front(dll_t *dll);

/**
 * @brief Delete a node at the rear of dll.
 * 
 * @param dll (linked_list_t *): Pointer to linked list.
 * @return (int): 0 on successful delete, -1 on non delete.
 */
int dll_delete_rear(dll_t *dll);

/**
 * @brief Delete a node at a given position.
 * 
 * @param dll (linked_list_t *): Pointer to linked list.
 * @return (int): 0 on successful delete, -1 on non delete.
 */
int dll_delete_at_pos(dll_t *dll, size_t index);

/**
 * @brief Search a dll for the first occurrence of data.
 * 
 * @param dll (linked_list_t *): Pointer to linked list.
 * @param data (void *): Data to be searched.
 * @return dll_node_t* 
 */
dll_node_t *dll_search(dll_t *dll, void *data);

/**
 * @brief Insert data into a dll sorting it in the process.
 * 
 * @param dll (dll_t *): Pointer to doubly_linked_list struct.
 * @param head_ref  (dll_node_t **): Pointer to dll node pointer.
 * @param data (void *): Data to be associated with the node. 
 * @param compare : User-defined comparison function. The function must return an integer.
 * Negative if a is less than b, 0 if they are equal, and positive if a is greater than b.
 * @return (int): 0 on success, -1 on failure.
 */
int dll_insertion_sort(dll_t *dll, dll_node_t **head_ref, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Display the contents of a doubly linked list that contains strings.
 * 
 * @param dll (dll_t *): Pointer to doubly_linked_list struct. 
 */
void dll_display_strings(dll_t *dll);

#endif // DLL_H