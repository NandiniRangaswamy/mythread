#include <sys/types.h>
#include "myqueue.h"
#include "futex.h"
#include "mythread.h"
#include "mythread_wrapper.h"

#define THREAD_ARRAY_SIZE 250
mythread_t *threadArray[THREAD_ARRAY_SIZE];
int arrayPosition = 0;
queue *schedQueue;
mythread_t *currentThread;

mythread_t mythread_self(void)
{
	
}

/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */
int mythread_create(mythread_t *new_thread_ID,
		    mythread_attr_t *attr,
		    void * (*start_func)(void *),
		    void *arg)
			{
				*new_thread_ID.start_func = start_func;
				*new_thread_ID.arg = arg;
				*new_thread_ID.futex.down();
				threadArray[arrayPosition++] = new_thread_ID;
				mythread_wrapper_create(new_thread_ID, attr);
			}
			

/*
 * mythread_yield - switch from running thread to the next ready one
 */
int mythread_yield(void)
{
	schedQueue.enqueue(currentThread);
	schedule();
}

void schedule()
{
	if(schedQueue.count() == 0)
	{
		return;
	}
	else
	{
		mythread_t *previousThread = currentThread;
		currentThread = schedQueue.dequeue();
		*currentThread.futex.up();
		if(previousThread != NULL)
		{
			*previousThread.futex.down();
		}
	}
}


/*
 * mythread_join - suspend calling thread if target_thread has not finished,
 * enqueue on the join Q of the target thread, then dispatch ready thread;
 * once target_thread finishes, it activates the calling thread / marks it
 * as ready.
 */
int mythread_join(mythread_t target_thread, void **status);

/*
 * mythread_exit - exit thread, awakes joiners on return
 * from thread_func and dequeue itself from run Q before dispatching run->next
 */
void mythread_exit(void *retval);

int mythread_attr_init(mythread_attr_t *attr);
int mythread_attr_destroy(mythread_attr_t *attr);
int mythread_attr_getstack(const mythread_attr_t *attr,
			   void **stackaddr,
			   size_t *stacksize);
int mythread_attr_setstack(mythread_attr_t *attr, void *stackaddr,
			   size_t stacksize);
int mythread_attr_getstacksize(const mythread_attr_t *attr, 
			       size_t *stacksize);
int mythread_attr_setstacksize(mythread_attr_t *attr, size_t stacksize);

#endif /* MYTHREAD_H */
