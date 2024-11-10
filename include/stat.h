#ifndef STAT_H
#define STAT_H

struct Stat {
  int pid;
  char tcomm[256];
  char state;
  int ppid;
  int pgrp;
  int sid;
  int tty_nr;
  int tty_pgrp;
  int flags;
  int min_flt;
  int cmin_flt;
  int maj_flt;
  int cmaj_flt;
  int utime;
  int stime;
  int cutime;
  int cstime;
  int priority;
  int nice;
  int num_threads;
  int it_real_value;
  int start_time;
  int vsize;
  int rss;
  int rsslim;
  int start_code;
  int end_code;
  int start_stack;
  int esp;
  int eip;
  int pending;
  int blocked;
  int sigign;
  int sigcatch;
  int unused_1;
  int unused_2;
  int unused_3;
  int exit_signal;
  int task_cpu;
  int rt_priority;
  int policy;
  int blkio_ticks;
  int gtime;
  int cgtime;
  int start_data;
  int end_data;
  int start_brk;
  int arg_start;
  int arg_end;
  int env_start;
  int env_end;
  int exit_code;
};

extern int generate_stat(struct Stat* output);
extern int parse_pid_stat(int pid, struct Stat* output);

#endif
