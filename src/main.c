#include <stat.h>
#include <stdio.h>

int main(void) {
  struct Stat st;
  generate_stat(&st);

  int result = parse_pid_stat(1, &st);

  printf("%s", st.tcomm);

  return 0;
}
