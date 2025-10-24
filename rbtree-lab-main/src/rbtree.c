#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->root = p->nil;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
  newNode->key = key;
  newNode->color = RBTREE_RED;
  newNode->left = t->nil;
  newNode->right = t->nil;

  if (t->root == t->nil)
  {
    newNode->color = RBTREE_BLACK;
    newNode->parent = t->nil;
    t->root = newNode;
    return t->root;
  }

  // 삽입
  node_t *pre = t->nil;
  node_t *cur = t->root;
  while (cur != t->nil)
  {
    pre = cur;
    if (key < cur->key)
      cur = cur->left;
    else
      cur = cur->right;
  }

  newNode->parent = pre;
  if (key < pre->key)
    pre->left = newNode;
  else
    pre->right = newNode;

  // 정렬
  node_t *p, *g, *u;

  while ((p = newNode->parent)->color == RBTREE_RED)
  {
    g = p->parent;
    u = (g->left == p) ? g->right : g->left;

    if (u->color == RBTREE_RED)
    {
      p->color = RBTREE_BLACK;
      u->color = RBTREE_BLACK;
      g->color = RBTREE_RED;
      newNode = g;
    }
    else
    {
      node_t *l, *center, *r;

      if (g->left == p)
      {
        if (key < p->key)
        {
          l = newNode;
          center = p;
          r = g;
        }
        else
        {
          l = p;
          center = newNode;
          r = g;

          l->right = center->left;
          if (center->left != t->nil)
            center->left->parent = l;
        }
      }
      else
      {
        if (key < p->key)
        {
          l = g;
          center = newNode;
          r = p;

          r->left = center->right;
          if (center->right != t->nil)
            center->right->parent = r;
        }
        else
        {
          l = g;
          center = p;
          r = newNode;
        }
      }

      if (g->parent == t->nil)
        t->root = center;
      else if (g->parent->left == g)
        g->parent->left = center;
      else
        g->parent->right = center;

      center->parent = g->parent;
      center->left = l;
      center->right = r;
      l->parent = center;
      r->parent = center;

      center->color = RBTREE_BLACK;
      l->color = RBTREE_RED;
      r->color = RBTREE_RED;

      break;
    }
  }

  t->root->color = RBTREE_BLACK;
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
