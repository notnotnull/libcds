#ifndef QUEUE_H
#define QUEUE_H
/**
 * @file queue.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Queue Library
 * @version 0.1
 * @date 2021-10-26
 * 
 * @details Queue - Abstract Data Type where data elements are added and removed 
 * in a First-In-First-Out (FIFO) order.
 */

#include <stddef.h>

/**
 * @brief Queue Node Structure
 * 
 * @property data (void *): Data associated with node.
 * @property next (struct queue node *): Pointer to next node.
 * 
 * @typedef queue_node_t
 */
typedef struct queue_node {
	void *data;
	struct queue_node *next;
} queue_node_t;

/**
 * @brief Queue Struct
 * 
 * @property nodes (size_t): Number of nodes currently in the Queue.
 * @property head (struct queue_node *): Pointer to first node in the Queue.
 * @property tail (struct queue_node *): Pointer to last node in the Queue.
 * 
 * @typedef queue_t
 */
typedef struct queue {
	size_t nodes;
	struct queue_node *head;
	struct queue_node *tail;
} queue_t;

/**
 * @brief Create a queue node structure.
 * 
 * @param data (void *): Data to be associated with the node.
 * @return (queue_node_t *): Pointer to queue_node struct or NULL on failure. 
 */
queue_node_t *queue_create_node(void *data);

/**
 * @brief Create a queue structure.
 * 
 * @return (queue_t *): Pointer to queue struct or NULL if a failure occurs.
 */
queue_t *queue_create(void);

/**
 * @brief Deallocate memory used in a queue struct.
 * 
 * @param q (queue_t **): Double Pointer to queue struct.
 */
void queue_destroy(queue_t **q);

/**
 * @brief Add a node to a queue.
 * 
 * @param q (queue_t *): Pointer to queue struct.
 * @param data (void *): Data to be associated with the node.
 * @return (int): 0 on success, -1 on failure.
 */
int enqueue(queue_t *q, void *data);

/**
 * @brief Remove a node from the front of a queue.
 * 
 * @param q (queue_t *): Pointer to queue struct. 
 * @return (queue_node_t *) Pointer to queue node struct, NULL on failure.
 */
queue_node_t *dequeue(queue_t *q);

/**
 * @brief Search a queue for data.
 * 
 * @param q (queue_t *): Pointer to queue struct.
 * @param data (void *): Data to be associated with the node.
 * @return (queue_node_t *) Pointer to queue node struct, NULL on failure. 
 */
queue_node_t *queue_search(queue_t *q, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Find data in a queue at a given index.
 * 
 * @param q (queue_t *): Pointer to queue struct.
 * @param index (int): Index to search.
 * @return (queue_node_t *) Pointer to queue node struct, NULL on failure. 
 */
queue_node_t *queue_find_at_index(queue_t *q, size_t index);

#endif //QUEUE_H