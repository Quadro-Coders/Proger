#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#define STR_SIZE 100 // max string STR_SIZE
#define N_STRUCTS 10 // number of structures

struct Game {
  wchar_t genre[STR_SIZE];
  wchar_t dev[STR_SIZE];
  wchar_t platform[STR_SIZE];
  wchar_t date[STR_SIZE];
};

// str input 
wint_t input(wchar_t str[STR_SIZE]);

// input  struct
wint_t setter(struct Game *ptr);

// print struct
void view(const struct Game strct);
