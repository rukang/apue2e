#include "apue.h"
#include <pthread.h>

pthread_t ntid;

/*thread safe: it's context is safe against threaded call*/
void
printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
	  (unsigned int)tid, (unsigned int)tid);
}

/*entry point of the new thread: only one argument*/
void *
thr_fn(void *arg)
{
	printids("new thread: ");/*call a thread safe function*/
	return((void *)0);/*return to done*/
}
/*entry point of the master thread*/
int
main(void)
{
	int		err;/*main thread*/

	err = pthread_create(&ntid, NULL, thr_fn, NULL);/*master thread give one argument and the global resource to share*/
	if (err != 0)/*main thread*/
		err_quit("can't create thread: %s\n", strerror(err));
	sleep(1);
	printids("main thread:");/*call a thread safe function*/
	sleep(1);
	exit(0);/*exit as the container process*/
}

