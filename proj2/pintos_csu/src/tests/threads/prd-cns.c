/* Replacing headers with alarm-wait.c */
#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"
#define N 10
#define BUFSIZE 3
static int buffer[BUFSIZE];
static int bufin = 0, bufout = 0;

/* Replacing static sem_t with struct sempahore */
struct semaphore  empty, full;

/* Replacing PTHREAD_Mutex_Intitializer with struct lock */
struct lock buffer_lock;

static void producer(void *arg1 UNUSED) {//Remove pointer from the function and used UNUSED with the parameter to remove the warning
   int i, item;

   for (i = 0; i < N; i++) {
      sem_down(&empty);//Replacing sem_wait to sem_down
      item = i*i*i*i;
      lock_acquire(&buffer_lock);//Replacing lock to lock_acquire
      buffer[bufin] = item;    
      bufin = (bufin + 1) % BUFSIZE;
      lock_release(&buffer_lock);//Replacing unlock to lock_release
      printf("p: put item %d\n", item); 
      sem_up(&full);//Replacing sem_post to sem_up
   }   
  // return NULL;
}

static void consumer(void *arg2 UNUSED) {//Remove pointer from function and used UNUSED with the argument to remove the warning
   int i, item;

   for (i = 0; i < N; i++) {
      sem_down(&full);//Replacing sem_wait to sem_down
      lock_acquire(&buffer_lock);//Replacing lock to lock_acquire
      item = buffer[bufout];
      bufout = (bufout + 1) % BUFSIZE;
      lock_release(&buffer_lock);//Replacing unlock to lock_release
      printf("c: get item %d\n",item);
      sem_up(&empty);//Replacing sem_post to sem_up
   }   
  // return NULL;
}
 
void test_prd_cns(void) {//Replacing main method name to test_prd_cns
   lock_init(&buffer_lock);//lock intialization
   sem_init(&full, 0);//Relacing sem_init with only two parameters
   sem_init(&empty, BUFSIZE);//Replacing sem_init with only two parameters
   thread_create("producer", PRTY_DEFAULT, producer, NULL);//Replacing pthread_create to thread_create and also replacing the first two parameters
   thread_create("consumer", PRTY_DEFAULT, consumer, NULL);//Replacing pthread_create to thread_create and also replacing the first two parameters
  // thread_exit(0);
}

