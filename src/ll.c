#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ll_node_t *
ll_create_node (void *data)
{
  ll_node_t *new = calloc (1, sizeof (ll_node_t));
  if (new == NULL)
    {
      goto ret;
    }
  new->data = data;

ret:
  return new;
}

linked_list_t *
ll_create (void)
{
  linked_list_t *ll = calloc (1, sizeof (linked_list_t));
  return ll;
}

void
ll_destroy (linked_list_t **ll, void (*destroy) (void *))
{
  if (ll == NULL)
    {
      goto ret;
    }
  ll_node_t *current = (*ll)->head;
  ll_node_t *next_node;

  while (current != NULL)
    {
      next_node = current->next;
      destroy (current->data);
      free (current);
      current = next_node;
    }
ret:
  free (*ll);
  *ll = NULL;
}

int
ll_insert_front (linked_list_t *ll, void *data)
{
  int ret_val = -1;

  /* Initial Check, Make sure LL is not NULL */
  if (ll == NULL)
    {
      goto ret;
    }

  ll_node_t *new = ll_create_node (data);
  if (new == NULL)
    {
      goto ret;
    }
  new->next = ll->head;
  ll->head = new;
  ll->nodes++;

  ret_val = 0;

ret:
  return ret_val;
}

int
ll_insert_rear (linked_list_t *ll, void *data)
{
  int ret_val = -1;
  ll_node_t *new = NULL;
  ll_node_t *tail = NULL;

  new = ll_create_node (data);
  if (new == NULL)
    {
      goto ret;
    }

  new->next = NULL;

  /* If no linked list items - node becomes head */
  if (ll->head == NULL)
    {
      ll->head = new;
      goto success;
    }

  /* Travel to last node */
  tail = ll->head;
  while (tail->next)
    {
      tail = tail->next;
    }

  /* last node */
  tail->next = new;

success:
  ll->nodes++;
  ret_val = 0;

ret:
  return ret_val;
}

int
ll_insert_at_pos (linked_list_t *ll, size_t index, void *data)
{
  ll_node_t *new;
  ll_node_t *prev = ll->head;
  ll_node_t *current = ll->head;
  int ret_val = -1;
  size_t count = 0;

  if (ll == NULL)
    {
      goto ret;
    }

  if (index > ll->nodes)
    {
      fprintf (stderr, "Invalid Index\n");
      goto ret;
    }

  new = ll_create_node (data);
  if (new == NULL)
    {
      goto ret;
    }

  /* If there are no nodes and requested index is 0*/
  if (ll->head == NULL && index == 0)
    {
      ll->head = new;
      goto insert_success;
    }
  else if (ll->head == NULL && index != 0)
    {
      fprintf (stderr, "Invalid Index\n");
      free (new);
      goto ret;
    }

  while (current)
    {
      if (count == index && index == 0)
        {
          new->next = ll->head;
          ll->head = new;
          break;
        }
      if (count == index)
        {
          new->next = current;
          prev->next = new;
          break;
        }
      count++;
      prev = current;
      current = current->next;
    }

insert_success:
  ll->nodes++;
  ret_val = 0;
ret:
  return ret_val;
}

ll_node_t *
ll_search (linked_list_t *ll, void *data)
{
  ll_node_t *temp = ll->head;
  while (temp)
    {
      if (temp->data == data)
        {
          return temp;
        }
      temp = temp->next;
    }

  return NULL;
}

int
ll_insertion_sort (linked_list_t *ll, void *data, int (*compare) (void *a, void *b))
{
  int ret_val = -1;
  if (ll == NULL)
    {
      goto ret;
    }
  ll_node_t *new = ll_create_node (data);
  if (new == NULL)
    {
      goto ret;
    }

  /* Check if inserting into empty list or head is greater */
  if (ll->head == NULL)
    {
      ll->head = new;
    }
  else if (compare (ll->head->data, data) >= 0)
    {
      new->next = ll->head;
      ll->head = new;
    }
  else
    {
      ll_node_t *current = ll->head;
      /* Locate the node before the point of insertion */
      while (current->next != NULL && compare (current->data, new->data) < 0)
        {
          current = current->next;
        }
      new->next = current->next;
      current->next = new;
    }

  ret_val = 0;
ret:
  return ret_val;
}

int
ll_delete_node (linked_list_t *ll, void *data)
{
  int ret_val = -1;
  if (ll == NULL)
    {
      goto ret;
    }

  ll_node_t *current;
  ll_node_t *prev;
  current = ll->head;
  prev = current;

  /* If head node itself holds the key to be deleted */
  if (current != NULL && current->data == data)
    {
      ll->head = current->next;
      goto delete_success;
    }

  while (current != NULL && current->data != data)
    {
      prev = current;
      current = current->next;
    }

  /* Data not found */
  if (current == NULL)
    {
      goto ret;
    }

delete_success:
  ret_val = 0;
  free (current);

ret:
  return ret_val;
}

void
ll_display_ints (linked_list_t *ll)
{
  ll_node_t *current = ll->head;
  while (current)
    {
      printf ("%d->", *(int *)current->data);
      current = current->next;
    }
}