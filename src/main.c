#include <proc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  unsigned int pids_length = 0;
  if(proc_get_pids_length(&pids_length) != 0) {
    printf("pids_length");
    return -1;
  }

  int* pids = (int*) malloc(pids_length * sizeof(int));
  if(pids == NULL) {
    printf("malloc");
    return -1;
  }

  if(proc_get_pids(pids, pids_length) != 0) {
    printf("proc_get_pids");
    free(pids);
    return -1;
  }

  for(unsigned int i = 0; i < pids_length; i ++)
    printf("%i\n", pids[i]);

  free(pids);

  return 0;
}
