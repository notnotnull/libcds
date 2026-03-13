#ifndef WGRAPH_H
#define WGRPAH_H
/**
 * @file wgraph.h
 * @author Alex Campbell (alex.m.campbell@hotmail.com)
 * @brief Undirected Weighted Graph Implementation.
 * @version 0.1
 * @date 2021-10-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Adjacency Node Structure.
 * 
 * @property dst (size_t): Destination value.
 * @property weight (size_t): Weight associated with node.
 * @property next (struct adj_node *) Pointer to next node (if applicable). 
 * 
 * @typedef adj_node_t
 * 
 */
typedef struct adj_node {
	size_t dst;
	size_t weight;
	struct adj_node *next;
} adj_node_t;

/**
 * @brief Adjacency List Structure.
 * 
 * @property head (adj_node_t *): Pointer to first node in the adjacency list. 
 * 
 * @typedef adj_list_t
 * 
 */
typedef struct adj_list {
	adj_node_t *head;
} adj_list_t;

/**
 * @brief Weighted Graph Structure.
 * 
 * @property vertices (size_t): Number of vertices created alongside weighted graph.
 * @property array (adj_list_t *): Array of adjacency nodes.
 * 
 * @typedef wgraph_t
 * 
 */
typedef struct graph {
	size_t vertices;
	adj_list_t *array;
} wgraph_t;

/**
 * @brief Create a wgraph structure.
 * 
 * @param vertices (size_t): Number of graph vertices to create.
 * @return (wgraph_t *): Pointer to graph structure.
 */
wgraph_t *create_wgraph(size_t vertices);

/**
 * @brief Create a weighted graph node structure.
 * 
 * @param dst (size_t): Destination value.
 * @param weight (size_t): Weight associated with node.
 * @return (adj_node_t *): pointer to node structure. 
 */
adj_node_t *create_node_w(size_t dst, size_t weight);

/**
 * @brief Deallocate heap memory allocations associated with graph structure.
 * 
 * @param wg (wgraph_t **): Double Pointer to graph struct.
 */
void destroy_wgraph(wgraph_t **wg);

/**
 * @brief Remove a node aand all its edges from a graph. 
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 * @param src (size_t): Source value.
 * @return (int): 0 on success, -1 on failure.
 */
int remove_wgraph_node(wgraph_t *wg, size_t src);

/**
 * @brief Find a node in a graph and return a reference to its location in memory.
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 * @param src (size_t): Source value to search for.
 * @return (adj_node_t *): Pointer to graph node structure.
 */
adj_node_t *find_wgraph_node(wgraph_t *wg, size_t src);

/**
 * @brief Find an edge within a weighted graph.
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 * @param src (size_t): Source value to search for.
 * @param dst (size_t): Destination value to search for.
 * @return true if edge is found.
 * @return false if edge is not found.
 */
bool find_wgraph_edge(wgraph_t *wg, size_t src, size_t dst);

/**
 * @brief Add an edge to a wighted graph.
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 * @param src (size_t): Source value.
 * @param dst (size_t): Destination value.
 * @param weight (size_t): Weight associated with node.
 * @return (int): 0 on success, -1 on failure.
 */
int insert_wgraph_edge(wgraph_t *wg, size_t src, size_t dst, size_t weight);

/**
 * @brief Remove an edge from a weighted graph.
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 * @param src (size_t): Source value.
 * @param dst (size_t): Destination value.
 * @return (int): 0 on success, -1 on failure.
 */
int remove_wgraph_edge(wgraph_t *wg, size_t src, size_t dst);

/**
 * @brief Display an undirected weighted graph to the console. 
 * 
 * @param wg (wgraph_t *): Pointer to graph struct.
 */
void display_wgraph(wgraph_t *wg);

/**
 * @brief Calculate the weight of a given path.
 * 
 * @param wg (wgraph_t *): Pointer to a weighted graph structure.
 * @param path (size_t *): Pointer to a predefined list of node numbers. The user of the library must define.
 * @param path_len (size_t): Size of the predefined user list, `path`.
 * 
 * @return (size_t): Weight of path. On failure 0, with errno set to EINVAL if failure 
 * due to invalid arguments and ENOMEDIUM if path not found. 
 */
size_t calc_wgraph_weight(wgraph_t *wg, size_t *path, size_t path_len);

#endif // WGRAPH_H