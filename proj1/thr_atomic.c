#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
double global_sum = 0;
pthread_mutex_t lock= PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
struct struct_args {
int num;
int start;
int end;
};
void* function(void *arguments) {
struct struct_args *args = arguments;
double result = 0;
for(long i=args->start; i<=args->end; i++) {
result += sqrt(i);
}
printf("thr %d %f\n", args->num, result);
pthread_mutex_lock(&lock);
global_sum += result;
pthread_mutex_unlock(&lock);
pthread_barrier_wait(&barrier);
return NULL;
}
int main(int argc, char *argv[]) {
if(argc<3) {
printf(" number of threads are required in number power of two");
exit(0);
}
int m = atoi(argv[1]);
int n = atoi(argv[2]);
int start = 1;
int end = n/m;
struct struct_args args[m];
pthread_t thread_id[m];
pthread_barrier_init(&barrier,NULL,m+1);
for(int i=0;i<m;i++){
args[i].start=start;
args[i].end = end;
args[i].num = i;
start = end+1;
end += n/m;
pthread_create(&thread_id[i], NULL, function, (void *)&args[i]);
}
pthread_barrier_wait(&barrier);
printf("square root sum %f\n", global_sum);
pthread_barrier_destroy(&barrier);
return 0;
}

