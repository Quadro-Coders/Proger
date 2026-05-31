#include "list.h"

list_node *list_init() { return NULL; }
list_node *list_create_node() {
  list_node *node = (list_node *)malloc(sizeof(list_node));
  if (!node)
    return NULL;
  node->next = node;
  node->prev = node;
  return node;
}
// ввод значений для добавления нескольких элементов в начало
void list_add_front_multi(list_node **head) {
  int c; // c-для очистки буфера
  int key;
  double value;

  for (int i = 1;; i++) {
    printf("Элемент %d\n", i);
    if (input_key(&key) == 0)
      break;

    if (input_value(&value) == 0)
      break;

    list_node *new_head = list_add_front(*head, key, value);
    if (new_head == NULL) {
      printf("Элемент %d не добавлен\n", i);
      return;
    } else {
      *head = new_head;
    }
  }
}
// добавление элемента в начало списка
list_node *list_add_front(struct list_node *head, int key, double value) {
  list_node *new = list_create_node();
  if (new == NULL) {
    printf("Нет памяти\n");
    return NULL;
  }
  new->key = key;
  new->value = value;
  if (head == NULL) {
    new->next = new;
    new->prev = new;
    return new;
  }

  new->next = head;
  new->prev = head->prev;
  head->prev->next = new;
  head->prev = new;
  return new;
}
// ввод значений для добавления нескольких элементов в конец
void list_add_tail_multi(list_node **head) {
  int c; // c-для очистки буфера
  int key;
  double value;
  for (int i = 1;; i++) {
    printf("Элемент %d\n", i);
    if (input_key(&key) == 0)
      break;

    if (input_value(&value) == 0)
      break;

    list_node *new_head = list_add_tail(*head, key, value);
    if (new_head == NULL) {
      printf("Элемент %d не добавлен\n", i + 1);
      return;
    }
    if (*head == NULL) {
      *head = new_head;
    }
  }
}
// добавление элемента в конец списка
list_node *list_add_tail(struct list_node *head, int key, double value) {
  list_node *new_node = list_create_node();
  if (new_node == NULL) {
    printf("Нет памяти\n");
    return NULL;
  }
  new_node->key = key;
  new_node->value = value;
  if (head == NULL) {
    new_node->next = new_node;
    new_node->prev = new_node;
    return new_node;
  }
  new_node->next = head;
  new_node->prev = head->prev;
  new_node->prev->next = new_node;
  head->prev = new_node;
  return new_node;
}

void list_add_index_multi(list_node **head) {
  int c; // c-для очистки буфера
  int key, index;
  double value;

  for (int i = 1;; i++) {
    printf("Элемент %d\n", i);

    if (*head != NULL) {
      if (input_index(&index) == 0)
        break;
    } else {
      printf("Список пуст. Создаем элемент\n");
      index = 0;
    }
    if (input_key(&key) == 0)
      break;

    if (input_value(&value) == 0)
      break;

    list_node *node = list_add_index(*head, key, value, index);
    if (node == NULL) {
      printf("Нет памяти\n");
      return;
    }

    *head = node;
  }
}
// добавление по индексу
list_node *list_add_index(struct list_node *head, int key, double value,
                          int index) {
  if (index < 0) {
    return head;
  }
  if (index == 0) {
    return list_add_front(head, key, value);
  }
  list_node *current = head;
  int i;
  for (i = 0; i < index && current->next != head; i++)
    current = current->next;
  if (i < index) {
    printf("Индекс больше размера списка, добавляем в конец\n");
    list_add_tail(head, key, value);
    return head;
  }
  list_node *node = list_create_node();
  if (node == NULL) {
    printf("Нет памяти\n");
    return head;
  }
  node->key = key;
  node->value = value;

  node->prev = current->prev;
  node->next = current;
  current->prev->next = node;
  current->prev = node;

  return head;
}

// вывод списка
void list_for_each(list_node *head) {
  if (head == NULL) {
    printf("Список пуст\n");
    return;
  }
  list_node *current = head;
  do {
    printf("Ключ: %d, Значение: %lf\n", current->key, current->value);
    current = current->next;
  } while (current != head);
}

// ввод ключа для поиска по ключу
void list_lookup_multi(list_node *head) {
  int c; // c-для очистки буфера
  int key;
  if (head == NULL) {
    printf("Список пуст\n");
    return;
  }
  for (int i = 1;; i++) {
    printf("Элемент %d\n", i);
    if (input_key(&key) == 0)
      break;

    list_lookup(head, key);
  }
}

