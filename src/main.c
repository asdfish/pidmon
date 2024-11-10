#include <utils.h>
#include <stdio.h>

int main(void) {
  bool is_num = string_is_int("-59");

  printf("%i", is_num);

  return 0;
}
