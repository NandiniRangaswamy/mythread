#define _GNU_SOURCE

#include <sys/types.h>
#include "mythread.h"
#include <sched.h>

void *start_new_thread_function(void *myThread);

int mythread_wrapper_create(mythread_t *newThread, mythread_attr_t *attr);