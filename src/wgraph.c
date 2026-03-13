#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "wgraph.h"

/** 
 * @brief Validate that we are allowed to access the requested source and destination node.
 * 
 * @param wg (wgraph_t *): Pointer to a weighted graph struct.
 * @param src (size_t): Source node.
 * @param dst (size_t): Destination node.
 * 
 * @return int: 0 on valid nodes, -1 on invalid nodes.
 */
static int validate_graph_nodes(wgraph_t *wg, size_t src, size_t dst);

void display_wgraph(wgraph_t *wg)
{
	if (wg == NULL) {
		return;
	}

	puts("\nsrc --(Weight)--> dst");
	for (size_t i = 0; i < wg->vertices; i++) {
		adj_node_t *current = wg->array[i].head;
		printf("%ld", i);
		while (current && current->dst != __UINT64_MAX__) {
			printf(" --(%ld)--> %ld", current->weight, current->dst);
			current = current->next;
		}
		puts("");

	}
}

wgraph_t *create_wgraph(size_t vertices)
{
	wgraph_t *new_graph = NULL;

	/* Limit vertices to one less than a uint64 */
	if (vertices < __UINT64_MAX__ ) {
		new_graph = calloc(1, sizeof(wgraph_t));
		if (new_graph == NULL) {
			printf("Unable to Allocate Graph.\n");
			goto ret;
		}
		new_graph->vertices = vertices;
	} else {
		printf("Too many vertices\n");
		goto ret;
	}
	new_graph->array = calloc(vertices, sizeof(adj_list_t));
	if (new_graph->array == NULL) {
		printf("Unable to Allocate graph array.\n");
	}

ret:
	return new_graph;
}

adj_node_t *create_node_w(size_t dst, size_t weight)
{
	adj_node_t *new = calloc(1, sizeof(adj_node_t));
	if (new != NULL) {
		new->dst = dst;
		new->weight = weight;
	}
	return new;
}

void destroy_wgraph(wgraph_t **wg)
{
	if (*wg == NULL) {
		return;
	}
	for (size_t i = 0; i < (*wg)->vertices; i++) {
		adj_node_t *current;

		while ((*wg)->array[i].head != NULL) {
			current = (*wg)->array[i].head;
			(*wg)->array[i].head = (*wg)->array[i].head->next;
			free(current);
		}
		free((*wg)->array[i].head);
	}
	free((*wg)->array);
	free(*wg);
	*wg = NULL;

}

int insert_wgraph_edge(wgraph_t *wg, size_t src, size_t dst, size_t weight)
{
	int ret_external = -1;
	if (wg == NULL) {
		goto ret;
	}
	int ret_internal = 0;

	/* Base check make sure we aren't requesting something out of bounds */
	ret_internal = validate_graph_nodes(wg, src, dst);
	if (ret_internal == -1) {
		goto ret;
	}

	adj_node_t *new = create_node_w(dst, weight);
	if (new == NULL) {
		printf("Unable to allocate new edge node\n");
		goto ret;
	}

	new->next = wg->array[src].head;
	wg->array[src].head = new;

	adj_node_t *new_2 = create_node_w(src, weight);
	if (new_2 == NULL) {
		printf("Unable to allocate new edge node\n");
		goto ret;
	}

	new_2->next = wg->array[dst].head;
	wg->array[dst].head = new_2;

	ret_external = 0;
ret:
	return ret_external;
}

bool find_wgraph_edge(wgraph_t *wg, size_t src, size_t dst)
{
	
	bool found = false;
	if (wg == NULL) {
		goto ret;
	}
	int ret_internal = 0;
	

	ret_internal = validate_graph_nodes(wg, src, dst);
	if (ret_internal == -1) {
		goto ret;
	}

	adj_node_t *current = wg->array[src].head;

	while (current != NULL) {
		if (current->dst == dst) {
			found = true;
			break;
		}
		current = current->next;
	}
	
ret:
	return found;

}

