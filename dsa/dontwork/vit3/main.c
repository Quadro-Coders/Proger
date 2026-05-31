#include "list.h"

int main() {
  list_node *HEAD = NULL;
  char exit = 1;
  int n;
  char c;
  while (exit) {

    menu();
    if (scanf("%d", &n) != 1) {
      printf("Ошибка ввода\n");
      continue;
    }
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    switch (n) {
    case 1:
      list_clear(&HEAD);
      HEAD = list_init();
      printf("Создан новый список\n");
      break;
    case 2:
      list_add_front_multi(&HEAD);
      break;
    case 3:
      list_add_tail_multi(&HEAD);
      break;
    case 4:
      list_add_index_multi(&HEAD);
      break;
    case 5:
      list_lookup_multi(HEAD);
      break;
    case 6:
      list_delete_multi(&HEAD);
      break;
    case 7:
      list_for_each(HEAD);
      break;
    case 8:
      list_clear(&HEAD);
      break;
    case 9:
      experiment(&HEAD);
      break;
    case 0:
      list_clear(&HEAD);
      exit = 0;
      break;
    default:
      printf("Такой команды нет\n");
    }
  }
  return 0;
}
//
// нету добавления по файлу
/*
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
*/