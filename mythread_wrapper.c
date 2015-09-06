#define _GNU_SOURCE

#include <sys/types.h>
#include "mythread.h"
#include "mythread_wrapper.h"
#include <sched.h>

void *start_new_thread_function(void *myThread)
{
	mythread_t *thread = (mythread_t *)myThread;
	*thread.futex.down();
	*thread.start_func(*myThread.arg);
	*thread.futex.up();
	return NULL;
}

int mythread_wrapper_create(mythread_t *newThread, mythread_attr_t *attr)
{
	void *stack = malloc(*attr.stacksize);
	pid_t tid = clone(start_new_thread_function, (char *)stack + (*attr.stacksize), 0, (void *)newThread);
	*new_thread.tid = tid;
}