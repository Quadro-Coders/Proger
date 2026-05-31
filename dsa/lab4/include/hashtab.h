#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_HASH_TAB 20000

typedef struct listnode
{
  char *key;
  uint32_t value;
  struct listnode *next;
} listnode;

// Основные функции хеш-таблицы
unsigned int hashtab_hash(char *key);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, uint32_t value);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);
void clearHash(listnode **hashtab);

// KP хеш-функция с подсчётом коллизий (для эксперимента 6)
void hashtab_add_KR(struct listnode **hashtab, char *key, uint32_t value, int *col);

// XOR хеш-функция с подсчётом коллизий (для эксперимента 6)
unsigned int hashtab_hash_XOR(char *key);
void hashtab_add_XOR(struct listnode **hashtab, char *key, uint32_t value, int *col);
struct listnode *hashtab_lookup_XOR(struct listnode **hashtab, char *key);
