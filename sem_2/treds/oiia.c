#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define NUM 4
#define STRS 5



void clean(){
    printf("cleaning up");
}

void* threadPrint(void* arg){
pthread_cleanup_push(clear);
char* str = (char**) arg;

for(int i=0;i<STRS;i++){
printf("thrd%s\n",str);
sleep(2);
}
pthread_cleanup_pop(1);
}


void cancelThreads(pthread_t treds[NUM]){
    for (int i=0;i<NUM;i++){
	pthread_cancel(treds[i]);
	printf("thread %d exited\n",i);
    }
}

void createThreads(pthread_t treds[NUM],char seq[NUM][6]){
    for(int i=0;i<NUM;i++){
    	pthread_create(&(treds[i]),NULL,threadPrint,(void*)seq[i]);
        //cancelThreads(treds);
	//sleep(2);
    }

}

int main(){
char seq[NUM][6]={"oiia","iaoii","iai","oiiii"};

srand(time(NULL));
pthread_t threads[NUM]={};
createThreads(threads,seq);
sleep(2);
cancelThreads(threads);
for (int i=0;i<NUM;i++){
    pthread_join(threads[i],NULL);
}
for (int i=0;i<5;i++){
    printf("main thread\n");
}
return 0;
}
