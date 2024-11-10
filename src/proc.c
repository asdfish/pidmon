#include <proc.h>
#include <utils.h>
#include <dirent.h>
#include <stddef.h>

int proc_get_pids(int* output, unsigned int output_length) {
  if(output == NULL)
    goto exit_failure;
  if(output_length == 0)
    goto exit_success;

  DIR* directory_pointer = opendir("/proc");
  if(directory_pointer == NULL)
    goto exit_failure;

  unsigned int i = 0;
  struct dirent* dirent_pointer = NULL;
  while(true) {
    dirent_pointer = readdir(directory_pointer);
    if(dirent_pointer == NULL || i > output_length)
      break;

    if(dirent_pointer->d_type == DT_DIR && string_is_int(dirent_pointer->d_name)) {
      int parsed_pid = 0;
      if(string_to_int(dirent_pointer->d_name, &parsed_pid) != 0)
        goto closedir_directory_pointer;

      *(output + i) = parsed_pid;
      i ++;
    }
  }

  closedir(directory_pointer);
exit_success:
  return 0;

closedir_directory_pointer:
  closedir(directory_pointer);
exit_failure:
  return -1;
}

int proc_get_pids_length(unsigned int* output) {
  if(output == NULL)
    goto exit_failure;

  DIR* directory_pointer = opendir("/proc");
  if(directory_pointer == NULL)
    goto exit_failure;

  unsigned int length = 0;
  struct dirent* dirent_pointer = NULL;
  while((dirent_pointer = readdir(directory_pointer)) != NULL)
    if(dirent_pointer->d_type == DT_DIR && string_is_int(dirent_pointer->d_name))
      length ++;

  closedir(directory_pointer);

  *output = length;
  return 0;

exit_failure:
  return -1;
}
