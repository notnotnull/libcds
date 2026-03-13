#ifndef STACK_H
#define STACK_H
/**
 * @file stack.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Stack Library
 * @version 1.0
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stddef.h>

/**
 * @brief Stack Cell Structure.
 * 
 * @property data (void *): Data associated with the cell.
 * @property next (struct stack_cell): Pointer to next cell in the stack.
 * 
 * @typedef stack_cell_t
 * 
 */
typedef struct stack_cell {
	void *data;
	struct stack_cell *next;
} stack_cell_t;

/**
 * @brief Stack Structure.
 * 
 * @property max_size (size_t): Maximum stack size.
 * @property cells (size_t): Track how many cells the stack currently has. 
 * @property top (struct stack_cell *): Pointer to the top stack cell. 
 * 
 * @typedef stack_t
 */
typedef struct stack {
	size_t max_size;
	size_t cells;
	struct stack_cell *top;
} stack_t;

/**
 * @brief Create a stack cell structure.
 * 
 * @param data (void *): Data to be associated with the cell.
 * @return (stack_cell_t *): Pointer to stack_cell struct or NULL on failure. 
 */
stack_cell_t *stack_cell_create(void *data);

/**
 * @brief Create a stack structure.
 * 
 * @param limit (size_t): maximum stack size. 
 * @return (stack_t *): Pointer to stack struct or NULL if a failure occurs.
 */
stack_t *stack_create(size_t limit);

/**
 * @brief Deallocate memory used in a stack struct.
 * 
 * @param s (stack_t **): Double Pointer to stack struct.
 */
void stack_destroy(stack_t **s);

/**
 * @brief Add a cell to the top of a stack.
 * 
 * @param s (stack_t *): Pointer to stack struct.
 * @param data (void *): Data to be assiciated with the cell.
 * @return (int): 0 on success, -1 on memory failure, -2 when stack is full.
 */
int stack_push(stack_t *s, void *data);

/**
 * @brief Remove a cell from the top of a stack.
 * 
 * @param s (stack_t *): Pointer to stack struct. 
 * @return (stack_cell_t *) Pointer to stack cell struct, NULL on failure.
 */
stack_cell_t *stack_pop(stack_t *s);

/**
 * @brief Find data in a stack at a given index.
 * 
 * @param s (stack_t *): Pointer to stack struct.
 * @param index (int): Index to search.
 * @return (stack_cell_t *) Pointer to stack cell struct, NULL on failure. 
 */
stack_cell_t *stack_find_at_index(stack_t *q, size_t index);

#endif // STACK_H