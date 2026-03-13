#include "bst.h"
#include <stdlib.h>

bst_node_t *
min_node (bst_node_t *node)
{
  bst_node_t *current = node;

  /* loop down to find the leftmost node */
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

bst_node_t *
create_bst_node (size_t key, void *data)
{
  bst_node_t *new = calloc (1, sizeof (bst_node_t));
  if (new == NULL)
    {
      goto ret;
    }
  new->key = key;
  new->data = data;

ret:
  return new;
}

bst_t *
create_bst (void)
{
  bst_t *bst = calloc (1, sizeof (bst_t));
  return bst;
}

void
destroy_bst (bst_node_t *root, void (*destroy) (void *))
{
  /* Post Order Free */
  if (root == NULL)
    {
      return;
    }

  destroy_bst (root->left, destroy);
  destroy_bst (root->right, destroy);
  destroy (root->data);
  free (root);
  root = NULL;
}

bst_node_t *
insert_bst (bst_node_t *root, size_t key, void *data)
{

  if (root == NULL)
    {
      return create_bst_node (key, data);
    }
  else if (key > root->key)
    {
      root->right = insert_bst (root->right, key, data);
    }
  else if (key < root->key)
    {
      root->left = insert_bst (root->left, key, data);
    }
  /* at this point it is implied that root->key == key */
  return root;
}

bst_node_t *
delete_bst_node (bst_node_t *root, size_t key, void (*destroy) (void *))
{
  /* base case root is NULL: do nothing */
  if (root == NULL)
    return root;

  /*
   * If the key to be deleted is smaller than the root's
   * key, then the node is potentially in the left subtree.
   */
  if (key < root->key)
    root->left = delete_bst_node (root->left, key, destroy);

  /*
   * If the key to be deleted is greater than the root's key, then it lies
   * in right subtree.
   */
  else if (key > root->key)
    root->right = delete_bst_node (root->right, key, destroy);

  /* if key is same as root's key, then This is the node to be deleted */
  else
    {
      /* nodes with only one child or no child */
      if (root->left == NULL)
        {
          bst_node_t *temp = root->right;
          destroy (root->data);
          free (root);
          root = NULL;
          return temp;
        }
      else if (root->right == NULL)
        {
          bst_node_t *temp = root->left;

          /* User implemented destroy function */
          destroy (root->data);
          free (root);
          root = NULL;
          return temp;
        }

      /*
       * Nodes with two children: Get the inorder successor
       * (smallest in the right subtree)
       */
      bst_node_t *temp = min_node (root->right);

      /* Copy the inorder successor's data to this node */
      root = temp;

      /* Delete the inorder successor */
      root->right = delete_bst_node (root->right, temp->key, NULL);
    }
  return root;
}

bst_node_t *
search_bst (bst_node_t *root, size_t key)
{
  /* if root->key is x then the element is found or return NULL if root is NULL */
  if (root == NULL || root->key == key)
    {
      return root;
    }
  else if (key > root->key)
    {
      return search_bst (root->right, key);
    }
  else
    {
      return search_bst (root->left, key);
    }
}
