#include <stat.h>
#include <utils.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int stat_set_from_pid(int pid, struct Stat* output) {
  if(output == NULL)
    return -1;

  unsigned int stat_path_length = strlen("/proc//stat") + int_string_length(pid);
  char stat_path[stat_path_length + 1];
  stat_path[0] = '\0';

  sprintf(stat_path, "/proc/%i/stat", pid);

  FILE* stat_pointer = fopen(stat_path, "r");
  if(stat_pointer == NULL)
    goto exit_failure;

  int scanned = fscanf(stat_pointer,
    "%i"
    " %256s"
    " %c"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i"
    " %i",
    &output->pid,
    output->tcomm,
    &output->state,
    &output->ppid,
    &output->pgrp,
    &output->sid,
    &output->tty_nr,
    &output->tty_pgrp,
    &output->flags,
    &output->min_flt,
    &output->cmin_flt,
    &output->maj_flt,
    &output->cmaj_flt,
    &output->utime,
    &output->stime,
    &output->cutime,
    &output->cstime,
    &output->priority,
    &output->nice,
    &output->num_threads,
    &output->it_real_value,
    &output->start_time,
    &output->vsize,
    &output->rss,
    &output->rsslim,
    &output->start_code,
    &output->end_code,
    &output->start_stack,
    &output->esp,
    &output->eip,
    &output->pending,
    &output->blocked,
    &output->sigign,
    &output->sigcatch,
    &output->unused_1,
    &output->unused_2,
    &output->unused_3,
    &output->exit_signal,
    &output->task_cpu,
    &output->rt_priority,
    &output->policy,
    &output->blkio_ticks,
    &output->gtime,
    &output->cgtime,
    &output->start_data,
    &output->end_data,
    &output->start_brk,
    &output->arg_start,
    &output->arg_end,
    &output->env_start,
    &output->env_end,
    &output->exit_code
  );

  if(scanned != 52)
    goto fclose_stat_pointer;

  fclose(stat_pointer);
  return 0;

fclose_stat_pointer:
  fclose(stat_pointer);
exit_failure:
  return -1;
}

int stat_reset(struct Stat* output) {
  if(output == NULL)
    return -1;

  output->pid = 0;
  output->tcomm[0] = '\0';
  output->state = '\0';
  output->ppid = 0;
  output->pgrp = 0;
  output->sid = 0;
  output->tty_nr = 0;
  output->tty_pgrp = 0;
  output->flags = 0;
  output->min_flt = 0;
  output->cmin_flt = 0;
  output->maj_flt = 0;
  output->cmaj_flt = 0;
  output->utime = 0;
  output->stime = 0;
  output->cutime = 0;
  output->cstime = 0;
  output->priority = 0;
  output->nice = 0;
  output->num_threads = 0;
  output->it_real_value = 0;
  output->start_time = 0;
  output->vsize = 0;
  output->rss = 0;
  output->rsslim = 0;
  output->start_code = 0;
  output->end_code = 0;
  output->start_stack = 0;
  output->esp = 0;
  output->eip = 0;
  output->pending = 0;
  output->blocked = 0;
  output->sigign = 0;
  output->sigcatch = 0;
  output->unused_1 = 0;
  output->unused_2 = 0;
  output->unused_3 = 0;
  output->exit_signal = 0;
  output->task_cpu = 0;
  output->rt_priority = 0;
  output->policy = 0;
  output->blkio_ticks = 0;
  output->gtime = 0;
  output->cgtime = 0;
  output->start_data = 0;
  output->end_data = 0;
  output->start_brk = 0;
  output->arg_start = 0;
  output->arg_end = 0;
  output->env_start = 0;
  output->env_end = 0;
  output->exit_code = 0;
  return 0;
}
