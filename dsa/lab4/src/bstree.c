#include <bstree.h>
// создание бинарного дерева
struct bstree *bstree_create(char *key, uint32_t value)
{
  bstree *node = (bstree *)malloc(sizeof(bstree));
  if (node != NULL)
  {

    node->key = (char *)malloc(strlen(key) + 1);
    if (!node->key)
    {
      free(node);
      exit(EXIT_FAILURE);
    }
    strcpy(node->key, key);

    node->value = value;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}
// добавление в бинарное дерево
void bstree_add(struct bstree *tree, char *key, uint32_t value)
{
  if (tree == NULL)
    return;

  bstree *par;
  for (par = tree; tree != NULL;)
  {
    par = tree;
    int cmp = strcmp(key, tree->key);
    if (cmp < 0)
      tree = tree->left;
    else if (cmp > 0)
      tree = tree->right;
    else
      return;
  }

  bstree *node = (bstree *)malloc(sizeof(bstree));
  if (node == NULL)
    return;

  node->key = (char *)malloc(strlen(key) + 1);
  if (!node->key)
  {
    free(node);
    exit(EXIT_FAILURE);
  }
  strcpy(node->key, key);
  node->value = value;
  node->left = NULL;
  node->right = NULL;

  if (strcmp(key, par->key) < 0)
    par->left = node;
  else
    par->right = node;
}

struct bstree *bstree_lookup(struct bstree *tree, char *key)
{
  while (tree != NULL)
  {
    int cmp = strcmp(key, tree->key);
    if (cmp == 0)
      return tree;
    else if (cmp < 0)
      tree = tree->left;
    else
      tree = tree->right;
  }
  return tree;
}

struct bstree *bstree_delete(struct bstree *tree, char *key)
{
  if (tree == NULL)
    return NULL;

  // поиск
  bstree *lookPrev = NULL;
  bstree *look = tree;
  while (look != NULL)
  {
    int cmp = strcmp(key, look->key);
    if (cmp == 0)
      break;
    lookPrev = look;
    if (cmp < 0)
      look = look->left;
    else
      look = look->right;
  }
  if (look == NULL)
    return tree;

  // нет дочерных
  if (look->left == NULL && look->right == NULL)
  {
    if (lookPrev == NULL)
    {
      free(look->key);
      free(look);
      return NULL;
    }

    if (lookPrev->left == look)
      lookPrev->left = NULL;
    else
      lookPrev->right = NULL;

    free(look->key);
    free(look);
    return tree;
  }

  // 1 дочерный
  if (look->left == NULL || look->right == NULL)
  {
    if (lookPrev == NULL)
    {
      bstree *temp = (look->left != NULL) ? look->left : look->right;
      free(look->key);
      free(look);
      return temp;
    }
    if (lookPrev->left == look)
    {
      if (look->left == NULL)
        lookPrev->left = look->right;
      else
        lookPrev->left = look->left;
    }
    else
    {
      if (look->left == NULL)
        lookPrev->right = look->right;
      else
        lookPrev->right = look->left;
    }
    free(look->key);
    free(look);
    return tree;
  }
  // 2 дочерных
  // ищем минимальный в правом поддереве
  bstree *lookMinPrev = look;
  bstree *lookMin = look->right;
  while (lookMin->left != NULL)
  {
    lookMinPrev = lookMin;
    lookMin = lookMin->left;
  }

  if (lookMinPrev != look)
  {
    lookMinPrev->left = lookMin->right;
    lookMin->right = look->right;
  }

  lookMin->left = look->left;

  // если удаляем корень
  if (look == tree)
  {
    free(look->key);
    free(look);
    return lookMin;
  }

  if (lookPrev->left == look)
    lookPrev->left = lookMin;
  else
    lookPrev->right = lookMin;

  free(look->key);
  free(look);
  return tree;
}

struct bstree *bstree_min(struct bstree *tree)
{
  if (tree == NULL)
    return NULL;
  while (tree->left != NULL)
    tree = tree->left;
  return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
  if (tree == NULL)
    return NULL;
  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}

void clearBstree(bstree *tree)
{
  if (tree == NULL)
    return;
  clearBstree(tree->left);
  clearBstree(tree->right);
  free(tree->key);
  free(tree);
}
