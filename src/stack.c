#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_cell_t *
stack_cell_create (void *data)
{
  stack_cell_t *new = calloc (1, sizeof (stack_cell_t));
  if (new == NULL)
    {
      goto ret;
    }
  new->data = data;

ret:
  return new;
}

stack_t *
stack_create (size_t limit)
{
  stack_t *s = calloc (1, sizeof (stack_t));
  if (s == NULL)
    {
      goto ret;
    }
  s->max_size = limit;

ret:
  return s;
}

void
stack_destroy (stack_t **s)
{
  if (*s == NULL)
    {
      goto ret;
    }

  if ((*s)->top == NULL)
    {
      goto ret;
    }

  stack_cell_t *temp = (*s)->top;
  stack_cell_t *current = (*s)->top;

  while (current != NULL)
    {
      temp = current;
      current = current->next;
      free (temp);
    }
ret:
  free (*s);
  *s = NULL;
}

int
stack_push (stack_t *s, void *data)
{
  int ret_val = -1;

  if (s == NULL)
    {
      goto ret;
    }
  stack_cell_t *new = stack_cell_create (data);
  if (new == NULL)
    {
      goto ret;
    }

  /* If NULL top */
  if (s->top == NULL)
    {
      s->top = new;
      /* Else insert at beginning and change the top */
    }
  else if (s->cells < s->max_size)
    {
      new->next = s->top;
      s->top = new;
      /* Stack is full */
    }
  else
    {
      ret_val = -2;
      free (new);
      goto ret;
    }
  s->cells++;
  ret_val = 0;

ret:
  return ret_val;
}

stack_cell_t *
stack_pop (stack_t *s)
{
  stack_cell_t *stack_pop_cell = NULL;
  if (s == NULL)
    {
      goto ret;
    }

  stack_cell_t *top_cell = s->top;

  /* If NULL top return NULL */
  if (top_cell != NULL)
    {
      stack_pop_cell = top_cell;
      s->top = top_cell->next;
      s->cells--;
    }

ret:
  return stack_pop_cell;
}

stack_cell_t *
stack_find_at_index (stack_t *s, size_t index)
{

  stack_cell_t *idx_cell = NULL;

  /* If there is no stack return NULL */
  if (s == NULL)
    {
      goto ret;
    }

  size_t count = 0;
  stack_cell_t *temp = s->top;

  /* If there is no top return NULL */
  if (s->top == NULL)
    {
      goto ret;
    }

  /* check if cell index exists */
  while (temp)
    {

      /* Index exists */
      if (count == index)
        {
          idx_cell = temp;
          break;
        }
      temp = temp->next;
      count++;
    }

ret:
  return idx_cell;
}