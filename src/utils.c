#include <utils.h>

unsigned int int_string_length(int input) {
  unsigned int length = 0;
  if(input < 0)
    length ++;

  while((input /= 10) != 0)
    length ++;

  return length;
}
