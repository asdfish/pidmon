#include <stat.h>
#include <stdio.h>

int main(void) {
  struct Stat st;
  printf("%i", st.ppid);

  return 0;
}
