#include "structfunc.h"

int main() {
  setlocale(LC_ALL, "");

  struct Game Lib[N_STRUCTS]; // aka game library of N_STRUCTS games
  for (size_t i=0; i<N_STRUCTS; i++) {
    //wprintf(L"\tEnter the %lu struct:\n", i+1);
    if (setter(Lib+i) == WEOF) return -1;
  }
  
  //putwchar(L'\n');

  for (size_t i=0; i<N_STRUCTS; i++) {
    view(*(Lib+i));
    putwchar(L'\n');
  }

  return 0;
}