int remove_wgraph_edge(wgraph_t *wg, size_t src, size_t dst)
{
	int ret_external = -1;
	if (wg == NULL) {
		goto ret;
	}
	int ret_internal;
	adj_node_t *current = NULL;
	adj_node_t *prev = NULL;
	adj_node_t *old_node = NULL;

	/* Make sure the node exists and that is indeed an edge */
	ret_internal = find_wgraph_edge(wg, src, dst);
	if (ret_internal == false) {
		goto ret;
	}

	current = wg->array[src].head;
	prev = current;

	while (current) {
		if (current->dst == dst && current != wg->array[src].head) {
			prev->next = current->next;
			free(current);
			break;
		}

		if (current == wg->array[src].head && current->dst == dst) {
			old_node = current->next;
			if (old_node != NULL) {
				current->next = current->next;
			} else {
				current->next = NULL;
			}
			current->dst = __UINT64_MAX__;
			free(old_node);
			break;
		}

		prev = current;
		current = current->next;
	}

	current = wg->array[dst].head;
	prev = current;

	while (current) {
		if (current->dst == src && current != wg->array[dst].head) {
			prev->next = current->next;
			free(current);
			break;
		}

		if (current == wg->array[dst].head && current->dst == src) {
			old_node = current->next;
			if (old_node != NULL) {
				current->next = current->next->next;
			} else {
				current->next = NULL;
			}
			current->dst = __UINT64_MAX__;
			free(old_node);
			break;
		}

		prev = current;
		current = current->next;
	}

	ret_external = 0;
ret:
	return ret_external;
}

adj_node_t *find_wgraph_node(wgraph_t *wg, size_t src)
{
	adj_node_t *search = NULL;
	if (wg == NULL) {
		goto ret;
	}
	int ret_internal = 0;
	ret_internal = validate_graph_nodes(wg, src, 0);
	if (ret_internal == -1) {
		goto ret;
	}

	search = wg->array[src].head;

ret:
	return search;
}

int remove_wgraph_node(wgraph_t *wg, size_t src)
{
	int ret_external = -1;
	if (wg == NULL) {
		goto ret;
	}
	int ret_internal;
	
	/* search for node */
	adj_node_t *remove = find_wgraph_node(wg, src);
	if (remove == NULL) {
		goto ret;
	}

	adj_node_t *current = remove->next;

	/* Remove all relationships and set node to NULL */
	while (wg->array[src].head != NULL) {
		current = wg->array[src].head;
		wg->array[src].head = wg->array[src].head->next;
		free(current);
	}
	free(wg->array[src].head);
	wg->array[src].head = NULL;

	for (size_t i = 0; i < wg->vertices; i++) {
		remove_wgraph_edge(wg, i, src);
	}

	ret_external = 0;
ret:
	return ret_external;
}

size_t calc_wgraph_weight(wgraph_t *wg, size_t *path, size_t path_len)
{
	size_t weight = 0;
	if (wg == NULL) {
		goto ret;
	}

	if (path == NULL || path_len < 2) {
		/* Invalid Argument */
		errno = EINVAL;
		goto ret;
	}

	size_t old_weight = 0;
	adj_node_t *current = NULL;

	for (size_t i = 0; i < path_len - 1; i++) {
		current = wg->array[path[i]].head;
		while (current) {
			if (current->dst == path[i+1]) {
				old_weight = weight;
				weight += current->weight;
				break;
			}
			current = current->next;
		}
		/* No Path */
		if (weight == old_weight) {
			weight = 0;
			errno = ENOMEDIUM;
			goto ret;
		}
	}

ret:
	return weight;
}

static int validate_graph_nodes(wgraph_t *wg, size_t src, size_t dst)
{
	int ret_val = -1;
	if (wg == NULL) {
		goto ret;
	}

	if (src >= wg->vertices || dst >= wg->vertices) {
		goto ret;
	}

	ret_val = 0;
ret:
	return ret_val;
}
