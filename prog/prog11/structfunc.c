#include "structfunc.h"

// str input 
wint_t input(wchar_t str[STR_SIZE]) {
  wint_t ch = 0;
  size_t cnt=0; // count readed wchars
  while (cnt<STR_SIZE && (ch=getwchar())!=L'\n' && ch!=WEOF) {
    *(str+cnt) = (wchar_t)ch;
    cnt++;
  }
  *(str+cnt) = L'\0'; // end string
  if (ch==WEOF) return WEOF;
  return (wint_t)cnt;
}

// input  struct
wint_t setter(struct Game *ptr) {
  //fputws(L"Enter game genre: ", stdout);
  if (input(ptr->genre) == WEOF) return -1;
  //fputws(L"Enter game developer: ", stdout);
  if (input(ptr->dev) == WEOF) return -1;
  //fputws(L"Enter game platform: ", stdout);
  if (input(ptr->platform) == WEOF) return -1;
  //fputws(L"Enter game realese date: ", stdout);
  if (input(ptr->date) == WEOF) return -1;
  return 0;
}

// print struct
void view(const struct Game strct) {
  fputws(L"========== Game info ==========\n", stdout);
  wprintf(L"Genre: %ls\n", strct.genre);
  wprintf(L"Developer: %ls\n", strct.dev);
  wprintf(L"Platform: %ls\n", strct.platform);
  wprintf(L"Realese date: %ls\n", strct.date);
  fputws(L"===============================\n", stdout);
}