// поиск по ключу
list_node *list_lookup(struct list_node *head, int key) {
  list_node *current = head;
  do {
    if (current->key == key) {
      printf("Элемент с ключом %d: адрес:%p значение:%lf\n", key, current,
             current->value);
      return current;
    }
    current = current->next;
  } while (current != head);
  printf("Элемент с ключом: %d не найден\n", key);
  return NULL;
}

// очистка списка
void list_clear(list_node **HEAD) {
  if (*HEAD == NULL)
    return;

  list_node *last = (*HEAD)->prev;
  last->next = NULL;

  list_node *current = *HEAD;
  while (current != NULL) {
    list_node *next = current->next;
    free(current);
    current = next;
  }

  *HEAD = NULL;
}

void list_delete_multi(list_node **head) {
  int c; // c-для очистки буфера
  int key;
  if (*head == NULL) {
    printf("Список пуст\n");
    return;
  }
  for (int i = 1;; i++) {
    printf("Элемент %d\n", i);
    if (input_key(&key) == 0)
      break;

    *head = list_delete(*head, key);
    if (*head == NULL) {
      printf("Список пуст\n");
      return;
    }
  }
}

// удаление элемента по ключу
list_node *list_delete(struct list_node *head, int key) {
  if (!head)
    return NULL;
  list_node *listNodeKey = list_lookup(head, key);
  if (listNodeKey == NULL) {
    return head;
  }
  listNodeKey->next->prev = listNodeKey->prev;
  listNodeKey->prev->next = listNodeKey->next;

  if (listNodeKey == head) {
    list_node *newHead = head->next;
    if (newHead == head) {
      free(listNodeKey);
      return NULL;
    }
    printf("Элемент по ключу %d удален\n", key);
    free(listNodeKey);
    return newHead;
  }
  printf("Элемент по ключу %d удален\n", key);
  free(listNodeKey);
  return head;
}

// экспериментальные исследования
// экспериментальная функция
void experiment(list_node **head) {
  int m, c; // m-для правильности ввода, c-для очистки буфера
  int n;    // количество элементов
  do {
    printf("Количество элементов(q для выхода): ");
    m = scanf(" %d", &n);

    if (m == 0) {
      c = getchar();
      if (c == 'q' || c == EOF) {
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        return;
      } else
        printf("Ввод некорректный. Повторите ввод\n");
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    }
  } while (!m);
  double t1 = wtime();

  for (int i = 1; i <= n; i++) {
    if (*head == NULL)
      *head = list_add_tail(*head, getrand(0, 10000000), getrand(0, 10000000));
    else
      list_add_tail(*head, getrand(0, 10000000), getrand(0, 10000000));
  }
  t1 = wtime() - t1;
  // printf("Последний ключ: %d\n", (*head)->prev->key);
  printf("Время добавления в конец: %lf мс\n", t1 * 1e3);

  double t2 = wtime();
  list_lookup(*head, getrand(0, 10000000));
  t2 = wtime() - t2;
  printf("Время поиска: %lf мс\n", t2 * 1e3);
}

//
int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int input_key(int *key) {
  int c, m;
  do {
    printf("Введите ключ(q для выхода): ");
    m = scanf("%d", key);
    if (m == 0) {
      c = getchar();
      if (c == 'q' || c == EOF) {
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        return 0;
      } else
        printf("Ввод некорректный. Повторите ввод\n");
    }
    while ((c = getchar()) != '\n' && c != EOF)
      ;
  } while (!m);
  return 1;
}

int input_value(double *value) {
  int c, m;
  do {
    printf("Введите значение(q для выхода): ");
    m = scanf("%lf", value);
    if (m == 0) {
      c = getchar();
      if (c == 'q' || c == EOF) {
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        return 0;
      } else
        printf("Ввод некорректный. Повторите ввод\n");
    }
    while ((c = getchar()) != '\n' && c != EOF)
      ;
  } while (!m);
  return 1;
}

int input_index(int *index) {
  int c, m;
  do {
    printf("Введите индекс(q для выхода): ");
    m = scanf("%d", index);
    if (m == 0) {
      c = getchar();
      if (c == 'q' || c == EOF) {
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        return 0;
      } else
        printf("Ввод некорректный. Повторите ввод\n");
    }
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    if (*index < 0) {
      printf("Индекс меньше 0. Повторите ввод\n");
      m = 0;
    }
  } while (!m);
  return 1;
}

void menu() {
  printf("1) Создать новый список\n");
  printf("2) Добавить в начало списка\n");
  printf("3) Добавить в конец списка\n");
  printf("4) Добавить по индексу\n");
  printf("5) Поиск элемента\n");
  printf("6) Удалить элемент по ключу\n");
  printf("7) Вывести все элементы списка\n");
  printf("8) Очистить список\n");
  printf("9) Экспериментальные исследования\n");
  printf("0) Завершить работу\n");
}