#include <stat.h>
#include <stdio.h>

int main(void) {
  struct Stat st;
  stat_reset(&st);

  int result = stat_set_from_pid(1, &st);

  printf("%s", st.tcomm);

  return 0;
}
