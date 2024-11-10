#include <stat.h>
#include <utils.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int stat_set_from_pid(struct Stat* stat, int pid) {
  if(stat == NULL)
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
    &stat->pid,
    stat->tcomm,
    &stat->state,
    &stat->ppid,
    &stat->pgrp,
    &stat->sid,
    &stat->tty_nr,
    &stat->tty_pgrp,
    &stat->flags,
    &stat->min_flt,
    &stat->cmin_flt,
    &stat->maj_flt,
    &stat->cmaj_flt,
    &stat->utime,
    &stat->stime,
    &stat->cutime,
    &stat->cstime,
    &stat->priority,
    &stat->nice,
    &stat->num_threads,
    &stat->it_real_value,
    &stat->start_time,
    &stat->vsize,
    &stat->rss,
    &stat->rsslim,
    &stat->start_code,
    &stat->end_code,
    &stat->start_stack,
    &stat->esp,
    &stat->eip,
    &stat->pending,
    &stat->blocked,
    &stat->sigign,
    &stat->sigcatch,
    &stat->unused_1,
    &stat->unused_2,
    &stat->unused_3,
    &stat->exit_signal,
    &stat->task_cpu,
    &stat->rt_priority,
    &stat->policy,
    &stat->blkio_ticks,
    &stat->gtime,
    &stat->cgtime,
    &stat->start_data,
    &stat->end_data,
    &stat->start_brk,
    &stat->arg_start,
    &stat->arg_end,
    &stat->env_start,
    &stat->env_end,
    &stat->exit_code
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

int stat_reset(struct Stat* stat) {
  if(stat == NULL)
    return -1;

  stat->pid = 0;
  stat->tcomm[0] = '\0';
  stat->state = '\0';
  stat->ppid = 0;
  stat->pgrp = 0;
  stat->sid = 0;
  stat->tty_nr = 0;
  stat->tty_pgrp = 0;
  stat->flags = 0;
  stat->min_flt = 0;
  stat->cmin_flt = 0;
  stat->maj_flt = 0;
  stat->cmaj_flt = 0;
  stat->utime = 0;
  stat->stime = 0;
  stat->cutime = 0;
  stat->cstime = 0;
  stat->priority = 0;
  stat->nice = 0;
  stat->num_threads = 0;
  stat->it_real_value = 0;
  stat->start_time = 0;
  stat->vsize = 0;
  stat->rss = 0;
  stat->rsslim = 0;
  stat->start_code = 0;
  stat->end_code = 0;
  stat->start_stack = 0;
  stat->esp = 0;
  stat->eip = 0;
  stat->pending = 0;
  stat->blocked = 0;
  stat->sigign = 0;
  stat->sigcatch = 0;
  stat->unused_1 = 0;
  stat->unused_2 = 0;
  stat->unused_3 = 0;
  stat->exit_signal = 0;
  stat->task_cpu = 0;
  stat->rt_priority = 0;
  stat->policy = 0;
  stat->blkio_ticks = 0;
  stat->gtime = 0;
  stat->cgtime = 0;
  stat->start_data = 0;
  stat->end_data = 0;
  stat->start_brk = 0;
  stat->arg_start = 0;
  stat->arg_end = 0;
  stat->env_start = 0;
  stat->env_end = 0;
  stat->exit_code = 0;
  return 0;
}

int stats_set_from_pids(struct Stat* stats, unsigned int stats_length, int* pids, unsigned int pids_length) {
  if(stats == NULL || pids == NULL)
    goto exit_failure;
  if(stats_length == 0 || pids_length == 0)
    goto exit_success;

  for(unsigned int i = 0; i < stats_length && i < pids_length; i ++)
    if(stat_set_from_pid(stats + i, *(pids + i)) != 0)
      goto exit_failure;

exit_success:
  return 0;
exit_failure:
  return -1;
}

int stats_reset(struct Stat* stats, unsigned int stats_length) {
  if(stats == NULL)
    goto exit_failure;
  if(stats_length == 0)
    goto exit_success;

  for(unsigned int i = 0; i < stats_length; i ++)
    if(stat_reset(stats + i) != 0)
      goto exit_failure;

exit_success:
  return 0;
exit_failure:
  return -1;
}
