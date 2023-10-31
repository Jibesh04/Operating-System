/* Reader Writer Problem */
/*
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int num = 1;

void * writer(){
	int wno;
	while(1){
		wno = 1 + rand() % 10;
		// sleep(0.1);
		num = num * 2 % 100;
		printf("Writer %d modified num to %d\n", wno, num);
	}
}

void * reader(){
	int rno;
	while(1){
		rno = 1 + rand() % 10;
		// sleep(0.1);
		printf("Reader %d read num as %d\n", rno, num);
	}
}

int main(){
	int n_read = 3, n_write = 3;
	pthread_t read[n_read], write[n_write];
	for(int i = 0; i < n_read; i++)
		pthread_create(&read[i], NULL, reader, NULL);
	for(int i = 0; i < n_write; i++)
		pthread_create(&write[i], NULL, writer, NULL);
	for(int i = 0; i < n_read; i++)
		pthread_join(read[i], NULL);
	for(int i = 0; i < n_write; i++)
		pthread_join(write[i], NULL);
	return 0;
}
*/

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o ReadWr.exe ./ReadWr.c
./ReadWr.c: In function ‘writer’:
./ReadWr.c:11:27: warning: implicit declaration of function ‘rand’ [-Wimplicit-function-declaration]
   11 |                 wno = 1 + rand() % 10;
      |                           ^~~~
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./ReadWr.exe
Reader 4 read num as 1
Reader 8 read num as 1
Reader 7 read num as 1
Reader 6 read num as 1
Reader 4 read num as 1
Reader 6 read num as 1
Reader 10 read num as 1
Reader 2 read num as 1
Reader 8 read num as 2
Reader 7 read num as 1
Reader 10 read num as 2
Reader 4 read num as 2
Reader 1 read num as 2
Reader 1 read num as 2
Reader 7 read num as 2
Reader 3 read num as 2
Writer 7 modified num to 4
Writer 9 modified num to 8
Writer 8 modified num to 16
Reader 3 read num as 1
Writer 3 modified num to 2
Writer 3 modified num to 28
Reader 7 read num as 2
Reader 8 read num as 56
Reader 1 read num as 64
Reader 10 read num as 56
Reader 2 read num as 4
Writer 4 modified num to 56
Writer 10 modified num to 32
Writer 10 modified num to 24
Writer 8 modified num to 48
Writer 4 modified num to 96
Writer 7 modified num to 92
Writer 2 modified num to 84
Writer 3 modified num to 68
Writer 10 modified num to 36
Writer 4 modified num to 72
Reader 6 read num as 56
Reader 10 read num as 44
Reader 5 read num as 44
Reader 3 read num as 56
Reader 3 read num as 56
^C
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int num = 1;
int readCount = 0;
sem_t wrt;
pthread_mutex_t mutex;

void * writer(void* wno){
	// int wno;
	while(1){
		sem_wait(&wrt);
		// wno = 1 + rand() % 10;
		// sleep(0.1);
		num = num * 2 % 100;
		printf("Writer %d modified num to %d\n", *((int*)wno), num);
		sem_post(&wrt);
	}
}

void * reader(void* rno){
	// int rno;
	while(1){
		pthread_mutex_lock(&mutex);
		readCount++;
		if(readCount == 1)
			sem_wait(&wrt);
		pthread_mutex_unlock(&mutex);
		// rno = 1 + rand() % 10;
		// sleep(0.1);
		printf("Reader %d read num as %d\n", *((int*)rno), num);
		pthread_mutex_lock(&mutex);
		readCount--;
		if(readCount == 0)
			sem_post(&wrt);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	int n_read = 1, n_write = 1;
	pthread_t read[n_read], write[n_write];
	int no[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	sem_init(&wrt, 0, 1);
	
	for(int i = 0; i < n_read; i++)
		pthread_create(&read[i], NULL, reader, (void*)&no[i]);
	for(int i = 0; i < n_write; i++)
		pthread_create(&write[i], NULL, writer, (void*)&no[i]);
	for(int i = 0; i < n_read; i++)
		pthread_join(read[i], NULL);
	for(int i = 0; i < n_write; i++)
		pthread_join(write[i], NULL);
	
	sem_destroy(&wrt);
	pthread_mutex_destroy(&mutex);
	
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ gcc -o ReadWr.exe ./ReadWr.c
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/OS_LAB$ ./ReadWr.exe
Reader 1 read num as 1
Reader 1 read num as 1
Reader 1 read num as 1
Reader 1 read num as 1
Reader 1 read num as 1
Writer 1 modified num to 2
Writer 1 modified num to 4
Writer 1 modified num to 8
Writer 1 modified num to 16
Writer 1 modified num to 32
Writer 1 modified num to 64
Writer 1 modified num to 28
Writer 1 modified num to 56
Reader 1 read num as 56
Reader 1 read num as 56
Reader 1 read num as 56
Reader 1 read num as 56
Reader 1 read num as 56
Reader 1 read num as 56
Reader 1 read num as 56
Writer 1 modified num to 12
Writer 1 modified num to 24
Reader 1 read num as 24
Reader 1 read num as 24
Writer 1 modified num to 48
Writer 1 modified num to 96
^C
*/
