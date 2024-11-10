#include <utils.h>
#include <string.h>

static const char numbers[10] = {
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
};

unsigned int int_string_length(int input) {
  unsigned int length = 1;

  if(input < 0)
    length ++;

  while((input /= 10) != 0)
    length ++;

  return length;
}

bool string_is_int(const char* string) {
  if(strlen(string) == 0)
    goto exit_failure;
  if(strlen(string) == 1 && string[0] == '-')
    goto exit_failure;

  for(unsigned int i = (string[0] == '-' ? 1 : 0); i < strlen(string); i ++) {
    bool char_is_number = false;
    for(unsigned int j = 0; j < 10; j ++)
      if(string[i] == numbers[j]) {
        char_is_number = true;
        break;
      }

    if(!char_is_number)
      goto exit_failure;
  }

  return true;
exit_failure:
  return false;
}
