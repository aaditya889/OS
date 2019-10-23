#include"handlers.c"

void load_data() {
  char * codes,
    let [50] = {
      "QWERTYUIOP[]ASDFGHJKL;'`ZXCVBNM,./"
    };
  unsigned short x = 0;
  codes = scan_codes;
  for (int i = 16; i <= 27; i++)
    codes[i] =
    let [x++];
  codes[28] = '\n';
  codes[43] = '\\';
  for (int i = 30; i <= 41; i++)
    codes[i] =
    let [x++];

  for (int i = 44; i <= 53; i++)
    codes[i] =
    let [x++];

  codes[57] = ' ';
}
