#ifndef PQUEUE_H
#define PQUEUE_H

/**
 * @file pqueue.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Priority Queue Library using a Binary Min Heap.
 * @version 0.1
 * @date 2021-10-26
 * 
 * @details Priority Queue - Abstract Data Type where data elements are added and removed 
 * in a First-In-First-Out (FIFO) order, but elements are assigned a priority.
 * 
 */

#include <stddef.h>

/**
 * @brief Priority Queue Element Struct
 * 
 * @property priority (size_t): Priority value associated with .
 * @property data (void *): Data associated with element.
 * 
 * @typedef pqueue_element_t
 */
typedef struct pqueue_element {
	size_t priority;
	void *data;
} pqueue_element_t;

/**
 * @brief Priority Queue (Binary Heap) Structure.
 * 
 * @property max_size (size_t): Maximum size of the priority queue.
 * @property elements (size_t): Number of elements currently in the pqueue.
 * @property array (struct pqueue element *): Array of pqueue elements.
 * 
 * @typedef pqueue_t
 * 
 */
typedef struct pqueue_binary_heap {
	size_t max_size;
	size_t elements;
	struct pqueue_element *array;
} pqueue_t;

/**
 * @brief Create a pqueue element object.
 * 
 * @param priority (size_t): Priority value of the element.
 * @param data (void *): Data to be associated with the element.
 * @return (pqueue_element_t *): Pointer to pqueue_element struct or NULL on failure. 
 */

/**
 * @brief Create a pqueue object.
 * 
 * @param max_size (size_t): maximum size of the pqueue.
 * @return (pqueue_t *): Pointer to pqueue struct or NULL if a failure occurs.
 */
pqueue_t *create_pqueue(size_t max_size);

/**
 * @brief Deallocate memory used in a pqueue struct.
 * 
 * @param pq (pqueue_t **): Double Pointer to pqueue struct.
 */
void destroy_pqueue(pqueue_t **pq);

/**
 * @brief Add a element to a pqueue.
 * 
 * @param pq (pqueue_t *): Pointer to pqueue struct.
 * @param data (void *): Data to be associated with the element.
 * @param priority (size_t): Priority value of the element.
 * @return (int): 0 on success, -1 on failure.
 */
int enpqueue(pqueue_t *pq, void *data, size_t priority);

/**
 * @brief Remove a element from the front of a pqueue.
 * 
 * @param pq (pqueue_t *): Pointer to pqueue struct. 
 * @return (void *) Pointer to pqueue element's data, NULL on failure.
 */
void *depqueue(pqueue_t *pq);

/**
 * @brief Search a pqueue for data.
 * 
 * @param pq (pqueue_t *): Pointer to pqueue struct.
 * @param data (void *): Data to be associated with the element.
 * @return (pqueue_element_t *) Pointer to pqueue element struct, NULL on failure. 
 */
pqueue_element_t *search_pqueue(pqueue_t *pq, void *data);

/**
 * @brief Find data in a pqueue at a given index.
 * 
 * @param pq (pqueue_t *): Pointer to pqueue struct.
 * @param index (size_t): Index to search.
 * @return (pqueue_element_t *) Pointer to pqueue element struct, NULL on failure. 
 */
pqueue_element_t *find_pqueue_index(pqueue_t *pq, size_t index);

/**
 * @brief Print the contents of a pqueue if it contains integers.
 * 
 * @param pq (pqueue_t *): Pointer to pqueue struct.
 */
void display_pqueue_ints(pqueue_t *pq);

#endif // PQUEUE_H