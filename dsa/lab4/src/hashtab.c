#include <hashtab.h>

// Хеш-функция Кернигана-Ричи (KP)
unsigned int hashtab_hash(char *key)
{
  unsigned int h = 0, hash_mul = 31;
  while (*key)
    h = h * hash_mul + (unsigned int)*key++;
  return h % SIZE_HASH_TAB;
}

// Инициализация хеш-таблицы
void hashtab_init(struct listnode **hashtab)
{
  for (int i = 0; i < SIZE_HASH_TAB; i++)
    *(hashtab + i) = NULL;
}

// Добавление элемента в хеш-таблицу
void hashtab_add(struct listnode **hashtab, char *key, uint32_t value)
{
  listnode *node = (listnode *)malloc(sizeof(listnode));
  unsigned int i = hashtab_hash(key);
  if (node != NULL)
  {
    node->key = (char *)malloc(strlen(key) + 1);
    if (!node->key)
    {
      free(node);
      return;
    }
    strcpy(node->key, key);
    node->value = value;
    node->next = hashtab[i];
    hashtab[i] = node;
  }
}

// Поиск элемента в хеш-таблице
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
  unsigned int i = hashtab_hash(key);
  listnode *temp = hashtab[i];
  while (temp != NULL)
  {
    if (strcmp(key, temp->key) == 0)
      return temp;
    temp = temp->next;
  }
  return NULL;
}

// Удаление элемента из хеш-таблицы
void hashtab_delete(struct listnode **hashtab, char *key)
{
  unsigned int i = hashtab_hash(key);
  listnode *node = hashtab[i];
  listnode *prev = NULL;
  while (node != NULL)
  {
    if (strcmp(key, node->key) == 0)
    {
      if (prev == NULL)
        hashtab[i] = node->next;
      else
        prev->next = node->next;
      free(node->key);
      free(node);
      return;
    }
    prev = node;
    node = node->next;
  }
}

// Очистка всей хеш-таблицы
void clearHash(listnode **hashtab)
{
  for (int i = 0; i < SIZE_HASH_TAB; i++)
  {
    if (hashtab[i] == NULL)
      continue;
    listnode *temp = hashtab[i];
    while (temp != NULL)
    {
      listnode *temp1 = temp->next;
      free(temp->key);
      free(temp);
      temp = temp1;
    }
  }
}

// KR хеш-функция с подсчётом коллизий
void hashtab_add_KR(struct listnode **hashtab, char *key, uint32_t value, int *col)
{
  listnode *node = (listnode *)malloc(sizeof(listnode));
  unsigned int i = hashtab_hash(key);
  if (node != NULL)
  {
    node->key = (char *)malloc(strlen(key) + 1);
    if (!node->key)
    {
      free(node);
      return;
    }
    strcpy(node->key, key);
    // подсчёт коллизии: если ячейка уже занята, увеличиваем счётчик
    if (hashtab[i] != NULL)
      (*col)++;
    node->value = value;
    node->next = hashtab[i];
    hashtab[i] = node;
  }
}

// XOR хеш-функция
unsigned int hashtab_hash_XOR(char *key)
{
  unsigned int h = 0;
  int shift = 0;
  while (*key)
  {
    // побитовое исключающее ИЛИ со сдвигом на 5 позиций
    h ^= ((unsigned int)*key++) << shift;
    shift = (shift + 5) % 32;
  }
  return h % SIZE_HASH_TAB;
}

// Добавление в хеш-таблицу с использованием XOR и подсчётом коллизий
void hashtab_add_XOR(struct listnode **hashtab, char *key, uint32_t value, int *col)
{
  listnode *node = (listnode *)malloc(sizeof(listnode));
  unsigned int i = hashtab_hash_XOR(key);
  if (node != NULL)
  {
    node->key = (char *)malloc(strlen(key) + 1);
    if (!node->key)
    {
      free(node);
      return;
    }
    strcpy(node->key, key);
    if (hashtab[i] != NULL)
      (*col)++;
    node->value = value;
    node->next = hashtab[i];
    hashtab[i] = node;
  }
}

// Поиск в хеш-таблице с использованием XOR
struct listnode *hashtab_lookup_XOR(struct listnode **hashtab, char *key)
{
  unsigned int i = hashtab_hash_XOR(key);
  listnode *temp = hashtab[i];
  while (temp != NULL)
  {
    if (strcmp(key, temp->key) == 0)
      return temp;
    temp = temp->next;
  }
  return NULL;
}
