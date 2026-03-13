#include "ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNV_PRIME_64 1099511628211
#define FNV_OFFSET_64 14695981039346656037u

static int
resize (hash_table_t *ht)
{
  int ret_val = -1;
  size_t i = ht->capacity - 1;
  printf ("Resizing Hashtable %ld -> %ld capacity\n", ht->capacity, (ht->capacity * 2));
  size_t next_size = (ht->capacity * 2);
  ht->array = realloc (ht->array, next_size * (sizeof (ht_item_t)));
  if (!ht->array)
    {
      printf ("Unable to reallocate - something went wrong.\n");
      goto ret;
    }
  ht->capacity = next_size;
  ret_val = 0;
ret:
  return ret_val;
}

static bool
has_item (ht_item_t *item)
{
  return item->has_item || item->data;
}

/**
 * Take a string and return a Fowler-Noll-Vo hash.
 * @authors Glenn Fowler, Landon Curt Noll, Kiem-Phong Vo
 * @date 1991
 * @accessed 2021
 * @source https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 *
 * @param s (char *) - Pointer to the string to hash.
 * @return (uint64_t) 64 bit integer of the string hash.
 */
uint64_t
FNV64 (const char *s)
{
  uint64_t hash = FNV_OFFSET_64, i;
  for (i = 0; i < strlen (s); i++)
    {
      hash = hash ^ (s[i]);
      hash = hash * FNV_PRIME_64;
    }
  return hash;
}

hash_table_t *
create_ht (size_t capacity)
{
  hash_table_t *ht = malloc (sizeof (hash_table_t));
  if (!ht)
    {
      goto ret;
    }
  ht->capacity = capacity;
  ht->array = calloc ((ht->capacity), sizeof (ht_item_t));
  if (!ht->array)
    {
      goto ret;
    }
  ht->items = 0;
  ht->load_factor = (double)2 / 3;
ret:
  return ht;
}

void
destroy_ht (hash_table_t **ht, void (*destroy) (void *))
{
  if (*ht == NULL)
    {
      return;
    }
  for (size_t i = 0; i < (*ht)->capacity; i++)
    {
      destroy ((*ht)->array[i].data);
    }

  free ((*ht)->array);
  (*ht)->array = NULL;
  free (*ht);
  *ht = NULL;
}

int
insert_ht (hash_table_t *ht, void *data, int (*compare) (void *a, void *b))
{
  int ret_val = -1;

  if (ht == NULL)
    {
      goto ret;
    }
  int cmp = 0;

  /* Cast (void *) data to (char *) for hashing purposes using FNV64 */
  size_t hash = FNV64 ((char *)data) % ht->capacity;
  size_t hash_copy = hash;
  while (has_item (&ht->array[hash]))
    {
      /* Collision */
      if (ht->array[hash].hash == hash_copy)
        {
          cmp = compare (ht->array[hash].data, data);
          /* Item already exists */
          if (cmp == 0)
            {
              goto ret;
            }
          else
            {
              while (!has_item (&ht->array[hash]))
                {
                  hash += 1;
                }
            }
        }

      /* Move to next spot in hast table if previous was full - Collision handling technique */
      hash += 1;
    }

  ht->array[hash].has_item = true;
  ht->array[hash].hash = hash_copy;
  ht->array[hash].data = data;
  ht->items++;

  /* If load factor reaches 2/3 capacity then resize by doubling the capacity */
  if ((float)(ht->items) >= ht->capacity * ht->load_factor)
    {
      resize (ht);
    }

  ret_val = 0;
ret:
  return ret_val;
}

ht_item_t *
search_ht (hash_table_t *ht, void *data, int (*compare) (void *a, void *b))
{
  ht_item_t *search = NULL;
  if (ht == NULL)
    {
      goto ret;
    }
  int cmp = 0;

  /* Cast (void *) data to (char *) for hashing purposes using FNV64 */
  size_t hash = FNV64 ((char *)data) % ht->capacity;
  size_t hash_copy = hash;

  while (hash < ht->capacity)
    {
      /* Hash exists */
      if (ht->array[hash].hash == hash_copy)
        {

          /* If the data in the array matches the requested search data then return a reference */
          cmp = compare (ht->array[hash].data, data);
          if (cmp == 0)
            {
              search = &ht->array[hash];
              break;
            }
        }

      /* Move to next spot in hash table */
      hash += 1;
    }

ret:
  return search;
}

ht_item_t *
index_ht (hash_table_t *ht, size_t index)
{
  ht_item_t *index_item = NULL;

  if (index >= ht->capacity)
    {
      goto ret;
    }

  index_item = &ht->array[index];

ret:
  return index_item;
}

int
delete_ht_item (hash_table_t *ht, void *data, int (*compare) (void *a, void *b))
{
  int ret_val = -1;

  ht_item_t *delete = search_ht (ht, data, compare);
  if (!delete)
    {
      goto ret;
    }

  delete->data = NULL;
  delete->has_item = false;
  delete->hash = INT64_MAX;
  ht->items--;

  ret_val = 0;
ret:
  return ret_val;
}