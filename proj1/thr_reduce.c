#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
pthread_t* thread;
long range=0;
int j=0;
int n, m;
double* globalsum;
void* function(void *arguments) {
double result;
long id =(long)arguments ;
for(long i=(id*n/m)+1; i<=(id+1)*n/m; i++) {
result += sqrt(i);
}
globalsum[id]= result;
int k=m/2;
for(int i =0; i <m; i++)
{
if(id < k)
{
pthread_join(thread[((id+k)*1)], NULL);
globalsum[id] +=globalsum[((id+k)*1)];
k=k/2;
}
else
break;
}if(id==0)
for(int i=0;i<m;i++)
{
printf("globalsum[%d]= %lf\n",i,globalsum[i]);
}
}

int main(int argc, char *argv[])
{
if(argc<3)
{
printf("Number of threads are required in number of two");
exit(0);
}
m=atoi(argv[1]);
n=atoi(argv[2]);
globalsum=(double*)malloc(m*sizeof(double));
thread = (pthread_t*) malloc(sizeof(pthread_t)*m);
range = n/m;
for(long i=m-1; i>=0; i--)
{
if(pthread_create(&thread[i],NULL,function,(void*)i))
printf("Error:cannot be processed");
}
free(thread);
pthread_exit(NULL);
}
