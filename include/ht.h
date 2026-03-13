#ifndef HT_H
#define HT_H

/**
 * @file ht.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Hash Table Library using FNV64.
 * @version 0.1
 * @date 2021-10-26
 * 
 * @details Hast Table (HT) - A Set ADT implementation with a 1 to 1 mapping of keys and
 * data.
 * 
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Hash Table Item Structure
 * 
 * @property hash (uint64_t): Hash associated with data address.
 * @property data (void *): Data to be hashed and stored in hash table. 
 * @property empty (bool): Boolean value indicating if the location is empty or not.
 * 
 * @typedef ht_item_t 
 * 
 */
typedef struct hash_table_item {
	uint64_t hash;
	void *data;
	bool has_item;
} ht_item_t;

/**
 * @brief Hash Table Structure
 * 
 * @property array (ht_item_t *): Array of hash table items.
 * @property capacity (size_t): Hash table capacity.
 * @property items (size_t): Track the number of items in a hash table.
 * @property load_factor (double): Ratio to determine when the hash table should be resized.
 * 
 * @typedef hash_table_t
 * 
 */
typedef struct hash_table {
	ht_item_t *array;
	size_t capacity;
	size_t items;
	double load_factor;
} hash_table_t;

/**
 * @brief Create a hash_table object. 
 * 
 * @param capacity (size_t): Maximum capacity to create the hash table array.
 * @return (hash_table_t *): Pointer to hash table structure.
 */
hash_table_t *create_ht(size_t capacity);

/**
 * @brief Destroy a hash table object, free memory allocations including any allocated memory given to `data`
 * utilizing a user provided deallocation function.
 * 
 * @param ht (hash_table_t **): Double Pointer to hash table structure.
 * @param destroy : Memory address of user-defined destruction function to be preformed on void * data.
 */
void destroy_ht(hash_table_t **ht, void (*destroy)(void *));

/**
 * @brief Insert data into a hashtable
 * 
 * @param ht (hash_table_t *): Pointer to hash table structure.
 * @param data (void *): Pointer to data that will be inserted.
 * @param compare : User-defined comparison function that must return an int. 
 * @return (int): 0 on successful insertion, -1 on failure. 
 */
int insert_ht(hash_table_t *ht, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Delete a hash table item from a hash table.
 * 
 * @param ht (hash_table_t *): Pointer to hash table structure.
 * @param data (void *): Pointer to data to be hashed, searched, and deleted.
 * @param compare : User-defined comparison function that must return an int.
 * @return (int): 0 on successful insertion, -1 on failure.
 */
int delete_ht_item(hash_table_t *ht, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Search a hash table for given data.
 * 
 * @param ht (hash_table_t *): Pointer to hash table structure.
 * @param data (void *): Pointer to data to be hashed, searched, and deleted.
 * @param compare : User-defined comparison function that must return an int. 
 * @return (ht_item_t *): Pointer to hash table item structure. 
 */
ht_item_t *search_ht(hash_table_t *ht, void *data, int (*compare)(void *a, void *b));

/**
 * @brief Index a hash table an return a pointer to the indexed object.
 * 
 * @param ht (hash_table_t *): Pointer to hash table structure.
 * @param index (size_t): Index to search.
 * @return (ht_item_t *):  Pointer to indexed hash table item structure.
 */
ht_item_t *index_ht(hash_table_t *ht, size_t index);


#endif // HT_H